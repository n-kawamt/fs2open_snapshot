/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Network/multi_dogfight.cpp $
 * $Revision: 2.15 $
 * $Date: 2006-09-20 05:05:28 $
 * $Author: taylor $
 * 
 * $Log: not supported by cvs2svn $
 * Revision 2.14  2006/01/16 11:02:23  wmcoolmon
 * Various warning fixes, scripting globals fix; added "plr" and "slf" global variables for in-game hooks; various lua functions; GCC fixes for scripting.
 *
 * Revision 2.13  2006/01/13 03:31:09  Goober5000
 * übercommit of custom IFF stuff :)
 *
 * Revision 2.12  2005/10/10 17:21:07  taylor
 * remove NO_NETWORK
 *
 * Revision 2.11  2005/08/27 00:21:27  Kazan
 * potential fix for mantis bug 237
 *
 * Revision 2.10  2005/07/13 03:25:59  Goober5000
 * remove PreProcDefine #includes in FS2
 * --Goober5000
 *
 * Revision 2.9  2005/07/02 19:45:00  taylor
 * ton of non-standard resolution fixes
 *
 * Revision 2.8  2005/03/02 21:18:19  taylor
 * better support for Inferno builds (in PreProcDefines.h now, no networking support)
 * make sure NO_NETWORK builds are as friendly on Windows as it is on Linux/OSX
 * revert a timeout in Client.h back to the original value before Linux merge
 *
 * Revision 2.7  2005/02/04 10:12:31  taylor
 * merge with Linux/OSX tree - p0204
 *
 * Revision 2.6  2004/07/26 20:47:42  Kazan
 * remove MCD complete
 *
 * Revision 2.5  2004/07/12 16:32:57  Kazan
 * MCD - define _MCD_CHECK to use memory tracking
 *
 * Revision 2.4  2004/03/08 15:06:24  Kazan
 * Did, undo
 *
 * Revision 2.3  2004/03/05 09:02:02  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.2  2003/03/18 10:07:04  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.1.2.1  2002/09/24 18:56:44  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.1  2002/08/01 01:41:07  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:26  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:11  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 11    8/18/99 11:31a Jefff
 * mission title on kill matrix
 * 
 * 10    8/17/99 9:55a Dave
 * Fixed dogfight scoring problem.
 * 
 * 9     8/06/99 12:29a Dave
 * Multiple bug fixes.
 * 
 * 8     5/03/99 8:32p Dave
 * New version of multi host options screen.
 * 
 * 7     4/12/99 10:07p Dave
 * Made network startup more forgiving. Added checkmarks to dogfight
 * screen for players who hit commit.
 * 
 * 6     4/12/99 2:22p Dave
 * More checks for dogfight stats.
 * 
 * 5     2/24/99 3:40p Dave
 * Fixed problem where ships were becoming traitor all the time.
 * 
 * 4     2/24/99 2:25p Dave
 * Fixed up chatbox bugs. Made squad war reporting better. Fixed a respawn
 * bug for dogfight more.
 * 
 * 3     2/23/99 8:11p Dave
 * Tidied up dogfight mode. Fixed TvT ship type problems for alpha wing.
 * Small pass over todolist items.
 * 
 * 2     2/23/99 2:29p Dave
 * First run of oldschool dogfight mode. 
 *   
 * $NoKeywords: $
 */


#include "network/multi_dogfight.h"
#include "network/multi.h"
#include "network/multiutil.h"
#include "network/multi_log.h"
#include "object/object.h"
#include "ship/ship.h"
#include "freespace2/freespace.h"
#include "io/key.h"
#include "missionui/missionscreencommon.h"
#include "gamesnd/eventmusic.h"
#include "gamesnd/gamesnd.h"
#include "network/multiui.h"
#include "missionui/chatbox.h"
#include "ui/ui.h"
#include "graphics/font.h"
#include "globalincs/alphacolors.h"
#include "playerman/player.h"
#include "stats/scoring.h"
#include "mission/missionparse.h"
#include "iff_defs/iff_defs.h"

#include "fs2open_pxo/Client.h"
#include "cfile/cfile.h"




extern int PXO_SID; // FS2 Open PXO Session ID
extern char PXO_Server[32];
extern int PXO_port;

// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT DEFINES/VARS
//

// interface stuff
UI_WINDOW Multi_df_window;

#define NUM_MULTI_DF_BUTTONS			1
#define ACCEPT_BUTTON					0

ui_button_info Multi_df_buttons[GR_NUM_RESOLUTIONS][NUM_MULTI_DF_BUTTONS] = {
	{ // GR_640
		// accept
		ui_button_info("CB_05a",	571,	425,	578,	413,	5),
	}, 	
	{ // GR_1024
		// accept
		ui_button_info("2_CB_05a",	914,	681,	914,	660,	5),
	}
};

int Multi_df_background_bitmap = -1;
char *Multi_df_background_fname[GR_NUM_RESOLUTIONS] = {
	"KillMatrix",
	"2_KillMatrix"
};
char *Multi_df_mask_fname[GR_NUM_RESOLUTIONS] = {
	"KillMatrix-m",
	"2_KillMatrix-m"
};

// coord 3 is max width
static int Kill_matrix_title_coords[GR_NUM_RESOLUTIONS][3] = {
	{	// GR_640
		19, 118, 172
	},
	{	// GR_1024
		33, 194, 272
	}
};

// display area coords
int Multi_df_display_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		43, 133, 569, 269
	},
	{ // GR_1024
		60, 213, 919, 429
	}
};

#define MULTI_DF_TOTAL_ADJUST				5

// "check" icon coords
int Multi_df_check_coords[GR_NUM_RESOLUTIONS] = {
	// GR_640
	28,	

	// GR_1024
	45	
};

// players when the screen started - we need to store this explicity so that even after players leave, we can display the full kill matrix
typedef struct multi_df_score {
	char callsign[CALLSIGN_LEN+1];		// callsign for this guy	
	scoring_struct stats;					// stats for the guy	
	int np_index;								// absolute index into the netplayers array
} multi_df_score;
multi_df_score Multi_df_score[MAX_PLAYERS];
int Multi_df_score_count = 0;


// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT FORWARD DECLARATIONS
//

// process button presses
void multi_df_process_buttons();

// button was pressed
void multi_df_button_pressed(int button);

// setup kill matrix data
void multi_df_setup_kill_matrix();

// blit the kill matrix
void multi_df_blit_kill_matrix();

// stuff a string representing the # of kills, player X had on player Y (where X and Y are indices into Multi_df_score)
// returns the # of kills
int multi_df_stuff_kills(char *kills, int player_x, int player_y);


// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT FUNCTIONS
//

// call once per level just before entering the mission
void multi_df_level_pre_enter()
{			
	int idx;

	// if we're not in dogfight mode, do nothing
	if(!(Netgame.type_flags & NG_TYPE_DOGFIGHT)){
		return;
	}

	// go through all player ships and make them hostile
	for(idx=0; idx<MAX_PLAYERS; idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL) && (Net_players[idx].m_player->objnum >= 0) && (Objects[Net_players[idx].m_player->objnum].type == OBJ_SHIP)){
			Ships[Objects[Net_players[idx].m_player->objnum].instance].team = Iff_traitor;
		}
	}

	// 
}

// evaluate a kill in dogfight by a netplayer
void multi_df_eval_kill(net_player *killer, object *dead_obj)
{
	int dead_index = -1;
	
	// if we're not in dogfight mode, do nothing
	if(!(Netgame.type_flags & NG_TYPE_DOGFIGHT)){
		return;
	}

	// sanity checks
	if((killer == NULL) || (dead_obj == NULL) || (killer->m_player == NULL)){
		return;
	}
	
	// try and find the dead player
	dead_index = multi_find_player_by_object(dead_obj);
	if(dead_index < 0){
		return;
	}
	Assert(dead_index < MAX_PLAYERS);
	if(dead_index == NET_PLAYER_INDEX(killer)){
		return;
	}

	// update his kills
	killer->m_player->stats.m_dogfight_kills[dead_index]++;
}

// debrief
void multi_df_debrief_init()
{
	// no longer is mission
	Game_mode &= ~(GM_IN_MISSION);	
	game_flush();

	// call scoring level close for my stats.  Needed for award_init.  The stats will
	// be backed out if used chooses to replace them.
	scoring_level_close();

	// multiplayer debriefing stuff
	multi_debrief_init();

	// close down any old instances of the chatbox
	chatbox_close();

	// create the new one
	chatbox_create();

	// always play success music
	common_music_init(SCORE_DEBRIEF_SUCCESS);

	// setup kill matrix
	multi_df_setup_kill_matrix();

	UI_WINDOW *w;
	ui_button_info *b;
	int idx;

	// load background bitmap
	Multi_df_background_bitmap = bm_load(Multi_df_background_fname[gr_screen.res]);
	Assert(Multi_df_background_bitmap);

	// create the UI window
	Multi_df_window.create(0, 0, gr_screen.max_w_unscaled, gr_screen.max_h_unscaled, 0);
	Multi_df_window.set_mask_bmap(Multi_df_mask_fname[gr_screen.res]);
	
	// initialize the control buttons
	for (idx=0; idx<NUM_MULTI_DF_BUTTONS; idx++) {
		b = &Multi_df_buttons[gr_screen.res][idx];

		// create the button
		b->button.create(&Multi_df_window, NULL, b->x, b->y, 60, 30, 1, 1);
		
		// set its highlight action
		b->button.set_highlight_action(common_play_highlight_sound);

		// set its animation bitmaps
		b->button.set_bmaps(b->filename);

		// link the mask hotspot
		b->button.link_hotspot(b->hotspot);
	}		

	// add some text
	w = &Multi_df_window;	
	w->add_XSTR("Accept", 1035, Multi_df_buttons[gr_screen.res][ACCEPT_BUTTON].xt, Multi_df_buttons[gr_screen.res][ACCEPT_BUTTON].yt, &Multi_df_buttons[gr_screen.res][ACCEPT_BUTTON].button, UI_XSTR_COLOR_PINK);

	// ***** FS2NetD Debrief ****
	unsigned int CurrentMissionChsum;


	cf_chksum_long(Netgame.mission_name, &CurrentMissionChsum);

	int mValidStatus = 0;

	if (Om_tracker_flag && FS2OpenPXO_Socket.isInitialized())
		mValidStatus = CheckSingleMission(Netgame.mission_name, CurrentMissionChsum, FS2OpenPXO_Socket, PXO_Server, PXO_port);

	//
	// Netgame.mission_name

		
	if (Om_tracker_flag && FS2OpenPXO_Socket.isInitialized() && (multi_num_players() > 1) && !game_hacked_data() && mValidStatus)
	{
		// --------------------- STICK STATS STORAGE CODE IN HERE ---------------------
		int spd_ret = SendPlayerData(PXO_SID, Players[Player_num].callsign, Multi_tracker_login, &Players[Player_num], PXO_Server,   FS2OpenPXO_Socket, PXO_port);
		
		switch (spd_ret) // 0 = pilot updated, 1  = invalid pilot, 2 = invalid (expired?) sid
		{
			case -1:
				multi_display_chat_msg("<Did not receive response from server within timeout period>",0,0);
				multi_display_chat_msg("<Your stats may not have been stored>",0,0);
				multi_display_chat_msg("<This is not a critical error>",0,0);

				break;

			case 0:
				multi_display_chat_msg(XSTR("<stats have been accepted>",850),0,0);
				break;
		
			case 1:
				multi_display_chat_msg(XSTR("<stats have been accepted>",850),0,0);
				multi_display_chat_msg("WARNING: Your pilot was invalid, this is a serious error, possible data corruption",0,0);
				break;

			case 2:
				PXO_SID  = Fs2OpenPXO_Login(Multi_tracker_login, Multi_tracker_passwd, FS2OpenPXO_Socket, PXO_Server, PXO_port);
				if (PXO_SID != -1)
				{
					 if (!SendPlayerData(PXO_SID, Players[Player_num].callsign, Multi_tracker_login, &Players[Player_num], PXO_Server,   FS2OpenPXO_Socket, PXO_port))
					 {	 // succeed!
						multi_display_chat_msg(XSTR("<stats have been accepted>",850),0,0);
						break;
					 }
				}

				multi_display_chat_msg(XSTR("<stats have been tossed>",851),0,0);
				

				break;

			default:
				multi_display_chat_msg("Unknown Stats Store Request Reply",0,0);
				break;
		}

		// refetch to try and resolve the display bug
		GetPlayerData(PXO_SID, Players[Player_num].callsign, &Players[Player_num], PXO_Server, FS2OpenPXO_Socket, PXO_port, true, 30);

	}
	else
	{
		multi_display_chat_msg(XSTR("<stats have been tossed>",851),0,0);
	}
}

// do frame
void multi_df_debrief_do()
{
	int k, new_k;
	char buf[256];
	
	k = chatbox_process();	
	new_k = Multi_df_window.process(k, 0);	

	// process keypresses
	switch(new_k){
	case KEY_ESC:
		multi_debrief_esc_hit();
		break;
	}

	// process buttons	
	multi_df_process_buttons();

	// music stuff
	common_music_do();

	// process debriefing details
	multi_debrief_do_frame();

	// draw the background
	GR_MAYBE_CLEAR_RES(Multi_df_background_bitmap);
	if (Multi_df_background_bitmap >= 0) {
		gr_set_bitmap(Multi_df_background_bitmap);
		gr_bitmap(0, 0);
	} 

	// draw the window
	Multi_df_window.draw();	

	// kill matrix
	multi_df_blit_kill_matrix();

	// render the chatbox
	chatbox_render();

	// draw the mission title
	strcpy(buf, The_mission.name);
	gr_force_fit_string(buf, 255, Kill_matrix_title_coords[gr_screen.res][2]);
	gr_set_color_fast(&Color_bright_white);
	gr_string(Kill_matrix_title_coords[gr_screen.res][0], Kill_matrix_title_coords[gr_screen.res][1], buf);

	// flip
	gr_flip();
}

// close
void multi_df_debrief_close()
{
	int idx;

	// shutdown the chatbox
	chatbox_close();

	// if stats weren't accepted, backout my own stats
	if (multi_debrief_stats_accept_code() != 1) {		
		// if stats weren't accepted, backout my own stats
		if (multi_debrief_stats_accept_code() != 1) {
			if(MULTIPLAYER_MASTER){
				for(idx=0; idx<MAX_PLAYERS; idx++){
					if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL)){
						scoring_backout_accept(&Net_players[idx].m_player->stats);
					}
				}
			} else {
				scoring_backout_accept( &Player->stats );
			}
		}
	}

	// music stuff
	common_music_close();
}


// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT FORWARD DEFINITIONS
//

// process button presses
void multi_df_process_buttons()
{
	int idx;

	for(idx=0; idx<NUM_MULTI_DF_BUTTONS; idx++){
		if(Multi_df_buttons[gr_screen.res][idx].button.pressed()){
			multi_df_button_pressed(idx);
			break;
		}
	}
}

// button was pressed
void multi_df_button_pressed(int button)
{
	switch(button){
	case ACCEPT_BUTTON:
		multi_debrief_accept_hit();
		break;
	}
}

// setup kill matrix data
void multi_df_setup_kill_matrix()
{
	int idx, s_idx;
	multi_df_score *s;

	Multi_df_score_count = 0;

	// add players as necessary
	for(idx=0; idx<MAX_PLAYERS; idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL)){
			// stuff data for this guy
			s = &Multi_df_score[Multi_df_score_count++];

			ml_printf("Dogfight debrief stats for %s", Net_players[idx].m_player->callsign);
			for(s_idx=0; s_idx<MAX_PLAYERS; s_idx++){
				ml_printf("%d", Net_players[idx].m_player->stats.m_dogfight_kills[s_idx]);
			}

			s->stats = Net_players[idx].m_player->stats;
			strcpy(s->callsign, Net_players[idx].m_player->callsign);			
			s->np_index = idx;
		}
	}
}

// blit the kill matrix
void multi_df_blit_kill_matrix()
{
	int idx, s_idx, str_len;
	int cx, cy;
	char squashed_string[CALLSIGN_LEN+1] = "";

	// max width of an individual item, and the text that can be in that item
	float max_item_width = ((float)Multi_df_display_coords[gr_screen.res][2] - 40.0f) / (float)(Multi_df_score_count + 1);
	float max_text_width = max_item_width * 0.8f;

	// start x for the top bar (one item to the right)
	int top_x_start = Multi_df_display_coords[gr_screen.res][0] + (int)max_item_width;
	int top_y_start = Multi_df_display_coords[gr_screen.res][1];	

	// start x for the side bar
	int side_x_start = Multi_df_display_coords[gr_screen.res][0];
	int side_y_start = Multi_df_display_coords[gr_screen.res][1] + 10;

	// draw the top bar
	cx = top_x_start;
	cy = top_y_start;
	for(idx=0; idx<Multi_df_score_count; idx++){		
		// force the string to fit nicely
		strcpy(squashed_string, Multi_df_score[idx].callsign);
		gr_force_fit_string(squashed_string, CALLSIGN_LEN, (int)max_text_width);
		gr_get_string_size(&str_len, NULL, squashed_string);

		// set color and blit the string		
		Assert(Multi_df_score[idx].np_index >= 0);
		if(Multi_df_score[idx].np_index >= 0){
			gr_set_color_fast(Color_netplayer[Multi_df_score[idx].np_index]);
		}
		gr_string(cx + (int)((max_item_width - (float)str_len)/2.0f), cy, squashed_string);

		// next spot
		cx += (int)max_item_width;
	}

	// draw the rest of the scoreboard	
	cx = side_x_start;
	cy = side_y_start;
	int row_total;
	for(idx=0; idx<Multi_df_score_count; idx++){		
		// draw a check if necessary
		if(!MULTI_CONNECTED(Net_players[Multi_df_score[idx].np_index]) || (Net_players[Multi_df_score[idx].np_index].state == NETPLAYER_STATE_DEBRIEF_ACCEPT) || (Net_players[Multi_df_score[idx].np_index].state == NETPLAYER_STATE_DEBRIEF_REPLAY)){
			if(Multi_common_icons[MICON_VALID] != -1){
				gr_set_bitmap(Multi_common_icons[MICON_VALID]);
				gr_bitmap(Multi_df_check_coords[gr_screen.res], cy);
			}
		}

		// draw the name
		cx = Multi_df_display_coords[gr_screen.res][0];
		strcpy(squashed_string, Multi_df_score[idx].callsign);
		gr_force_fit_string(squashed_string, CALLSIGN_LEN, (int)max_text_width);
		gr_get_string_size(&str_len, NULL, squashed_string);		
		Assert(Multi_df_score[idx].np_index >= 0);
		if(Multi_df_score[idx].np_index >= 0){
			gr_set_color_fast(Color_netplayer[Multi_df_score[idx].np_index]);
		}
		gr_string(cx, cy, squashed_string);

		cx = top_x_start;
		row_total = 0;
		for(s_idx=0; s_idx<Multi_df_score_count; s_idx++){
			// stuff the string to be displayed and select the proper display color
			if(s_idx == idx){
				strcpy(squashed_string, "-");
				gr_set_color_fast(&Color_grey);
			} else {
				row_total += multi_df_stuff_kills(squashed_string, idx, s_idx);
				Assert(Multi_df_score[idx].np_index >= 0);
				if(Multi_df_score[idx].np_index >= 0){
					gr_set_color_fast(Color_netplayer[Multi_df_score[idx].np_index]);
				}				
			}						

			// draw the string
			gr_force_fit_string(squashed_string, CALLSIGN_LEN, (int)max_text_width);
			gr_get_string_size(&str_len, NULL, squashed_string);
			gr_string(cx + (int)((max_item_width - (float)str_len)/2.0f), cy, squashed_string);

			// next spot
			cx += (int)max_item_width;
		}

		// draw the row total
		gr_set_color_fast(Color_netplayer[Multi_df_score[idx].np_index]);
		sprintf(squashed_string, "(%d)", row_total);
		gr_get_string_size(&str_len, NULL, squashed_string);
		gr_string(Multi_df_display_coords[gr_screen.res][0] + Multi_df_display_coords[gr_screen.res][2] - (MULTI_DF_TOTAL_ADJUST + str_len), cy, squashed_string);

		cy += 10;
	}

	/*
	// blit totals
	int column_total;
	cx = top_x_start;
	cy += 3;
	for(idx=0; idx<Multi_df_score_count; idx++){
		// add up this column
		column_total = 0;
		for(s_idx=0; s_idx<Multi_df_score_count; s_idx++){
			// add			
			column_total += Multi_df_score[idx].stats.m_dogfight_kills[s_idx];
		}

		// draw
		sprintf(squashed_string, "%d", column_total);
		gr_set_color_fast(Color_netplayer[Multi_df_score[idx].np_index]);
		gr_string(cx, cy, squashed_string);

		// next item
		cx += (int)max_item_width;
	}
	*/
}

// stuff a string representing the # of kills, player X had on player Y (where X and Y are indices into Multi_df_score)
// returns the # of kills
int multi_df_stuff_kills(char *kills, int player_x, int player_y)
{
	multi_df_score *s = &Multi_df_score[player_x];
	strcpy(kills, "");
	
	sprintf(kills, "%d", s->stats.m_dogfight_kills[Multi_df_score[player_y].np_index]);
	return s->stats.m_dogfight_kills[Multi_df_score[player_y].np_index];
}
