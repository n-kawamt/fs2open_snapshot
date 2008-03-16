/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/Hud/HUDsquadmsg.cpp $
 * $Revision: 2.32.2.6 $
 * $Date: 2007-05-26 00:56:01 $
 * $Author: Goober5000 $
 *
 * File to control sqaudmate messaging
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.32.2.5  2007/04/05 16:20:36  karajorma
 * Makes little difference but I suppose I should zero that
 *
 * Revision 2.32.2.4  2007/02/10 04:49:19  Goober5000
 * prevent the AI from falling into the black hole of disarming a turretless ship
 *
 * Revision 2.32.2.3  2007/01/14 20:55:20  karajorma
 * Fix bug where orders you gve last mission are sill accessible to the Order SEXP.
 *
 * Revision 2.32.2.2  2006/11/15 00:33:16  taylor
 * add some needed wing leader checks to prevent Assert()'s and out-of-bounds problems when the leader is dead/dying (Mantis bug #1134)
 *
 * Revision 2.32.2.1  2006/08/27 18:04:24  taylor
 * fix a compiler warning/error on Squadmsg_history[] init
 *
 * Revision 2.32  2006/05/20 02:03:01  Goober5000
 * fix for Mantis #755, plus make the missionlog #defines uniform
 * --Goober5000
 *
 * Revision 2.31  2006/04/05 19:59:11  karajorma
 * Bah! Silly error.
 *
 * Revision 2.30  2006/04/05 17:54:25  karajorma
 * Support added for the Enable/Disable-BuiltinMessages SEXP
 *
 * Revision 2.29  2006/03/22 18:12:16  taylor
 * don't really see the point of the Assert() here, just bail if it's an issue
 *
 * Revision 2.28  2006/03/18 22:00:43  Goober5000
 * fix comm order initialization bug
 * --Goober5000
 *
 * Revision 2.27  2006/03/01 04:01:37  Goober5000
 * fix comm message localization
 *
 * Revision 2.26  2006/02/20 02:13:08  Goober5000
 * added ai-ignore-new which hopefully should fix the ignore bug
 * --Goober5000
 *
 * Revision 2.25  2006/02/02 07:00:29  Goober5000
 * consolidated comm order stuff
 * --Goober5000
 *
 * Revision 2.24  2006/02/02 06:04:02  Goober5000
 * restore retail compatibility with comm orders: one logic bugfix, one cosmetic bugfix
 * --Goober5000
 *
 * Revision 2.23  2006/01/13 11:09:45  taylor
 * fix hud comm message screwups (missing support ship, no coverme, etc) that was part :V: bug and (bigger) part Ship_types related bug
 *
 * Revision 2.22  2006/01/13 03:30:59  Goober5000
 * übercommit of custom IFF stuff :)
 *
 * Revision 2.21  2006/01/10 18:37:46  randomtiger
 * Improvements to voice recognition system.
 * Also function put on -voicer launcher option.
 *
 * Revision 2.20  2006/01/03 17:07:10  randomtiger
 * Added voice recognition functionality for Visual C6 project only.
 * Currently still a work in progress.
 *
 * Revision 2.19  2005/12/29 08:08:33  wmcoolmon
 * Codebase commit, most notably including objecttypes.tbl
 *
 * Revision 2.18  2005/10/29 22:09:29  Goober5000
 * multiple ship docking implemented for initially docked ships
 * --Goober5000
 *
 * Revision 2.17  2005/10/10 17:21:04  taylor
 * remove NO_NETWORK
 *
 * Revision 2.16  2005/07/22 10:18:38  Goober5000
 * CVS header tweaks
 * --Goober5000
 *
 * Revision 2.15  2005/07/13 03:15:52  Goober5000
 * remove PreProcDefine #includes in FS2
 * --Goober5000
 *
 * Revision 2.14  2005/07/11 10:01:06  wmcoolmon
 * Fixed the bug where sending an ignore command to "All fighters" would
 * apply to all ships
 *
 * Revision 2.13  2005/07/07 16:36:57  taylor
 * various compiler warning fixes (some of these from dizzy)
 *
 * Revision 2.12  2005/03/25 06:57:34  wmcoolmon
 * Big, massive, codebase commit. I have not removed the old ai files as the ones I uploaded aren't up-to-date (But should work with the rest of the codebase)
 *
 * Revision 2.11  2005/03/10 08:00:06  taylor
 * change min/max to MIN/MAX to fix GCC problems
 * add lab stuff to Makefile
 * build unbreakage for everything that's not MSVC++ 6
 * lots of warning fixes
 * fix OpenGL rendering problem with ship insignias
 * no Warnings() in non-debug mode for Linux (like Windows)
 * some campaign savefile fixage to stop reverting everyones data
 *
 * Revision 2.10  2005/03/02 21:24:44  taylor
 * more network/inferno goodness for Windows, takes care of a few warnings too
 *
 * Revision 2.9  2005/02/04 10:12:30  taylor
 * merge with Linux/OSX tree - p0204
 *
 * Revision 2.8  2004/07/26 20:47:32  Kazan
 * remove MCD complete
 *
 * Revision 2.7  2004/07/12 16:32:49  Kazan
 * MCD - define _MCD_CHECK to use memory tracking
 *
 * Revision 2.6  2004/03/05 09:02:03  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.5  2004/02/06 21:25:43  Goober5000
 * ugh... okay, *really* fixed the head thing this time
 * --Goober5000
 *
 * Revision 2.4  2004/01/30 07:39:07  Goober5000
 * whew - I just went through all the code I ever added (or at least, that I could
 * find that I commented with a Goober5000 tag) and added a bunch of Asserts
 * and error-checking
 * --Goober5000
 *
 * Revision 2.3  2003/06/11 02:59:47  phreak
 * local ssm stuff for hud.
 * they are always in lock range due to the subspace drive on them
 * they also can't be targeted when in stage 3.
 *
 * Revision 2.2  2003/01/19 22:20:23  Goober5000
 * fixed a bunch of bugs -- the support ship sexp, the "no-subspace-drive" flag,
 * and departure into hangars should now all work properly
 * --Goober5000
 *
 * Revision 2.1  2002/08/01 01:41:05  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:23  penguin
 * Warpcore CVS sync
 *
 * Revision 1.3  2002/05/13 15:11:03  mharris
 * More NO_NETWORK ifndefs added
 *
 * Revision 1.2  2002/05/10 20:42:43  mharris
 * use "ifndef NO_NETWORK" all over the place
 *
 * Revision 1.1  2002/05/02 18:03:08  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 16    9/06/99 10:45a Andsager
 * Add freighter to player override of protected status.
 * 
 * 15    9/06/99 10:32a Andsager
 * Allow attack of protected fighter, bomber, freighters, by player's
 * orders.
 * 
 * 14    8/26/99 8:51p Dave
 * Gave multiplayer TvT messaging a heavy dose of sanity. Cheat codes.
 * 
 * 13    7/30/99 10:31p Dave
 * Added comm menu to the configurable hud files.
 * 
 * 12    7/09/99 5:54p Dave
 * Seperated cruiser types into individual types. Added tons of new
 * briefing icons. Campaign screen.
 * 
 * 11    6/16/99 10:20a Dave
 * Added send-message-list sexpression.
 * 
 * 10    6/09/99 9:53a Andsager
 * 1st pass at grey menu items when no ships/wings/fighters accepting
 * orders.
 * 
 * 9     4/23/99 12:01p Johnson
 * Added SIF_HUGE_SHIP
 * 
 * 8     4/16/99 5:54p Dave
 * Support for on/off style "stream" weapons. Real early support for
 * target-painting lasers.
 * 
 * 7     3/30/99 5:40p Dave
 * Fixed reinforcements for TvT in multiplayer.
 * 
 * 6     3/28/99 5:58p Dave
 * Added early demo code. Make objects move. Nice and framerate
 * independant, but not much else. Don't use yet unless you're me :)
 * 
 * 5     1/07/99 9:07a Jasen
 * HUD coords
 * 
 * 4     12/28/98 3:17p Dave
 * Support for multiple hud bitmap filenames for hi-res mode.
 * 
 * 3     12/21/98 5:02p Dave
 * Modified all hud elements to be multi-resolution friendly.
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:49a Dave
 * 
 * 198   9/11/98 2:05p Allender
 * make reinforcements work correctly in multiplayer games.  There still
 * may be a team vs team issue that I haven't thought of yet :-(
 * 
 * 197   8/28/98 3:28p Dave
 * EMP effect done. AI effects may need some tweaking as required.
 * 
 * 196   8/25/98 1:48p Dave
 * First rev of EMP effect. Player side stuff basically done. Next comes
 * AI code.
 * 
 * 195   6/30/98 2:17p Dave
 * Revised object update system. Removed updates for all weapons. Put
 * button info back into control info packet.
 * 
 * 194   6/09/98 10:31a Hoffoss
 * Created index numbers for all xstr() references.  Any new xstr() stuff
 * added from here on out should be added to the end if the list.  The
 * current list count can be found in FreeSpace.cpp (search for
 * XSTR_SIZE).
 * 
 * 193   5/26/98 11:54a Allender
 * fix multiplayer problems and sexpression crash
 * 
 * 192   5/24/98 4:27p Allender
 * fix bug when determine who could message in multiplayer
 * 
 * 191   5/23/98 2:34a Lawrance
 * Fix problems with HUD squad messaging, don't save/restore bindings
 * 
 * 190   5/22/98 12:41a Allender
 * don't save/restore key presses in comm menu
 * 
 * 189   5/21/98 9:38p Allender
 * don't save/clear key bindings
 * 
 * 188   5/21/98 3:32p Allender
 * don't allow comm menu in observer mode
 * 
 * 187   5/19/98 12:19p Mike
 * Cheat codes!
 * 
 * 186   5/18/98 10:08a Lawrance
 * increase MSG_KEY_EAT_TIME to 300ms
 * 
 * 185   5/18/98 12:41a Allender
 * fixed subsystem problems on clients (i.e. not reporting properly on
 * damage indicator).  Fixed ingame join problem with respawns.  minor
 * comm menu stuff
 * 
 * 184   5/13/98 5:08p Allender
 * fix code in which sometimes wings wouldn't respond in multiplayer when
 * doing a message all fighters
 * 
 * 183   5/08/98 4:38p Allender
 * always allow player ships to count when counting fighters for
 * messaging.  Terran command will now always issue the shooting at
 * friendlies message
 * 
 * 182   5/08/98 2:11p Mike
 * Add "/Repair Subsys" to "Rearm" option in Comm menu.
 * 
 * 181   5/06/98 2:57p Allender
 * always allow rearm ship to be called in
 * 
 * 180   5/05/98 2:04a Mike
 * Fix bug in support ship code.
 * 
 * 179   5/05/98 1:41a Mike
 * Improve support ship availability.
 * 
 * 178   5/04/98 12:59a Allender
 * players who are traitors shouldn't be allowed to rearm or use messaging
 * shortcuts
 * 
 * 177   5/04/98 12:39a Allender
 * make page up and page down only active when > 10 items on menu
 * 
 * 176   4/29/98 10:56p Allender
 * don't allow shortcuts in mutliplayer when player cannot message (except
 * for rearm repair)
 * 
 * 175   4/23/98 10:06a Allender
 * don't use the word "player" in event log for rearm event.  Send
 * shipname instead (players only)
 * 
 * 174   4/23/98 9:15a Allender
 * make rearm shortcut work for clients
 * 
 * 173   4/23/98 1:49a Allender
 * major rearm/repair fixes for multiplayer.  Fixed respawning of AI ships
 * to not respawn until 5 seconds after they die.  Send escort information
 * to ingame joiners
 * 
 * 172   4/22/98 4:59p Allender
 * new multiplayer dead popup.  big changes to the comm menu system for
 * team vs. team.  Start of debriefing stuff for team vs. team  Make form
 * on my wing work with individual ships who have high priority orders
 * 
 * 171   4/21/98 12:15a Allender
 * don't allow observers to use shortcut messaging keys
 * 
 * 170   4/20/98 12:36a Mike
 * Make team vs. team work when player is hostile.  Several targeting
 * problems.
 * 
 * 169   4/13/98 12:51p Allender
 * made countermeasure succeed indicator work in multiplayer.  Make rearm
 * shortcut work more appropriately.
 * 
 * 168   4/10/98 2:42p Johnson
 * (from allender)  when sending wing command, don't assert if ship to
 * send message not found -- don't send message.  Allow rearm message
 * shortcut even if comm destroyed
 * 
 * 167   4/10/98 2:39p Johnson
 * 
 * 166   4/10/98 12:47p Allender
 * changed working on replay popup.  Don't reference repair in comm menu.
 * Added Shift-R for repair me
 * 
 * 165   4/09/98 12:35p Allender
 * disallow messaging to departing wings and departing/dying ships
 * 
 * 164   4/08/98 4:06p Allender
 * make selection of wing Player team based, not TEAM_FRIENDLY.
 * 
 * 163   4/07/98 5:30p Lawrance
 * Player can't send/receive messages when comm is destroyed.  Garble
 * messages when comm is damaged.
 * 
 * 162   4/07/98 1:53p Lawrance
 * Fix uninitialized data bug.
 * 
 * 161   4/06/98 12:11a Allender
 * prevent the comm menu keys from being held over after menu goes away
 * 
 * 160   4/05/98 3:06p Allender
 * don't allow ships/wings to act on orders which they shouldn't receive
 * 
 * 159   4/03/98 12:17a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 158   4/02/98 5:50p Dave
 * Put in support for standard comm messages to get sent to netplayers as
 * well as ai ships. Make critical button presses not get evaluated on the
 * observer.
 *
 * $NoKeywords: $
*/
 


#include "graphics/2d.h"
#include "hud/hud.h"
#include "ship/ship.h"
#include "playerman/player.h"
#include "io/key.h"
#include "io/timer.h"
#include "hud/hudsquadmsg.h"
#include "ai/aigoals.h"
#include "parse/sexp.h"
#include "globalincs/linklist.h"
#include "mission/missionlog.h"
#include "mission/missionmessage.h"
#include "gamesnd/gamesnd.h"
#include "hud/hudsquadmsg.h"
#include "hud/hudtargetbox.h"
#include "ship/subsysdamage.h"
#include "weapon/emp.h"
#include "weapon/weapon.h"
#include "iff_defs/iff_defs.h"
#include "network/multimsgs.h"
#include "network/multiutil.h"
#include "network/multi_pmsg.h"


// defines for different modes in the squad messaging system

#define DEFAULT_MSG_TIMEOUT		(8 * 1000)		// number of seconds * 1000 to get milliseconds
#define MSG_KEY_EAT_TIME			(300)

int Squad_msg_mode;							// current mode that the messaging system is in
LOCAL int Msg_key_used;								// local variable which tells if the key being processed
															// with the messaging system was actually used
LOCAL int Msg_key;									// global which indicates which key was currently pressed
LOCAL int Msg_mode_timestamp;
int Msg_instance;						// variable which holds ship/wing instance to send the message to
int Msg_shortcut_command;			// holds command when using a shortcut key
LOCAL int Msg_target_objnum;				// id of the current target of the player
LOCAL ship_subsys *Msg_targeted_subsys;// pointer to current subsystem which is targeted
//#ifndef NDEBUG
LOCAL	int Msg_enemies;						// tells us whether or not to message enemy ships or friendlies
//#endif

LOCAL int Msg_eat_key_timestamp;			// used to temporarily "eat" keys

// defined to position the messaging box
int Mbox_item_h[GR_NUM_RESOLUTIONS] = {
	10, 
	10
};
int Mbox_item_xoffset[GR_NUM_RESOLUTIONS] = {
	17,
	17
};

// top of the message box gauge
int Mbox_top_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		445, 5
	},
	{ // GR_1024
		827, 5
	}
};

int Mbox_bmap_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		445, 17
	},
	{ // GR_1024
		827, 17
	}
};

// squadmsg menu pgup and pgdn
int Menu_pgup_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		590, 9
	},
	{ // GR_1024
		937, 9
	}
};
int Menu_pgdn_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		590, 120
	},
	{ // GR_1024
		937, 120
	}
};

// -----------
// following defines/vars are used to build menus that are used in messaging mode

typedef struct mmode_item {
	int	instance;					// instance in Ships/Wings array of this menu item
	int	active;						// active items are in bold text -- inactive items greyed out
	char	text[NAME_LENGTH];		// text to display on the menu
} mmode_item;

#define MAX_MENU_ITEMS		50				// max number of items in the menu
#define MAX_MENU_DISPLAY	10				// max number that can be displayed

mmode_item MsgItems[MAX_MENU_ITEMS];
int Num_menu_items = -1;					// number of items for a message menu
int First_menu_item= -1;							// index of first item in the menu

// -----------
// following set of vars/defines are used to store/restore key bindings for keys that
// are used in messaging mode

// array to temporarily store key bindings that will be in use for the messaging
// system
typedef struct key_store {
	int	option_num;					// which element in the	Control_config array is this
	int	id;							// which id (1 or 2) is this key.
	int	key_value;					// which key value to put there.
} key_store;

#define MAX_KEYS_NO_SCROLL	10
#define MAX_KEYS_USED		12		// maximum number of keys used for the messaging system

key_store key_save[MAX_KEYS_USED];		// array to save the key information during messaging mode
int num_keys_saved = 0;					// number of keys that are saved.

// next array is the array of MAX_KEYS_USED size which are the keys to use for messaging mode

int keys_used[] = {	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
							KEY_PAGEUP, KEY_PAGEDOWN  };

#define ID1		1
#define ID2		2

// following are defines and character strings that are used as part of messaging mode

#define NUM_COMM_ORDER_TYPES			6

#define TYPE_SHIP_ITEM					0
#define TYPE_WING_ITEM					1
#define TYPE_ALL_FIGHTERS_ITEM			2
#define TYPE_REINFORCEMENT_ITEM			3
#define TYPE_REPAIR_REARM_ITEM			4
#define TYPE_REPAIR_REARM_ABORT_ITEM	5


char Comm_order_types[NUM_COMM_ORDER_TYPES][NAME_LENGTH];
comm_order Comm_orders[NUM_COMM_ORDER_ITEMS];


// Goober5000
// this is stupid, but localization won't work otherwise
void hud_init_comm_orders()
{
	int i;

	char *temp_comm_order_types[] =
	{
		XSTR("Ships", 293),
		XSTR("Wings", 294),
		XSTR("All Fighters", 295),
		XSTR("Reinforcements", 296),
		XSTR("Rearm/Repair Subsys", 297),
		XSTR("Abort Rearm", 298)
	};

	struct { char *name; int item; } temp_comm_orders[] =
	{
		{ XSTR("Destroy my target", 299),	ATTACK_TARGET_ITEM },
		{ XSTR("Disable my target", 300),	DISABLE_TARGET_ITEM },
		{ XSTR("Disarm my target", 301),	DISARM_TARGET_ITEM },
		{ XSTR("Destroy subsystem", 302),	DISABLE_SUBSYSTEM_ITEM },
		{ XSTR("Protect my target", 303),	PROTECT_TARGET_ITEM },
		{ XSTR("Ignore my target", 304),	IGNORE_TARGET_ITEM },
		{ XSTR("Form on my wing", 305),		FORMATION_ITEM },
		{ XSTR("Cover me", 306),			COVER_ME_ITEM },
		{ XSTR("Engage enemy", 307),		ENGAGE_ENEMY_ITEM },
			{ XSTR("Capture my target", 308),	CAPTURE_TARGET_ITEM },
		{ XSTR("Rearm me", 309),			REARM_REPAIR_ME_ITEM },
		{ XSTR("Abort rearm", 310),			ABORT_REARM_REPAIR_ITEM },
		// all ships
		{ XSTR("Depart", 311),				DEPART_ITEM },
	
		// support ships (maintain original comm menu order)
		{ XSTR("Stay near me", -1),			STAY_NEAR_ME_ITEM},
		{ XSTR("Stay near my target", -1),	STAY_NEAR_TARGET_ITEM},
		{ XSTR("Keep safe distance", -1),	KEEP_SAFE_DIST_ITEM},
	};

	for (i = 0; i < NUM_COMM_ORDER_TYPES; i++)
	{
		strcpy(Comm_order_types[i], temp_comm_order_types[i]);
	}

	for (i = 0; i < NUM_COMM_ORDER_ITEMS; i++)
	{
		strcpy(Comm_orders[i].name, temp_comm_orders[i].name);
		Comm_orders[i].item = temp_comm_orders[i].item;
	}
}

// Text to display on the messaging menu when using the shortcut keys
char *comm_order_get_text(int item)
{
	int i;

	for (i = 0; i < NUM_COMM_ORDER_ITEMS; i++)
	{
		if (Comm_orders[i].item == item)
			return Comm_orders[i].name;
	}

	// not found
	Int3();
	return NULL;
}

int squadmsg_history_index = 0;
squadmsg_history Squadmsg_history[SQUADMSG_HISTORY_MAX];

// used for Message box gauge
#define NUM_MBOX_FRAMES		3

static hud_frames Mbox_gauge[NUM_MBOX_FRAMES];
static int Mbox_frames_loaded = 0;
static char *Mbox_fnames[GR_NUM_RESOLUTIONS][NUM_MBOX_FRAMES] =
{
//XSTR:OFF
	{ // GR_640
		"message1",		// top part of menu
		"message2",		// middle part
		"message3"		// bottom part
	}, 
	{ // GR_1024
		"message1",		// top part of menu
		"message2",		// middle part
		"message3"		// bottom part
	}
//XSTR:ON
};

static int Mbox_title_coord[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		447, 6
	},
	{ // GR_1024
		829, 6
	}
};
static int Mbox_item_coord[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		449, 18
	},
	{ // GR_1024
		831, 18
	}
};

// forward declarations
void hud_add_issued_order(char *name, int order, char *target);
int hud_squadmsg_is_target_order_valid(int order, int find_order, ai_info *aip = NULL );
int hud_squadmsg_ship_order_valid( int shipnum, int order );

// function to set up variables needed when messaging mode is started
void hud_squadmsg_start()
{
//	int i;

	//if ( num_keys_saved < 0 )  // save the keys if they haven't been saved yet
	hud_squadmsg_save_keys();

	Msg_key = -1;

/*
	for (i=0; i<num_keys_saved; i++)
		clear_key_binding ( (short) key_save[i].key_value );				// removes all mention of this key from Control_config
*/

	Num_menu_items = -1;													// reset the menu items
	First_menu_item = 0;
	Squad_msg_mode = SM_MODE_TYPE_SELECT;							// start off at the base state
	Msg_mode_timestamp = timestamp(DEFAULT_MSG_TIMEOUT);		// initialize our timer to bogus value
	Msg_shortcut_command = -1;											// assume no shortcut key being used
	Msg_target_objnum = Player_ai->target_objnum;				// save the players target object number
	Msg_targeted_subsys = Player_ai->targeted_subsys;				// save the players currently targted subsystem
#ifndef NDEBUG
	Msg_enemies = 0;														// tells us if we are messaging enemy ships
#endif

	snd_play( &Snds[SND_SQUADMSGING_ON] );
}

// functions which will restore all of the key binding stuff when messaging mode is done
void hud_squadmsg_end()
{
/*
	int i;
	key_store *ksp;

	// move through all keys saved and restore their orignal values.
	for ( i=0; i<num_keys_saved; i++ ) {
		ksp = &key_save[i];
		Control_config[ksp->option_num].key_id = (short) ksp->key_value;
	}
*/

	if ( message_is_playing() == FALSE )
		snd_play( &Snds[SND_SQUADMSGING_OFF] );
}

// function which returns true if there are fighters/bombers on the players team in the mission
// In debug versions, we will allow messaging to enemies
bool hud_squadmsg_exist_fighters( )
{
	ship_obj *so;
	object *objp;
	ship *shipp;

	for (so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so))
	{	
		objp = &Objects[so->objnum];
		shipp = &Ships[objp->instance];
		Assert ( shipp->objnum != -1 );

		// check fighter is accepting orders
		if (shipp->orders_accepted == 0)
			continue;

		// be sure ship is on correct team
#ifdef NDEBUG
		if (shipp->team != Player_ship->team)
			continue;
#else
		if (!Msg_enemies && (shipp->team != Player_ship->team))
			continue;
#endif

		// cannot be my ship or an instructor
		if ((objp == Player_obj) || is_instructor(objp))
			continue;
			
		// ship must be a fighter/bomber
		if ( !(Ship_info[shipp->ship_info_index].flags & (SIF_FIGHTER | SIF_BOMBER)) )
			continue;

		// this ship satisfies everything
		return true;
	}

	return false;
}


// function which counts the number of ships available for messaging.  Used to determine if
// we should grey out a menu or allow a shortcut command to apply.  parameter "flag" is used
// to tell us whether or not we should add the ship to a menu item or not.  We include the
// flag so that we don't have to have conditions for messaging ships/wings in two places.
int hud_squadmsg_count_ships(int add_to_menu)
{
	int count;
	ship_obj *so;
	object *objp;
	ship *shipp;

	count = 0;
	for (so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so))
	{	
		objp = &Objects[so->objnum];
		shipp = &Ships[objp->instance];
		Assert ( shipp->objnum != -1 );

		// ships must be able to receive a message
		if ( Ship_info[shipp->ship_info_index].class_type < 0 || !(Ship_types[Ship_info[shipp->ship_info_index].class_type].ai_bools & STI_AI_ACCEPT_PLAYER_ORDERS) )
			continue;

		// be sure ship is on correct team
#ifdef NDEBUG
		if (shipp->team != Player_ship->team)
			continue;
#else
		if (!Msg_enemies && (shipp->team != Player_ship->team))
			continue;
#endif

		// departing or dying ships cannot be on list
		if ( shipp->flags & (SF_DEPARTING|SF_DYING) )
			continue;

		// cannot be my ship or an instructor
		if ((objp == Player_obj) || is_instructor(objp))
			continue;

		// ship must be accepting ship type orders
		if ( shipp->orders_accepted == 0)
			continue;

		// if it is a player ship, we must be in multiplayer
		if ( (objp->flags & OF_PLAYER_SHIP) && !(Game_mode & GM_MULTIPLAYER) )
			continue;

		// if a messaging shortcut, be sure this ship can process the order
		if ( Msg_shortcut_command != -1 ) {
			if ( !(shipp->orders_accepted & Msg_shortcut_command) )
				continue;
			else if ( !hud_squadmsg_ship_order_valid(objp->instance, Msg_shortcut_command) )
				continue;
		}

		// this ship satisfies everything
		count++;
		if (add_to_menu)
		{
			Assert ( Num_menu_items < MAX_MENU_ITEMS );
			strcpy( MsgItems[Num_menu_items].text, shipp->ship_name );
			MsgItems[Num_menu_items].instance = SHIP_INDEX(shipp);
			MsgItems[Num_menu_items].active = 1;
			Num_menu_items++;
		}
	}

	// if adding to the menu and we have > 10 items, then don't allow page up and page down to be used.
	if ( add_to_menu && (Num_menu_items > MAX_MENU_DISPLAY) )
		hud_squadmsg_save_keys(1);

	return count;
}

// routine to return true if a wing should be put onto the messaging menu
int hud_squadmsg_wing_valid(wing *wingp)
{
	// int player_count, j;
	int special_ship_index;

	// a couple of special cases to account for before adding to count (or to menu).  The wing gone
	// flags is firm indication to skip this particular wing.  Also, skip if enemy wing
	if ( (wingp->flags  & WF_WING_GONE) || (wingp->current_count == 0) )
		return 0;

	// departing wings don't get attention either
	if ( wingp->flags & WF_WING_DEPARTING )
		return 0;

	// sanity check on ship_index field -- if check is successful, then check the team.
	special_ship_index = wingp->ship_index[wingp->special_ship];

	// if there is no wing leader then don't bother continuing
	if (special_ship_index < 0)
		return 0;

	// be sure ship is on same team
#ifdef NDEBUG
	if (Ships[special_ship_index].team != Player_ship->team)
		return 0;
#else
	if (!Msg_enemies && (Ships[special_ship_index].team != Player_ship->team))
		return 0;
#endif

	// if this wing is the players wing, and there is only one ship in the wing, then skip past it
	if ( (Ships[Player_obj->instance].wingnum == WING_INDEX(wingp)) && (wingp->current_count == 1) )
		return 0;

	// check if wing commander is accepting orders
	if ( Ships[special_ship_index].orders_accepted == 0)
		return 0;

	// if doing a message shortcut is being used, be sure the wing can "accept" the command.  Only need
	// to look at the wing commander
	if ( Msg_shortcut_command != -1 ) {
		if ( !(Ships[special_ship_index].orders_accepted & Msg_shortcut_command) )
			return 0;
	}
	// MULTI - changed to allow messaging of netplayers
	// don't count wings where all ships are player ships		
	/*
	player_count = 0;
	for ( j = 0; j < wingp->current_count; j++ ) {
		if ( Objects[Ships[wingp->ship_index[j]].objnum].flags & OF_PLAYER_SHIP )
			player_count++;
	}
	if ( player_count == wingp->current_count )
		return 0;
	*/

	return 1;
}

// function like above, except for wings
int hud_squadmsg_count_wings( int add_to_menu )
{
	int count, i, j;

	count = 0;

	// add the player starting wings first
	for ( i = 0; i < MAX_STARTING_WINGS; i++ ) {
		int wingnum;

		wingnum = Starting_wings[i];
		if ( wingnum == -1 )
			continue;

		if ( hud_squadmsg_wing_valid(&Wings[wingnum]) ) {
			count++;
			if ( add_to_menu ) {
				Assert ( Num_menu_items < MAX_MENU_ITEMS );
				strcpy( MsgItems[Num_menu_items].text, Wings[wingnum].name );
				MsgItems[Num_menu_items].instance = wingnum;
				MsgItems[Num_menu_items].active = 1;
				Num_menu_items++;
			}
		}
	}

	for ( i = 0; i < Num_wings; i++ ) {
		// if this wing is a player starting wing, skip it since we added it above
		for ( j = 0; j < MAX_STARTING_WINGS; j++ ) {
			if ( i == Starting_wings[j] )
				break;
		}
		if ( j < MAX_STARTING_WINGS )
			continue;

		if ( hud_squadmsg_wing_valid(&Wings[i]) ) {
			count++;
			if ( add_to_menu ) {
				Assert ( Num_menu_items < MAX_MENU_ITEMS );
				strcpy( MsgItems[Num_menu_items].text, Wings[i].name );
				MsgItems[Num_menu_items].instance = i;
				MsgItems[Num_menu_items].active = 1;
				Num_menu_items++;
			}
		}
	}
	return count;
}


// function to set the current submode in message mode -- also resets variables that
// should be reset inbetween submodes
void hud_squadmsg_do_mode( int mode )
{
	Squad_msg_mode = mode;
	Num_menu_items = -1;
	First_menu_item = 0;
}

void hud_squadmsg_page_down()
{
	if ( (First_menu_item + MAX_MENU_DISPLAY) < Num_menu_items ) {
		First_menu_item += MAX_MENU_DISPLAY;
		Assert ( First_menu_item < Num_menu_items );
	}
}

void hud_squadmsg_page_up()
{
	if ( First_menu_item > 0 ) {
		First_menu_item -= MAX_MENU_DISPLAY;
		Assert (First_menu_item >= 0 );
	}
}

int hud_squadmsg_get_total_keys()
{
	int num_keys_used;

	num_keys_used = MAX_KEYS_NO_SCROLL;
	if ( Num_menu_items > MAX_MENU_DISPLAY )
		num_keys_used = MAX_KEYS_USED;

	return num_keys_used;
}

// function called from high level keyboard read code to give the squadmsg code a key.
// return 1 is the key was used by the messaging code, 0 otherwise
int hud_squadmsg_read_key( int k )
{
	int i, key_found, num_keys_used;

	num_keys_used = hud_squadmsg_get_total_keys();

	if ( !(Player->flags & PLAYER_FLAGS_MSG_MODE) ) {
		// check to see if any messaging keys are still down for some length of time
		// after messaging is over.  Return true for a while.
		if ( !timestamp_elapsed(Msg_eat_key_timestamp) ) {
			for (i = 0; i < num_keys_used; i++ ) {
				if ( keyd_pressed[keys_used[i]] )
					return 1;
			}
		}

		return 0;
	}

	key_found = 0;
	for (i = 0; i < num_keys_used; i++ ) {
		if ( k == keys_used[i] ) {
			if ( key_down_count(k) ) {
				Msg_key = k;
				key_found = 1;
			}

			if ( keyd_pressed[k] ) {
				key_found = 1;
			}

//			key_down_count(k);
			break;
		}
	}

	if ( key_found )
		return 1;

	return 0;
}

// function which reads the keyboard array and determines if a menu key has been hit
int hud_squadmsg_get_key()
{
	int k, i, num_keys_used;

	if ( Msg_key == -1 )
		return -1;

	k = Msg_key;
	Msg_key = -1;

	num_keys_used = hud_squadmsg_get_total_keys();

	// if the emp effect is active, never accept keypresses
	if(emp_active_local()){
		return -1;
	}

	for ( i = 0; i < num_keys_used; i++ ) {
		if ( k == keys_used[i] ) {
			Msg_key_used = 1;						// this variable will extend the timer

			// use a timestamp to prevent top level key code from possibly reprocessing this key
			Msg_eat_key_timestamp = timestamp(MSG_KEY_EAT_TIME);
			if ( k == KEY_PAGEDOWN ) {			// pageup and pagedown scroll the menu -- deal with these seperately!!
				hud_squadmsg_page_down();
				return -1;
			} else if ( k == KEY_PAGEUP ) {
				hud_squadmsg_page_up();
				return -1;
			} else if ( k == KEY_ESC ) {
				hud_squadmsg_toggle();
				return -1;
			} else if ( (i < Num_menu_items) && (Squad_msg_mode == SM_MODE_REINFORCEMENTS) )		// return any key if selecting reinforcement
				return i;

			// play general fail sound if inactive item hit.
			else if ( (i < Num_menu_items) && !(MsgItems[i].active) )
				gamesnd_play_iface(SND_GENERAL_FAIL);

			else if ( (i < Num_menu_items) && (MsgItems[i].active) )	// only return keys that are associated with menu items
				return i;

			else {
				Msg_key_used = 0;					// if no #-key pressed for visible item, break and allow timer to 
				break;								// to continue as if no key was pressed
			}
		}
	}

	return -1;
}

// function which will essentially print out the contents of the current state of the messaging
// menu.  Parameters will be a title.  The menu items and the number of items will be
// in global vars since they don't get recomputed every frame.
void hud_squadmsg_display_menu( char *title )
{
	int bx, by, sx, sy, i, nitems, none_valid, messaging_allowed;

	// hud_set_bright_color();
	hud_set_gauge_color(HUD_MESSAGE_BOX, HUD_C_BRIGHT);
	if ( title ) {
		gr_string(Mbox_title_coord[gr_screen.res][0], Mbox_title_coord[gr_screen.res][1], title);
	}

	if ( Num_menu_items < MAX_MENU_DISPLAY )
		nitems = Num_menu_items;
	else {
		if ( First_menu_item == 0 )					// First_menu_item == 0 means first page of items
			nitems = MAX_MENU_DISPLAY;
		else if ( (Num_menu_items - First_menu_item) <= MAX_MENU_DISPLAY )	// check if remaining items fit on one page
			nitems = Num_menu_items - First_menu_item;
		else {
			nitems = MAX_MENU_DISPLAY;
		}
	}

	sx = Mbox_item_coord[gr_screen.res][0];
	sy = Mbox_item_coord[gr_screen.res][1];
	bx = Mbox_bmap_coords[gr_screen.res][0];	// global x-offset where bitmap gets drawn
	by = Mbox_bmap_coords[gr_screen.res][1];		// global y-offset where bitmap gets drawn

	none_valid = 1;		// variable to tell us whether all items in the menu are valid or not

	// use another variable to tell us whether we can message or not.
	messaging_allowed = 1;

	if ( (Game_mode & GM_MULTIPLAYER) && !multi_can_message(Net_player) ){
		messaging_allowed = 0;
	}

	for ( i = 0; i < nitems; i++ ) {
		int item_num;
		char *text = MsgItems[First_menu_item+i].text;

		// blit the background
		// hud_set_default_color();
		hud_set_gauge_color(HUD_MESSAGE_BOX);
		if ( Mbox_gauge[1].first_frame >= 0 ) {
			GR_AABITMAP(Mbox_gauge[1].first_frame, bx, by);			
		}
		by += Mbox_item_h[gr_screen.res];

		// set the text color
		if ( MsgItems[First_menu_item+i].active ) {
			// hud_set_bright_color();
			hud_set_gauge_color(HUD_MESSAGE_BOX, HUD_C_BRIGHT);
		} else {
			/*
			dim_index = MIN(5, HUD_color_alpha - 2);
			if ( dim_index < 0 ) {
				dim_index = 0;
			}
			gr_set_color_fast(&HUD_color_defaults[dim_index]);
			*/

			hud_set_gauge_color(HUD_MESSAGE_BOX, HUD_C_DIM);
		}

		// first do the number
		item_num = (i+1) % MAX_MENU_DISPLAY;
		emp_hud_printf(sx, sy, EG_SQ1 + i, NOX("%1d."), item_num );		

		// then the text
		emp_hud_string(sx+Mbox_item_xoffset[gr_screen.res], sy, EG_SQ1 + i, text);		

		sy += Mbox_item_h[gr_screen.res];

		// if we have at least one item active, then set the variable so we don't display any
		// message about no active items
		if ( MsgItems[First_menu_item+i].active )
			none_valid = 0;
	}

	// maybe draw an extra line in to make room for [pgdn], or for the 'no active items'
	// display
	if ( !messaging_allowed || none_valid || ((First_menu_item + nitems) < Num_menu_items) || (Msg_shortcut_command != -1) ) {
		// blit the background
		// hud_set_default_color();
		hud_set_gauge_color(HUD_MESSAGE_BOX);
		if ( Mbox_gauge[1].first_frame >= 0 ) {

			GR_AABITMAP(Mbox_gauge[1].first_frame, bx, by);			
		}
		by += Mbox_item_h[gr_screen.res];
	}

	// draw the bottom of the frame
	// hud_set_default_color();
	hud_set_gauge_color(HUD_MESSAGE_BOX);
	if ( Mbox_gauge[2].first_frame >= 0 ) {

		GR_AABITMAP(Mbox_gauge[2].first_frame, bx, by);		
	}

	// determine if we should put the text "[more]" at top or bottom to indicate you can page up or down
	hud_targetbox_start_flash(TBOX_FLASH_SQUADMSG);
	hud_targetbox_maybe_flash(TBOX_FLASH_SQUADMSG);
	if ( First_menu_item > 0 ) {
		gr_printf( Menu_pgup_coords[gr_screen.res][0], Menu_pgup_coords[gr_screen.res][1], XSTR( "[pgup]", 312) );
	}

	if ( (First_menu_item + nitems) < Num_menu_items ) {
		gr_printf( Menu_pgdn_coords[gr_screen.res][0], Menu_pgdn_coords[gr_screen.res][1], XSTR( "[pgdn]", 313));
	}

	if ( messaging_allowed ) {
		if ( none_valid ){
			gr_printf( sx, by - Mbox_item_h[gr_screen.res] + 2, XSTR( "No valid items", 314));
		} else if ( !none_valid && (Msg_shortcut_command != -1) ){
			gr_printf( sx, by - Mbox_item_h[gr_screen.res] + 2, "%s", comm_order_get_text(Msg_shortcut_command));
		}
	} else {
		// if this player is not allowed to message, then display message saying so
		gr_printf( sx, by - Mbox_item_h[gr_screen.res] + 2, XSTR( "Not allowed to message", 315));
	}

}

// function to return true or false if the given ship can rearm, or be repaired
int hud_squadmsg_can_rearm( ship *shipp )
{
	// player ships which turns traitor cannot rearm
	if ( (shipp == Player_ship) && (Player_ship->team == Iff_traitor) )
		return 0;

	// 5/6/98 -- MWA  Decided to always be able to call in support.
	return 1;
}

// calls for repair/rearm of the player ship.  Checks for the presense of the support
// ship and does the appropriate action if found
void hud_squadmsg_repair_rearm( int toggle_state, object *objp)
{
	int robjnum;
	object *robjp;
	object *tobj;
	int multi_player_num;

	// this is essentially a check for multiplayer server/client mode
	// in multiplayer mode, the server may have to issue this command when received from a client
	if(objp == NULL) {
		tobj = Player_obj;
		multi_player_num = -1;
	} else {
		tobj = objp;
		multi_player_num = multi_find_player_by_object(objp);
		Assert(multi_player_num != -1);
	}

	// see if player is already scheduled on arriving support ship.  If so, issues appripriate
	// message and bail
	if ( is_support_allowed(tobj) ) {
		if ( mission_is_repair_scheduled( tobj ) ) {
			message_send_builtin_to_player( MESSAGE_REARM_ON_WAY, NULL, MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, -1 );
		} else {
			robjnum = hud_support_find_closest(OBJ_INDEX(tobj));
			if ( robjnum != -1 ) {
				message_send_builtin_to_player( MESSAGE_REARM_ON_WAY, &Ships[Objects[robjnum].instance], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, -1 );
			} else {
				// request a rearm.  Next function returns -1 if ship is warping in, objnum of repair ship otherwise
				robjnum = ai_issue_rearm_request( tobj );
				if ( robjnum != -1) {
					robjp = &Objects[robjnum];
					message_send_builtin_to_player( MESSAGE_ON_WAY, &Ships[robjp->instance], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, -1 );

				} else {
					// if we are in this part of the if statment, a support ship has been warped in to
					// service us.  Issue appropriate message
					message_send_builtin_to_player( MESSAGE_REARM_WARP, NULL, MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_SOON, 0, 0, multi_player_num, -1 );
				}

				mission_log_add_entry(LOG_PLAYER_CALLED_FOR_REARM, Ships[tobj->instance].ship_name, NULL);
			}
		}
	}

	//if ( multi_player_num == -1 )		// only do the hud display if it is for me!
	//	hud_support_view_start();

	if ( toggle_state )
		hud_squadmsg_toggle();						// take us out of message mode
}

// function which gets called from keyboard code to issues a shortcut command for rearming.
void hud_squadmsg_rearm_shortcut()
{
	if ( !hud_squadmsg_can_rearm(Player_ship) )
		return;

	// multiplayer clients need to send this message to the server
	if ( MULTIPLAYER_CLIENT ) {
		send_player_order_packet(SQUAD_MSG_SHIP, 0, REARM_REPAIR_ME_ITEM);
		return;
	}

	hud_squadmsg_repair_rearm(0);
}

// code which is called when a player aborts his rearm request
void hud_squadmsg_repair_rearm_abort( int toggle_state, object *obj)
{
//	ai_info *aip;
//	object *robjp;
	object *tobj;

	// this is essentially a check for multiplayer server/client mode
	// in multiplayer mode, the server may have to issue this command when received from a client
	if(obj == NULL)
		tobj = Player_obj;
	else
		tobj = obj;

	// try to abort the request.  We shoudln't be in this function unless we are actually
	// queued for repair.  Send a message from support ship if the support ship is in the mission
	ai_abort_rearm_request( tobj );

	// move the next statements outside of the above if-statement.  Seems like this place
	// is the right place, since we want to change state of the messaging system regardless
	// of what happened above.
	if ( toggle_state )
		hud_squadmsg_toggle();						// take us out of message mode
}

// Goober5000 - redone and added a bit
// returns 1 if an order is valid for a ship.  Applies to things like departure when engines are blown, etc.
int hud_squadmsg_ship_order_valid( int shipnum, int order )
{
	// Goober5000
	Assert( shipnum >= 0 && shipnum < MAX_SHIPS );

	switch ( order  )
	{
		case DEPART_ITEM:
			// disabled ships can't depart.
			if (Ships[shipnum].flags & SF_DISABLED)
				return 0;

			// Goober5000: also can't depart if no subspace drives and no capships in the area
			if (Ships[shipnum].flags2 & SF2_NO_SUBSPACE_DRIVE)
			{
				// locate a capital ship on the same team:
				if (ship_get_ship_with_dock_bay(Ships[shipnum].team) < 0)
					return 0;
			}

			break;
	}
	return 1;
}

// returns true or false if the Players target is valid for the given order
// find_order is true when we need to search the comm_orders array for the order entry.  We have
// to do this action in some cases since all we know is the actual "value" of the order
int hud_squadmsg_is_target_order_valid(int order, int find_order, ai_info *aip )
{
	int target_objnum, i;
	ship *shipp, *ordering_shipp;
	object *objp;

	if ( aip == NULL )
		aip = Player_ai;

	// find the comm_menu item for this command
	if ( find_order ) {
		for (i = 0; i < NUM_COMM_ORDER_ITEMS; i++ ) {
			if ( Comm_orders[i].item == order )
				break;
		}
		Assert( i < NUM_COMM_ORDER_ITEMS );
		order = i;
	}

	// orders which don't operate on targets are always valid
	if ( !(Comm_orders[order].item & TARGET_MESSAGES) )
		return 1;

	target_objnum = aip->target_objnum;

	// order isn't valid if there is no player target
	if ( target_objnum == -1 ) {
		return 0;
	}

	objp = &Objects[target_objnum];

	ordering_shipp = &Ships[aip->shipnum];

	// target isn't a ship, then return 0
	if ( (objp->type != OBJ_SHIP) && (objp->type != OBJ_WEAPON) )
		return 0;

	// if it's a weapon, then it needs to be a WIF_BOMB weapon.  Only attack order valid, and only
	// valid on bombs not on the player's team
	if ( objp->type == OBJ_WEAPON ) {
		
		if (Weapons[objp->instance].lssm_stage==3){
			return 0;
		}
		
		if ( (Comm_orders[order].item == ATTACK_TARGET_ITEM )
			&& (Weapon_info[Weapons[objp->instance].weapon_info_index].wi_flags & WIF_BOMB)
			&& (Weapons[objp->instance].team != ordering_shipp->team) )

			return 1;

		return 0;
	}

	Assert( objp->type == OBJ_SHIP );

	shipp = &Ships[objp->instance];

	// if target is a navbouy, return 0
	if ( Ship_info[shipp->ship_info_index].flags & SIF_NAVBUOY ){
		return 0;
	}

	// if we are messaging a ship, and that ship is our target, no target type orders are ever active
	if ( (Squad_msg_mode == SM_MODE_SHIP_COMMAND) && (target_objnum == Msg_instance) ){
		return 0;
	}

	// if the order is a disable order or depart, and the ship is disabled, order isn't active
	if ( (Comm_orders[order].item == DISABLE_TARGET_ITEM) && (shipp->flags & SF_DISABLED) ){
		return 0;
	}

	// same as above except for disabled.
	if ( (Comm_orders[order].item == DISARM_TARGET_ITEM) && ((shipp->subsys_info[SUBSYSTEM_TURRET].num == 0) || (shipp->subsys_info[SUBSYSTEM_TURRET].current_hits == 0.0f)) ){
		return 0;
	}

	// if order is disable subsystem, and no subsystem targeted or no hits, then order not valid
	if ( (Comm_orders[order].item == DISABLE_SUBSYSTEM_ITEM) && ((aip->targeted_subsys == NULL) || (aip->targeted_subsys->current_hits <= 0.0f)) ){
		return 0;
	}

	// check based on target's and player's team
	if ( (shipp->team == ordering_shipp->team) && (FRIENDLY_TARGET_MESSAGES & Comm_orders[order].item) ){
		return 1;
	} else if ( (shipp->team != ordering_shipp->team) && (ENEMY_TARGET_MESSAGES & Comm_orders[order].item) ){
		return 1;
	} else {
		return 0;
	}
}

// function to send an order to all fighters/bombers.
void hud_squadmsg_send_to_all_fighters( int command, int player_num )
{
	ai_info *aip;
	ship *shipp, *ordering_shipp;
	int i, send_message;//, do_ship = 0;
	object *objp;

	// quick short circuit here because of actually showing comm menu even though you cannot message.
	// just a safety net.
	if ( (Game_mode & GM_MULTIPLAYER) && (player_num != -1) ) {
		if ( !multi_can_message(&Net_players[player_num]) ) {
			return;
		}
	}

	// check for multiplayer mode
	if((Game_mode & GM_MULTIPLAYER) && !(Net_player->flags & NETINFO_FLAG_AM_MASTER)) {
		send_player_order_packet(SQUAD_MSG_ALL, 0, command);
		return;
	}

	send_message = 1;									// internal flag to dictate who sends message
	aip = Player_ai;

	if ( player_num != -1 )
		aip = &Ai_info[Ships[Objects[Net_players[player_num].m_player->objnum].instance].ai_index];

	Assert( aip->shipnum != -1 );
	ordering_shipp = &Ships[aip->shipnum];

	/* Goober5000 - this relies on the weird calling logic that is now disabled
	if ( command == IGNORE_TARGET_ITEM ) {
		// if we were messaging a ship directly, set flag to send no messages.  We will send one
		// specifically from the ship player is ordering
		if ( (Msg_instance != MESSAGE_ALL_FIGHTERS) && (Squad_msg_mode == SM_MODE_SHIP_COMMAND) ) {
			do_ship = 1;
			send_message = 0;
		}
	}
	*/

	for ( i = 0; i < Num_wings; i++ ) {
		int shipnum;

		if ( (Wings[i].flags & WF_WING_GONE) || (Wings[i].current_count == 0) )
			continue;

		if ( Wings[i].flags & WF_WING_DEPARTING )
			continue;

		// get the first ship on the wing list and look at its team and then its type
		shipnum = Wings[i].ship_index[Wings[i].special_ship];

		// if special ship isn't valid then just move on
		if (shipnum < 0)
			continue;

		shipp = &Ships[shipnum];

		// can't message if not on players team
		if ( shipp->team != ordering_shipp->team )
			continue;

		// can't message if ship not fighter/bomber if the command isn't to everyone.
		if ( !(Ship_info[shipp->ship_info_index].flags & (SIF_FIGHTER | SIF_BOMBER)) )
			continue;

		// don't send the command if the "wing" won't accept the command.  We do this by looking at
		// the set of orders accepted for the wing leader
		if ( !(command & shipp->orders_accepted) )
			continue;

		// send the command to the wing
		if ( Wings[i].current_count > 1 ) {
			if ( hud_squadmsg_send_wing_command(i, command, send_message, player_num) ) {
				send_message = 0;
			}
		}
	}

	// now find any friendly fighter/bomber ships not in wings
	for ( objp = GET_FIRST(&obj_used_list); objp != END_OF_LIST(&obj_used_list); objp = GET_NEXT(objp) ) {
		if ( objp->type != OBJ_SHIP )
			continue;

		// don't send messge to ships not on player's team, or that are in a wing.
		shipp = &Ships[objp->instance];
		if ( (shipp->team != ordering_shipp->team) || (shipp->wingnum != -1) )
			continue;

		// don't send message to non fighter wings
		if ( !(Ship_info[shipp->ship_info_index].flags & (SIF_FIGHTER | SIF_BOMBER)) )
			continue;

		// skip departing/dying ships
		if ( shipp->flags & (SF_DEPARTING|SF_DYING) )
			continue;

		// don't send command if ship won't accept if
		if ( !(command & shipp->orders_accepted) )
			continue;

		if ( hud_squadmsg_send_ship_command(objp->instance, command, send_message, player_num) ) {
			send_message = 0;
		}
	}

	// we might send the ship command again if we are ignoring a target, and the guy
	// we ordered directly is a ship -- we want the response to come directly from the
	// guy we orders
	/* Goober5000 - yet again with the weird logic
	if ( do_ship ) {
		Assert( Msg_instance != MESSAGE_ALL_FIGHTERS );
		hud_squadmsg_send_ship_command( Msg_instance, command, 1 );
	}
	*/
}

// Check if any enemy ships are in the mission
int hud_squadmsg_enemies_present()
{
	ship		*shipp;
	ship_obj *so;

	for ( so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so) ) {
		shipp = &Ships[Objects[so->objnum].instance];
		if ( shipp->team != Player_ship->team )
			return 1;
	}

	return 0;
}

#define OVERRIDE_PROTECT_SHIP_TYPE	(SIF_FIGHTER|SIF_BOMBER|SIF_FREIGHTER|SIF_TRANSPORT)
// function which sends a message to a specific ship.  This routine can be called from one of two
// places.  Either after selecting a ship when using a hotkey, or after selecting a command when
// using the entire messaging menu system
//
// if local and addr are non-null, it means the function is being called by the (multiplayer) server in response to 
// a PLAYER_COMMAND_PACKET
int hud_squadmsg_send_ship_command( int shipnum, int command, int send_message, int player_num )
{
	ai_info *ainfo;
	int ai_mode, ai_submode;					// ai mode and submode needed for ship commands
	char *target_shipname;						// ship number of possible targets
	int message;
	int target_team, ship_team;				// team id's for the ship getting message and any target the player has
	ship *ordering_shipp;
	
	// quick short circuit here because of actually showing comm menu even though you cannot message.
	// just a safety net.
	if ( (Game_mode & GM_MULTIPLAYER) && (player_num != -1) ) {
		if ( !multi_can_message(&Net_players[player_num]) ) {
			return 0;
		}
	}

	// check for multiplayer mode
	if((Game_mode & GM_MULTIPLAYER) && !(Net_player->flags & NETINFO_FLAG_AM_MASTER)){
		send_player_order_packet(SQUAD_MSG_SHIP, shipnum, command);
		return 0;
	}

	ai_mode = AI_GOAL_NONE;							// needs to be initialized
	ai_submode = -1234567;
	ainfo = Player_ai;

	if ( player_num != -1 ){
		ainfo = &Ai_info[Ships[Objects[Net_players[player_num].m_player->objnum].instance].ai_index];
	}

	Assert( ainfo->shipnum != -1 );
	ordering_shipp = &Ships[ainfo->shipnum];

	// a shortcut to save on repetitive coding.  If the order is a 'target' order, make the default
	// mesage be "no target"
	message = MESSAGE_NOSIR;
	if ( (command & TARGET_MESSAGES) && (ainfo->target_objnum == -1) )
		message = MESSAGE_NO_TARGET;

	if ( hud_squadmsg_is_target_order_valid(command, 1, ainfo) ) {

		target_shipname = NULL;
		target_team = -1;
		if ( ainfo->target_objnum != -1) {
			if ( Objects[ainfo->target_objnum].type == OBJ_SHIP ) {
				if ( ainfo->target_objnum != Ships[shipnum].objnum ) {
					target_shipname = Ships[Objects[ainfo->target_objnum].instance].ship_name;		// I think this is right
					target_team = Ships[Objects[ainfo->target_objnum].instance].team;
				}
			}
		}

		Assert ( ainfo->shipnum != -1 );
		ship_team = Ships[ainfo->shipnum].team;		// team of the ship issuing the message

		switch ( command ) {									// value of k matches the #defines for ship messages
		case ATTACK_TARGET_ITEM:
			if ( Objects[ainfo->target_objnum].type == OBJ_SHIP ) {
				Assert( target_shipname );
				Assert( ship_team != target_team );

				// Orders to override protect
				if (Ship_info[Ships[Objects[ainfo->target_objnum].instance].ship_info_index].flags & OVERRIDE_PROTECT_SHIP_TYPE) {
					Objects[ainfo->target_objnum].flags &= ~OF_PROTECTED;
				}

				ai_mode = AI_GOAL_CHASE;
				ai_submode = SM_ATTACK;
			} else if ( Objects[ainfo->target_objnum].type == OBJ_WEAPON ) {
				ai_mode = AI_GOAL_CHASE_WEAPON;
				ai_submode = Objects[ainfo->target_objnum].instance;			// store the instance of the weapon -- ai goals code will deal with it
			} else
				Int3();
			message = MESSAGE_ATTACK_TARGET;
			break;

		case DISABLE_TARGET_ITEM:
			Assert( target_shipname );
			Assert( ship_team != target_team );

			// Orders to override protect
			if (Ship_info[Ships[Objects[ainfo->target_objnum].instance].ship_info_index].flags & OVERRIDE_PROTECT_SHIP_TYPE) {
				Objects[ainfo->target_objnum].flags &= ~OF_PROTECTED;
			}

			ai_mode = AI_GOAL_DISABLE_SHIP;
			ai_submode = -SUBSYSTEM_ENGINE;
			message = MESSAGE_DISABLE_TARGET;
			break;

		case DISARM_TARGET_ITEM:
			Assert( target_shipname );
			Assert( ship_team != target_team );

			// Orders to override protect
			if (Ship_info[Ships[Objects[ainfo->target_objnum].instance].ship_info_index].flags & OVERRIDE_PROTECT_SHIP_TYPE) {
				Objects[ainfo->target_objnum].flags &= ~OF_PROTECTED;
			}

			ai_mode = AI_GOAL_DISARM_SHIP;
			ai_submode = -SUBSYSTEM_TURRET;
			message = MESSAGE_DISARM_TARGET;
			break;

		case DISABLE_SUBSYSTEM_ITEM:
			Assert( target_shipname );
			Assert( ship_team != target_team );
			Assert( ainfo->targeted_subsys != NULL );
			Assert( ainfo->targeted_subsys->current_hits > 0.0f);

			// Orders to override protect
			if (Ship_info[Ships[Objects[ainfo->target_objnum].instance].ship_info_index].flags & OVERRIDE_PROTECT_SHIP_TYPE) {
				Objects[ainfo->target_objnum].flags &= ~OF_PROTECTED;
			}

			ai_mode = AI_GOAL_DESTROY_SUBSYSTEM;
			ai_submode = ship_get_subsys_index( &Ships[Objects[ainfo->target_objnum].instance], ainfo->targeted_subsys->system_info->subobj_name );
			message = MESSAGE_ATTACK_TARGET;
			break;

		case CAPTURE_TARGET_ITEM:
			Assert( target_shipname );
			Assert( ship_team != target_team );

			Assert(ainfo->target_objnum > -1);

			Objects[ainfo->target_objnum].flags |= OF_PROTECTED;

			ai_mode = AI_GOAL_DOCK;
			ai_submode = AIS_DOCK_0;
			message = MESSAGE_DOCK_YES;
			break;

		case PROTECT_TARGET_ITEM:

			// AL 31-3-98: Can't protect self... this can happen if all fighters
			//					are told to protect another friendly ship
			if ( ainfo->target_objnum == Ships[shipnum].objnum ) {
				return 0;
			}

			Assert( target_shipname );
			Assert( ship_team == target_team );

			ai_mode = AI_GOAL_GUARD;
			ai_submode = AIS_GUARD_PATROL;
			message = MESSAGE_YESSIR;
			break;

		case IGNORE_TARGET_ITEM:
			Assert( target_shipname );
			Assert( ship_team != target_team );

			ai_mode = AI_GOAL_IGNORE_NEW;
			ai_submode = 0;
			message = MESSAGE_YESSIR;
			break;
		
		case FORMATION_ITEM:
			message = MESSAGE_YESSIR;
			target_shipname = ordering_shipp->ship_name;
			ai_mode = AI_GOAL_FORM_ON_WING;
			ai_submode = 0;
			break;
		
		case COVER_ME_ITEM:
			ai_mode = AI_GOAL_GUARD;
			ai_submode = AIS_GUARD_PATROL;
			target_shipname = ordering_shipp->ship_name;
			message = MESSAGE_YESSIR;
			break;
		
		case ENGAGE_ENEMY_ITEM:
			ai_mode = AI_GOAL_CHASE_ANY;
			ai_submode = SM_ATTACK;
			// if no enemies present, use the affirmative, instead of engaging enemies message
			if ( hud_squadmsg_enemies_present() )
				message = MESSAGE_YESSIR;
			else
				message = MESSAGE_ENGAGE;
			target_shipname = NULL;
			break;
		
		case DEPART_ITEM:
			ai_mode = AI_GOAL_WARP;
			ai_submode = -1;
			message = MESSAGE_WARP_OUT;
			break;
		
		// the following are support ship options!!!
		case REARM_REPAIR_ME_ITEM:		
			if((Game_mode & GM_MULTIPLAYER) && (Net_player->flags & NETINFO_FLAG_AM_MASTER) && (player_num != -1) ){
				hud_squadmsg_repair_rearm(0,&Objects[Net_players[player_num].m_player->objnum]);
			} else {
				hud_squadmsg_repair_rearm(0);				// note we return right away.  repair/rearm code handles messaging, etc
			}
			return 0;
		
		case ABORT_REARM_REPAIR_ITEM:
			if((Game_mode & GM_MULTIPLAYER) && (Net_player->flags & NETINFO_FLAG_AM_MASTER) && (player_num != -1) ){
				hud_squadmsg_repair_rearm_abort(0,&Objects[Net_players[player_num].m_player->objnum]);
			} else {
				hud_squadmsg_repair_rearm_abort(0);		// note we return right away.  repair/rearm code handles messaging, etc
			}
			return 0;
		
		case STAY_NEAR_ME_ITEM:
		case STAY_NEAR_TARGET_ITEM:		// can't attack anything on same team

			// cannot stay near a hostile ship(?)
			if ( (command == STAY_NEAR_TARGET_ITEM) && (ship_team != target_team) )
				break;

			ai_mode = AI_GOAL_STAY_NEAR_SHIP;
			ai_submode = -1;
			message = MESSAGE_YESSIR;
			if ( command == STAY_NEAR_ME_ITEM )
				target_shipname = ordering_shipp->ship_name;
			break;
		
		case KEEP_SAFE_DIST_ITEM:
			ai_mode = AI_GOAL_KEEP_SAFE_DISTANCE;
			ai_submode = -1;
			message = MESSAGE_YESSIR;
			break;
		
		default:
			Int3();										// get Allender -- illegal message
			break;

		}

		// handle case of messaging one ship.  Deal with messaging all fighters next.
		if ( ai_mode != AI_GOAL_NONE ) {
			Assert(ai_submode != -1234567);
			ai_add_ship_goal_player( AIG_TYPE_PLAYER_SHIP, ai_mode, ai_submode, target_shipname, &Ai_info[Ships[shipnum].ai_index] );
			if( player_num == -1 )
				hud_add_issued_order(Ships[shipnum].ship_name, command, target_shipname);
		}
	}

	// if we're in multiplayer mode, and we're the server, determine if this virtual squadmate order should be
	// sent to other players in the game as an actual "order"
	if((Game_mode & GM_MULTIPLAYER) && (message != MESSAGE_NOSIR)){
		// if the multi_msg system processed and sent this order to a player, we should not play a response
		if(multi_msg_eval_ship_squadmsg(shipnum,command,ainfo,player_num)){
			send_message = 0;
		}
	}
	
	// this is the _response_
	if ( send_message && (!(Ships[shipnum].flags2 & SF2_NO_BUILTIN_MESSAGES)))
	{
		message_send_builtin_to_player( message, &Ships[shipnum], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_ANYTIME, 0, 0, player_num, -1 );	
	}
	
	return send_message;
}

// function to send a command to a wing.  Like above function, called from one of two places
//
// if local and addr are non-null, it means the function is being called by the (multiplayer) server in response to 
// a PLAYER_COMMAND_PACKET
//
// returns whether or not a message was sent
int hud_squadmsg_send_wing_command( int wingnum, int command, int send_message, int player_num )
{
	ai_info *ainfo;
	int ai_mode, ai_submode;					// ai mode and submode needed for ship commands
	char *target_shipname;						// ship number of possible targets
	int message_sent, message;
	int target_team, wing_team;				// team for the wing and the player's target
	ship *ordering_shipp;

	// quick short circuit here because of actually showing comm menu even though you cannot message.
	// just a safety net.
	if ( (Game_mode & GM_MULTIPLAYER) && (player_num != -1) ) {
		if ( !multi_can_message(&Net_players[player_num]) ) {
			return 0;
		}
	}

	// check for multiplayer mode
	if((Game_mode & GM_MULTIPLAYER) && !(Net_player->flags & NETINFO_FLAG_AM_MASTER)){
		send_player_order_packet(SQUAD_MSG_WING, wingnum,command);
		return 0;
	}

	ai_mode = AI_GOAL_NONE;							// needs to be initialized
	ai_submode = -1234567;
	ainfo = Player_ai;

	if ( player_num != -1 )
		ainfo = &Ai_info[Ships[Objects[Net_players[player_num].m_player->objnum].instance].ai_index];

	Assert( ainfo->shipnum != -1 );
	ordering_shipp = &Ships[ainfo->shipnum];

	// get the shipnum of the ship the player has targeted.  Used in enough places to do this just
	// once.  If the ship targeted is part of the wing that was messages -- bail out!!!

	// a shortcut to save on repetative coding
	message = MESSAGE_NOSIR;
	if ( (command & TARGET_MESSAGES) && (ainfo->target_objnum == -1) )
		message = MESSAGE_NO_TARGET;

	if ( hud_squadmsg_is_target_order_valid(command, 1, ainfo) ) {

		target_shipname = NULL;
		target_team = -1;
		if ( ainfo->target_objnum != -1) {
			if ( Objects[ainfo->target_objnum].type == OBJ_SHIP ) {
				target_shipname = Ships[Objects[ainfo->target_objnum].instance].ship_name;		// I think this is right
				target_team = Ships[Objects[ainfo->target_objnum].instance].team;
			}
		}

		Assert ( ainfo->shipnum != -1 );
		Assert ( (wingnum >= 0) && (wingnum < Num_wings) );

		// get the team for the wing
		Assert ( Wings[wingnum].ship_index[0] != -1 );
		wing_team = Ships[Wings[wingnum].ship_index[0]].team;

		switch ( command ) {									// value of k matches the #defines for ship messages
		case ATTACK_TARGET_ITEM:
			if ( Objects[ainfo->target_objnum].type == OBJ_SHIP ) {
				Assert( target_shipname );
				Assert( wing_team != target_team );
				if ( (Ships[Objects[ainfo->target_objnum].instance].wingnum != -1) && (Ships[Objects[ainfo->target_objnum].instance].wingnum == wingnum) ) {
					message = MESSAGE_NOSIR;
					ai_mode = AI_GOAL_NONE;
				} else {
					ai_mode = AI_GOAL_CHASE;
					ai_submode = SM_ATTACK;
					message = MESSAGE_ATTACK_TARGET;
				}
			} else if ( Objects[ainfo->target_objnum].type == OBJ_WEAPON ) {
				ai_mode = AI_GOAL_CHASE_WEAPON;
				ai_submode = Objects[ainfo->target_objnum].instance;			// store the instance of the weapon -- ai goals code will deal with it
				message = MESSAGE_ATTACK_TARGET;
			} else
				Int3();

			break;

		case DISABLE_TARGET_ITEM:
			Assert( target_shipname );
			Assert( wing_team != target_team );

			ai_mode = AI_GOAL_DISABLE_SHIP;
			ai_submode = -SUBSYSTEM_ENGINE;
			message = MESSAGE_DISABLE_TARGET;
			break;

		case DISARM_TARGET_ITEM:
			Assert( target_shipname );
			Assert( wing_team != target_team );

			ai_mode = AI_GOAL_DISARM_SHIP;
			ai_submode = -SUBSYSTEM_TURRET;
			message = MESSAGE_DISARM_TARGET;
			break;

		case DISABLE_SUBSYSTEM_ITEM:
			Assert( target_shipname );
			Assert( wing_team != target_team );
			Assert( ainfo->targeted_subsys != NULL );
			Assert( ainfo->targeted_subsys->current_hits > 0.0f);

			ai_mode = AI_GOAL_DESTROY_SUBSYSTEM;
			ai_submode = ship_get_subsys_index( &Ships[Objects[ainfo->target_objnum].instance], ainfo->targeted_subsys->system_info->subobj_name );
			message = MESSAGE_ATTACK_TARGET;
			break;


		case PROTECT_TARGET_ITEM:
			Assert( target_shipname );
			Assert( wing_team == target_team );

			ai_mode = AI_GOAL_GUARD;
			ai_submode = AIS_GUARD_PATROL;
			message = MESSAGE_YESSIR;
			break;

		case IGNORE_TARGET_ITEM:
			Assert( target_shipname );
			Assert( wing_team != target_team );

			ai_mode = AI_GOAL_IGNORE_NEW;
			ai_submode = 0;	//	actually, a don't care.
			message = MESSAGE_YESSIR;
			break;

		case FORMATION_ITEM:
			message = MESSAGE_YESSIR;
			target_shipname = ordering_shipp->ship_name;
			ai_mode = AI_GOAL_FORM_ON_WING;
			ai_submode = 0;
			break;

		case COVER_ME_ITEM:
			ai_mode = AI_GOAL_GUARD;
			ai_submode = AIS_GUARD_PATROL;
			target_shipname = ordering_shipp->ship_name;
			message = MESSAGE_YESSIR;
			break;

		case ENGAGE_ENEMY_ITEM:
			ai_mode = AI_GOAL_CHASE_ANY;
			ai_submode = SM_ATTACK;
			if ( hud_squadmsg_enemies_present() )
				message = MESSAGE_YESSIR;
			else
				message = MESSAGE_ENGAGE;
			target_shipname = NULL;
			break;

		case DEPART_ITEM:
			ai_mode = AI_GOAL_WARP;
			ai_submode = -1;
			message = MESSAGE_WARP_OUT;
			Wings[wingnum].flags |= WF_DEPARTURE_ORDERED;
			break;

		case REARM_REPAIR_ME_ITEM:
		case ABORT_REARM_REPAIR_ITEM:
		case STAY_NEAR_ME_ITEM:
		case STAY_NEAR_TARGET_ITEM:
		case KEEP_SAFE_DIST_ITEM:
			return 0;

		default:
			Int3();										// get Allender -- illegal message
			break;

		}

		if ( ai_mode != AI_GOAL_NONE ) {
			Assert(ai_submode != -1234567);
			ai_add_wing_goal_player( AIG_TYPE_PLAYER_WING, ai_mode, ai_submode, target_shipname, wingnum );
		}
	}

	// if we're in multiplayer mode, and we're the server, determine if this virtual squadmate order should be
	// sent to other players in the game as an actual "order"
	if((Game_mode & GM_MULTIPLAYER) && (message != MESSAGE_NOSIR)){
		// if there's at least one ai ship which got the command, let the response come through
		if(multi_msg_eval_wing_squadmsg(wingnum,command,ainfo,player_num)){
			send_message = 0;
		}
	}

	// this is the _response_
	message_sent = 0;
	if ( send_message ) {
		int ship_num;

		// get a random ship in the wing to send the message to the player		
		ship_num = ship_get_random_ship_in_wing( wingnum, SHIP_GET_UNSILENCED );
		
		// in multiplayer, its possible that all ships in a wing are players. so we'll just send from a random ship		
		if(ship_num == -1 && (Game_mode & GM_MULTIPLAYER)){
			ship_num = ship_get_random_ship_in_wing(wingnum);
		}
		
		// only send message if ship is found.  There appear to be cases where all ships
		// in a wing die in the same frame causing the wing to appear valid in the message
		// menu, but the get_random_ship* functions won't return dying ships.
		// Karajorma - No valid ships will be found if all the remaining ships have been silence either. 
		if ( ship_num != -1 ) {
			message_send_builtin_to_player( message, &Ships[ship_num], MESSAGE_PRIORITY_NORMAL, MESSAGE_TIME_ANYTIME, 0, 0, player_num, -1 );
			message_sent = 1;
		}
	}

	return message_sent;
}


// return number of available reinforcements, 0 if none available
int hud_squadmsg_reinforcements_available(int team)
{
	int i, count = 0;

	for (i = 0; i < Num_reinforcements; i++) {
		int wingnum;

		// no more left
		if ( Reinforcements[i].num_uses >= Reinforcements[i].uses ){
			continue;
		}

		// incorrect team
		if ( team != ship_get_reinforcement_team(i) ){
			continue;
		}

		//  check the arrival cue sexpression of the ship/wing of this reinforcement.
		// Goober5000 - if it can't arrive, it doesn't count.  This should check
		// for SEXP_FALSE as well as SEXP_KNOWN_FALSE, otherwise you end up with
		// a reinforcement menu containing no valid selections.
		if ( (wingnum = wing_name_lookup(Reinforcements[i].name, 1)) != -1 ) {
			Assert ( Wings[wingnum].arrival_cue >= 0 );
			if ( Sexp_nodes[Wings[wingnum].arrival_cue].value == SEXP_FALSE
				|| Sexp_nodes[Wings[wingnum].arrival_cue].value == SEXP_KNOWN_FALSE ){
				continue;
			}
		} else {
			p_object *p_objp;

			p_objp = mission_parse_get_arrival_ship( Reinforcements[i].name );
			if ( p_objp != NULL ) {
				if ( Sexp_nodes[p_objp->arrival_cue].value == SEXP_FALSE
					|| Sexp_nodes[p_objp->arrival_cue].value == SEXP_KNOWN_FALSE ){
					continue;
				}
			} else {
				Int3();							// allender says bogus!  reinforcement should be here since it wasn't a wing!
				continue;
			}
		}
		count++;
	}

	return count;
}

// function to put up window in upper right to allow for player to select the type
// of entity to select for a message (i.e. a wing or a ship)
void hud_squadmsg_type_select( )
{
	int k, i;

	First_menu_item = 0;	

	// Add the items
	for (i = 0; i < NUM_COMM_ORDER_TYPES; i++)
	{
		strcpy(MsgItems[i].text, Comm_order_types[i]);
		MsgItems[i].active = 1;						// assume active
	}
	Num_menu_items = NUM_COMM_ORDER_TYPES;


	// check to see if the player is a traitor.  If so, then he will not
	// be able to do anything from this menu
	if ( Player_ship->team == Iff_traitor ) {
		for (i = 0; i < MAX_MENU_ITEMS; i++ )
			MsgItems[i].active = 0;
		goto do_main_menu;
	}

	// based on ship counts, wing counts, shortcut active, grey out possible menu choices
	if ( !hud_squadmsg_count_ships(0) )
		MsgItems[TYPE_SHIP_ITEM].active = 0;

	if ( !hud_squadmsg_count_wings(0) )
		MsgItems[TYPE_WING_ITEM].active = 0;

	// check to be sure that we have some fighters/bombers on the players team that we
	// can message
	if ( !hud_squadmsg_exist_fighters() ){
		MsgItems[TYPE_ALL_FIGHTERS_ITEM].active = 0;
	}

	if ((Player_ship != NULL) && !hud_squadmsg_reinforcements_available(Player_ship->team)) {
		MsgItems[TYPE_REINFORCEMENT_ITEM].active = 0;
	}

	MsgItems[TYPE_REPAIR_REARM_ITEM].active = 1;				// this item will always be available (I think)
	MsgItems[TYPE_REPAIR_REARM_ABORT_ITEM].active = 0;

	// AL: 10/13/97
	// If the player ship communications are severely damaged, then the player
	// will only be able to call for repair/rearm ships
	//
	// also, only allow support ship if this player is not allowed to messaage. 
	if ( (hud_communications_state(Player_ship) != COMM_OK) || ((Game_mode & GM_MULTIPLAYER) && !multi_can_message(Net_player)) ) {
		for ( i = 0; i < MAX_MENU_ITEMS; i++ ){
			MsgItems[i].active = 0;
		}

		MsgItems[TYPE_REPAIR_REARM_ITEM].active = 1;
	}

	// check to see if the player is awaiting repair or being repaired.  Active the abort and inactive the repair items
	// check to see if the player is scheduled to be repaired by incoming ship
	if ( Ai_info[Ships[Player_obj->instance].ai_index].ai_flags & (AIF_AWAITING_REPAIR | AIF_BEING_REPAIRED) ) {
		MsgItems[TYPE_REPAIR_REARM_ITEM].active = 0;
		MsgItems[TYPE_REPAIR_REARM_ABORT_ITEM].active = 1;
	} else if ( mission_is_repair_scheduled(Player_obj) ) {
		MsgItems[TYPE_REPAIR_REARM_ITEM].active = 0;
		MsgItems[TYPE_REPAIR_REARM_ABORT_ITEM].active = 1;
	}

	// if no support available, can't call one in
	if ( !is_support_allowed(Player_obj) ) {
		MsgItems[TYPE_REPAIR_REARM_ITEM].active = 0;
		MsgItems[TYPE_REPAIR_REARM_ABORT_ITEM].active = 0;
	}

	// de-activate the rearm/repair item if the player has a full load of missiles and
	// all subsystems at full strength.  We will only check if this item hasn't been marked
	// inactive because of some other reason
	if ( MsgItems[TYPE_REPAIR_REARM_ITEM].active ) {

		if ( !hud_squadmsg_can_rearm(Player_ship) ){
			MsgItems[TYPE_REPAIR_REARM_ITEM].active = 0;
		}
	}

	// if using keyboard shortcut, these items are always inactive
	if ( Msg_shortcut_command != -1 ) {
		MsgItems[TYPE_REPAIR_REARM_ITEM].active = 0;
		MsgItems[TYPE_REINFORCEMENT_ITEM].active = 0;
		MsgItems[TYPE_REPAIR_REARM_ABORT_ITEM].active = 0;
	}

do_main_menu:
	hud_squadmsg_display_menu( XSTR( "Message What", 316) );
	k = hud_squadmsg_get_key();
	if ( k != -1 ) {							// when k != -1, we have a key that associates with menu item
		Assert ( k < Num_menu_items );
		if ( k == TYPE_SHIP_ITEM ){
			hud_squadmsg_do_mode( SM_MODE_SHIP_SELECT );
		} else if ( k == TYPE_WING_ITEM ) {
			hud_squadmsg_do_mode( SM_MODE_WING_SELECT );
		} else if ( k == TYPE_ALL_FIGHTERS_ITEM ) {
			hud_squadmsg_do_mode( SM_MODE_ALL_FIGHTERS );
		}
		
		if ( Msg_shortcut_command == -1 ) {
			if ( k == TYPE_REINFORCEMENT_ITEM ) {
				hud_squadmsg_do_mode( SM_MODE_REINFORCEMENTS );
				player_set_next_all_alone_msg_timestamp();
			} else if ( k == TYPE_REPAIR_REARM_ITEM ){
				hud_squadmsg_do_mode( SM_MODE_REPAIR_REARM );
			} else if ( k == TYPE_REPAIR_REARM_ABORT_ITEM ) {
				hud_squadmsg_do_mode( SM_MODE_REPAIR_REARM_ABORT );
			}
		}
	}
}

// function to display a list of ships to send a command to
void hud_squadmsg_ship_select()
{
	int k;

	if ( Num_menu_items == -1 ) {
		Num_menu_items = 0;
		hud_squadmsg_count_ships( 1 );
	}

	hud_squadmsg_display_menu( XSTR( "Select Ship", 317) );
	k = hud_squadmsg_get_key();
	if ( k != -1 ) {						// if true, we have selected a ship.
		if ( Msg_shortcut_command == -1 ) {
			Msg_instance = MsgItems[First_menu_item + k].instance;		// store the instance id in a global
			hud_squadmsg_do_mode( SM_MODE_SHIP_COMMAND );				// and move to a new mode
		} else {
			// we must convert the Msg_shortcut_command value to a value that the message
			// system normally uses to select a command.  Since the menu 
			//Assert( Msg_shortcut_command != IGNORE_TARGET_ITEM );
			hud_squadmsg_send_ship_command( MsgItems[First_menu_item+k].instance, Msg_shortcut_command, 1 );
			hud_squadmsg_toggle();
		}
	}

}

// function to display a list of wings to send a command to
void hud_squadmsg_wing_select()
{
	int k;

	if ( Num_menu_items == -1 ) {
		Num_menu_items = 0;
		hud_squadmsg_count_wings( 1 );
	}

	hud_squadmsg_display_menu( XSTR( "Select Wing", 318) );
	k = hud_squadmsg_get_key();
	if ( k != -1 ) {						// if true, we have selected a ship.
		if ( Msg_shortcut_command == -1 ) {									// do normal menu stuff when no hoykey active
			Msg_instance = MsgItems[First_menu_item + k].instance;	// store the instance id in a global
			hud_squadmsg_do_mode( SM_MODE_WING_COMMAND );				// and move to a new mode
		} else {
			//Assert( Msg_shortcut_command != IGNORE_TARGET_ITEM );
			hud_squadmsg_send_wing_command( MsgItems[First_menu_item+k].instance, Msg_shortcut_command, 1 );
			hud_squadmsg_toggle();
		}
	}

}

// code which gives an order to all fighters/bombers.  If there is a message shortcut active, then
// make that order apply to all fighters/bombers.  Otherwise, move to the ship_command menu
void hud_squadmsg_msg_all_fighters()
{
	if ( Msg_shortcut_command == -1 ) {
		Msg_instance = MESSAGE_ALL_FIGHTERS;
		hud_squadmsg_do_mode( SM_MODE_SHIP_COMMAND );
	} else {
		hud_squadmsg_send_to_all_fighters( Msg_shortcut_command );
		hud_squadmsg_toggle();
	}
}

// called to actually bring in a reinforcement.  For single player games, always gets called.
// for multiplayer games, always called on the server side.  Clients should never get here
void hud_squadmsg_call_reinforcement(int reinforcement_num, int player_num)
{
	int i, delay;
	reinforcements *rp;
	p_object *p_objp;

	rp = &Reinforcements[reinforcement_num];

	// safety net mainly for multiplayer servers in case some odd data desync occurs between 
	// server and clients
	if ( MULTIPLAYER_MASTER && (rp->num_uses == rp->uses) ) {
		return;
	}

	// check to see if the reinforcement called was a wing.
	for (i = 0; i < Num_wings; i++ ) {
		if ( !stricmp(rp->name, Wings[i].name) ) {
			// found a wingname.  Call the parse function to create all the ships in this wing
			// we must set the arrival cue of the wing to true, otherwise, this won't work!!
			Wings[i].flags &= ~WF_REINFORCEMENT;
			Wings[i].flags |= WF_RESET_REINFORCEMENT;

			// set up the arrival delay.  If it is 0, then make is some random number of seconds
			delay = rp->arrival_delay;
			if ( delay == 0 )
				delay = (int)(frand() * 3.0) + 3;
			Wings[i].arrival_delay = timestamp(delay * 1000);
			break;
		}
	}

	// if we found no wing name that matched the reinforcement name, then look for a ship
	// of the same name
	if ( i == Num_wings ) {
		p_objp = mission_parse_get_arrival_ship( rp->name );
		if ( p_objp ) {
			// by resetting the reinforcement flag, we will allow code which normally handles arrivals
			// to make this reinforcement arrive.  Doing so keeps the data structures clean.
			p_objp->flags &= ~P_SF_REINFORCEMENT;

			// set up the arrival delay
			delay = rp->arrival_delay;
			if ( delay == 0 )
				delay = (int)(frand() * 3.0) + 3;		// between 3 and 6 seconds to arrive
			p_objp->arrival_delay = timestamp(delay * 1000);
		} else {
			Int3();				// get allender -- I don't think that this can happen!!!!
			return;
		}
	}

	// increment the number of times this is used.  Incremented here on single player and multiplayer
	// server side only.  Clients keep track of own count when they actually call something in.
	rp->num_uses++;

	// commented out on 9/9/98 because these messages simply are not used
	/*
	// now play a message (if there is one to play) for this reinforcement arrival.  The first for loop
	// determine how many messages there are to play, since the array is packet.  Then, if >= 1 message
	// to play, play one
	for (i = 0; i < MAX_REINFORCEMENT_MESSAGES; i++ )
		if ( !strlen(rp->yes_messages[i]) )
			break;

	//if ( i > 0 )
	//	message_send_to_player( rp->yes_messages[myrand() % i], rp->name, MESSAGE_PRIORITY_NORMAL, HUD_SOURCE_FRIENDLY );
	*/

	mission_log_add_entry(LOG_PLAYER_CALLED_FOR_REINFORCEMENT, rp->name, NULL);
}

// function to display a list of reinforcements available to the player
void hud_squadmsg_reinforcement_select()
{
	int i, k;
	reinforcements *rp;

	if ( Num_menu_items == -1 ) {
		Num_menu_items = 0;
		for (i = 0; i < Num_reinforcements; i++) {
			rp = &Reinforcements[i];

			// don't put reinforcements onto the list that have already been used up.
			if ( (rp->num_uses == rp->uses) ){
				continue;
			}

			// don't put items which are not on my team
			if((Player_ship != NULL) && (ship_get_reinforcement_team(i) != Player_ship->team)){
				continue;
			} 

			Assert ( Num_menu_items < MAX_MENU_ITEMS );
			strcpy( MsgItems[Num_menu_items].text, rp->name );
			MsgItems[Num_menu_items].instance = i;
			MsgItems[Num_menu_items].active = 0;

			if ( rp->flags & RF_IS_AVAILABLE ) {
				MsgItems[Num_menu_items].active = 1;
			}

			Num_menu_items++;
		}
	}

//	hud_squadmsg_display_menu( "Select Reinforcement" );
	hud_squadmsg_display_menu( XSTR( "Select Ship/Wing", 319) );	// AL 11-14-97: Reinforcement didn't fit, so using this for now
	k = hud_squadmsg_get_key();
	if (k != -1) {
		int rnum;

		hud_squadmsg_toggle();						// take us out of message mode

		rnum = MsgItems[First_menu_item + k].instance;

		// check to see if trying to call a reinforcement not yet available.  If so, maybe play message, but
		// definately bail
		if ( MsgItems[First_menu_item + k].active == 0 ) {						
			return;
		}

		// in single player, or a multiplayer master, call in the reinforcement.  Clients send a packet to the
		// server
		if ( MULTIPLAYER_CLIENT ) {
			Reinforcements[rnum].num_uses++;			// increment this variable here since clients need to maintain a valid count
			send_player_order_packet(SQUAD_MSG_REINFORCEMENT, rnum, 0);
		} else {
			hud_squadmsg_call_reinforcement(rnum);
		}
	}
}

// function to display list of commands for a ship

void hud_squadmsg_ship_command()
{
	int k;
	int i, orders, default_orders;

	// when adding ship commands, we must look at the type of ship, and what messages that
	// ship allows.  First, place all messages that are possible onto the menu, then 

	// see if messaging all ships or just one.  Messaging all ships will mean all default orders
	// show on comm menu.
	if ( Msg_instance != MESSAGE_ALL_FIGHTERS ) {
		orders = Ships[Msg_instance].orders_accepted;
		default_orders = ship_get_default_orders_accepted( &Ship_info[Ships[Msg_instance].ship_info_index] );
	} else {

		default_orders = DEFAULT_MESSAGES;
		orders = default_orders;
	}

	First_menu_item = 0;
	Num_menu_items = 0;
	for ( i = 0; i < NUM_COMM_ORDER_ITEMS; i++ ) {
		// check to see if the comm order should even be added to the menu -- if so, then add it
		// the order will be activated if the bit is set for the ship.
		if ( default_orders & Comm_orders[i].item ) {
			Assert ( Num_menu_items < MAX_MENU_ITEMS );
			strcpy(MsgItems[Num_menu_items].text, Comm_orders[i].name);
			MsgItems[Num_menu_items].instance = Comm_orders[i].item;
			MsgItems[Num_menu_items].active = 0;
			// check the bit to see if the command is active
			if ( orders & Comm_orders[i].item )
				MsgItems[Num_menu_items].active = 1;

			// if the order cannot be carried out by the ship, then item should be inactive
			if ( (Msg_instance != MESSAGE_ALL_FIGHTERS) && !hud_squadmsg_ship_order_valid( Msg_instance, Comm_orders[i].item ) )
				MsgItems[Num_menu_items].active = 0;

			// do some other checks to possibly gray out other items.
			// if no target, remove any items which are associated with the players target
			if ( !hud_squadmsg_is_target_order_valid(i, 0) )
				MsgItems[Num_menu_items].active = 0;

			// if messaging all fighters, see if we should gray out the order if no one will accept it,
			// or modify the text if only some of the ships will accept it
			if ( Msg_instance == MESSAGE_ALL_FIGHTERS ) {
				ship_obj *so;
				ship *shipp;
				int partial_accept, all_accept;			// value which tells us what to do with menu item

				all_accept = Comm_orders[i].item;
				partial_accept = 0;
				for ( so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so) ) {

					// don't send messge to ships not on player's team, or that are in a wing.
					shipp = &Ships[Objects[so->objnum].instance];
					if ( shipp->team != Player_ship->team )
						continue;

					// don't send message to non fighter wings
					if ( !(Ship_info[shipp->ship_info_index].flags & (SIF_FIGHTER | SIF_BOMBER)) )
						continue;

					all_accept &= shipp->orders_accepted;		// 'and'ing will either keep this bit set or zero it properly
					partial_accept |= (shipp->orders_accepted & Comm_orders[i].item);	// 'or'ing will tell us if at least one accepts
				}

				if ( !all_accept ) {
					// either modify the text if a partial accept, or grey it out if no one accepts
					if ( partial_accept ) {
						strcat( MsgItems[Num_menu_items].text, XSTR( "(*)", 320) );
					} else {
						MsgItems[Num_menu_items].active = 0;
					}
				}
			}

			Num_menu_items++;
		}
	}

	hud_squadmsg_display_menu( XSTR( "What Command", 321) );
	k = hud_squadmsg_get_key();

	// when we get a valid goal, we must add the goal to the ai ship's goal list

	if ( k != -1 ) {
		Assert ( k < Num_menu_items );
		// when messaging all fighters or ignoring target, call the send_to_all_fighters routine
		// Goober5000 - ignore no longer sends to all fighters
		if ((Msg_instance == MESSAGE_ALL_FIGHTERS)/* || (MsgItems[k].instance == IGNORE_TARGET_ITEM)*/)
			hud_squadmsg_send_to_all_fighters(MsgItems[k].instance);
		else
			hud_squadmsg_send_ship_command(Msg_instance, MsgItems[k].instance, 1);

		hud_squadmsg_toggle();
	}
}

// function to display list of command for a wing
void hud_squadmsg_wing_command()
{
	int k;
	wing *wingp;
	int default_orders, i, orders;

	// when adding commands for wings, we will look at all of the ships in the wing, and create
	// the order list from that set of ships.  In the future, we may want to do something else....

	wingp = &Wings[Msg_instance];

	// or together all of the orders for all the ships in the wing
	default_orders = 0;
	for ( i = 0; i < wingp->current_count; i++ ) {
		orders = ship_get_default_orders_accepted( &Ship_info[Ships[wingp->ship_index[i]].ship_info_index] );
		default_orders |= orders;
	}
	default_orders &= ~CAPTURE_TARGET_ITEM;		// we cannot capture any target with a wing.

	Num_menu_items = 0;
	orders = Ships[wingp->ship_index[0]].orders_accepted;		// get the orders that the first ship in the wing will accept
	for ( i = 0; i < NUM_COMM_ORDER_ITEMS; i++ ) {
		// add the set of default orders to the comm menu.  We will currently allow all messages
		// to be available in the wing.
		if ( default_orders & Comm_orders[i].item ) {
			Assert ( Num_menu_items < MAX_MENU_ITEMS );
			strcpy(MsgItems[Num_menu_items].text, Comm_orders[i].name);
			MsgItems[Num_menu_items].instance = Comm_orders[i].item;
			MsgItems[Num_menu_items].active = 0;

			// possibly grey out the menu item depending on whether or not the "wing" will accept this order
			// the "wing" won't accept the order if the first ship in the wing doesn't accept it.
			if ( orders & Comm_orders[i].item )
				MsgItems[Num_menu_items].active = 1;

			// do some other checks to possibly gray out other items.
			// if no target, remove any items which are associated with the players target
			if ( !hud_squadmsg_is_target_order_valid(i, 0) )
				MsgItems[Num_menu_items].active = 0;

			Num_menu_items++;
		}
	}

	hud_squadmsg_display_menu( XSTR( "What Command", 321) );
	k = hud_squadmsg_get_key();
	if ( k != -1 ) {

		// ignore target gets sent to everyone.
		/* Goober5000 - not anymore
		if (MsgItems[k].instance == IGNORE_TARGET_ITEM)
			hud_squadmsg_send_to_all_fighters(MsgItems[k].instance);
		else */
			hud_squadmsg_send_wing_command(Msg_instance, MsgItems[k].instance, 1);

		hud_squadmsg_toggle();
	}
}



//----------------------------------------------------------
// external entry points below!!!!

// when starting messaging mode, we must remove old bindings from the
// keys that are used for messaging mode (which will get restored when
// messaging mode is done).

// this code below will get called only the key config changes (from ControlsConfig.cpp)
// or if the bindings haven't been saved yet.  This code doesn't remove the bindings
// but just sets up the array so that the bindings can be removed when messaging
// mode is entered.
//
// do_scroll indicates whether we should save the page up and page down keys
void hud_squadmsg_save_keys( int do_scroll )
{
//	int i, j;

	num_keys_saved = 0;

/*
	for ( j=0; j<MAX_KEYS_USED; j++ ) {
		for ( i=0; Control_config[i].text[0]; i++ ) {	// the text field in this structure is empty at the end of the config list
			if ( Control_config[i].key_id == keys_used[j] ) {		// this is true if we have a match

				// if we are not saving scrolling keys and we are trying to match page up and page down
				// then skip them.
				if ( !do_scroll && ((keys_used[j] == KEY_PAGEDOWN) || (keys_used[j] == KEY_PAGEUP)) )
					continue;

				Assert( num_keys_saved < MAX_KEYS_USED );
				key_save[num_keys_saved].option_num = i;
				key_save[num_keys_saved].key_value = keys_used[j];
				num_keys_saved++;
				break;  // done with this key -- move to next.
			}
		}
	}
*/
}

// function is called once per mission start.  Initializes those values
// which only need to be inited once per mission.
void hud_init_squadmsg( void ) 
{
	int i;

	if ( !Mbox_frames_loaded ) {
		for ( i = 0; i < NUM_MBOX_FRAMES; i++ ) {
			Mbox_gauge[i].first_frame = bm_load_animation(Mbox_fnames[gr_screen.res][i], &Mbox_gauge[i].num_frames);
			if ( Mbox_gauge[i].first_frame == -1 ) {
				Warning(LOCATION, "Could not load in ani: %s\n", Mbox_fnames[gr_screen.res][i]);
				return;
			}
		}
		Mbox_frames_loaded = 1;
	}

	Msg_eat_key_timestamp = timestamp(0);
	memset(Squadmsg_history, 0, sizeof(squadmsg_history) * SQUADMSG_HISTORY_MAX);
	squadmsg_history_index = 0; 
}

// external entry point into code which changes the messaging mode based on the
// previous player flag value.  I thought it better to isolate all system changes
// in this code.
void hud_squadmsg_toggle()
{
	// if the emp effect is active, always ignore this
	if(emp_active_local()){
		return;
	}

	// if entering this mode, must setup messaging system.  Don't start squadmessging if 
	// the player is dead.
	if ( !(Player->flags & PLAYER_FLAGS_MSG_MODE) ) {
		if ( Game_mode & GM_DEAD ){
			return;
		}

		if ( (Game_mode & GM_MULTIPLAYER) && NETPLAYER_IS_OBSERVER(Net_player) ){
			return;
		}

		hud_squadmsg_start();
	} else {
		hud_squadmsg_end();
	}

	Player->flags ^= PLAYER_FLAGS_MSG_MODE;
}

//#ifndef NDEBUG
// extern entry point to allow messaging of enemies
void hud_enemymsg_toggle()
{
	hud_squadmsg_toggle();
	// if we just entered message mode, turn on var that says to message enemies
	if ( Player->flags & PLAYER_FLAGS_MSG_MODE )
		Msg_enemies = 1;
}
//#endif

// external entry point into code when a keyboard shortcut is used for a command
// we are passed in an ID for the command to set internal variables.  This command
// will be used in place of the last menu in the messaging code
void hud_squadmsg_shortcut( int command )
{
	// check if the communications system is capable of sending a message
	if ( (hud_communications_state(Player_ship, 1) != COMM_OK) && (command != REARM_REPAIR_ME_ITEM) ) {
		return;
	}

	// observers in multiplayer games cannot have this active either
	if ( (Game_mode & GM_MULTIPLAYER) && NETPLAYER_IS_OBSERVER(Net_player) )
		return;

	// in multiplayer and I cannot message, don't allow anything except calling in for rearm
	if ( (Game_mode & GM_MULTIPLAYER) && !multi_can_message(Net_player) && (command != REARM_REPAIR_ME_ITEM) )
		gamesnd_play_error_beep();

	// player ships which turn traitor cannot rearm
	if ( Player_ship->team == Iff_traitor )
		return;

	if ( Player->flags & PLAYER_FLAGS_MSG_MODE )		// we are already in messaging mode -- maybe do sometime more interesting?
		return;
	hud_squadmsg_toggle();
	Msg_shortcut_command = command;									// save the command for later use

	if (Msg_shortcut_command == CAPTURE_TARGET_ITEM)			// some commands only apply to wings or ships
		Squad_msg_mode = SM_MODE_SHIP_SELECT;						//  -- don't offer choice

	/* Goober5000 - again with the stupid logic
	else if ( Msg_shortcut_command == IGNORE_TARGET_ITEM ) {	//  ignoring target applied to all ships
		hud_squadmsg_toggle();											// turns off mode which was turned on above
		hud_squadmsg_send_to_all_fighters( Msg_shortcut_command );
	}
	*/
}

// external entry point which is called when the player hits a selection key (1-0) while in messaging
// mode.  If we are in messaging mode, send the shortcut command to the ships that are part of the
// passed in selection set.  If there is no shortcut command, do nothing.  Returns 1 if the key
// was used, else 0.  This return value is used to tell the key control system that it should
// call the normal targeting selection stuff.
int hud_squadmsg_hotkey_select( int k )
{
	htarget_list *hitem, *plist;
	int send_message;
	object *objp;

	Assert ( Player->flags & PLAYER_FLAGS_MSG_MODE );

	if ( Msg_shortcut_command == -1 )
		return 0;

	Assert ( (k >= 0) && (k < MAX_KEYED_TARGETS) );
	plist = &(Player->keyed_targets[k]);

	if ( EMPTY(plist) )		// be sure that we have at least one ship in the list
		return 0;

	send_message = 1;
	// for each ship in the selection set list, send the shortcut command that the player
	// previously entered.  Be sure to check that we are not trying to send a command to
	// an enemy ship.
	for ( hitem = GET_FIRST(plist); hitem != END_OF_LIST(plist); hitem = GET_NEXT(hitem) ) {
		objp = hitem->objp;
		Assert ( objp->type == OBJ_SHIP );
		if ( Ships[objp->instance].team != Player_ship->team )
			continue;

		// be sure that this ship can accept this command
		if ( !(Ships[objp->instance].orders_accepted & Msg_shortcut_command) )
			continue;

		hud_squadmsg_send_ship_command( objp->instance, Msg_shortcut_command, send_message );
		send_message  = 0;
	}

	hud_squadmsg_toggle();			// turn off messaging mode
	return 1;
}


// the next function is called once a frame when the player is messaging someone
// in his squad.  After a period of 5 seconds of inactivity (i.e. no keypress to
// select something in the menu), the menu will disappear.  This function will only
// get called if the player flag PLAYER_FLAG_MSG_MODE is set.  Parameter is the key
// that was hit this frame

int hud_squadmsg_do_frame( )
{
	int target_changed;

	Assert ( Player->flags & PLAYER_FLAGS_MSG_MODE );		// be sure that messaging mode is set!!!

	// if the player is now dead, or the timestamp elapsed, then get out of messaging mode.
	if ( (Game_mode & GM_DEAD) || timestamp_elapsed(Msg_mode_timestamp) ) {
		hud_squadmsg_toggle();
		return 0;
	}

	Msg_key_used = 0;

	// check the player's current target.  Change in target resets the timer
	target_changed = 0;
	if ( Msg_target_objnum != Player_ai->target_objnum ) {
		Msg_target_objnum = Player_ai->target_objnum;
		target_changed = 1;
	}

	if ( Msg_targeted_subsys != Player_ai->targeted_subsys ) {
		Msg_targeted_subsys = Player_ai->targeted_subsys;
		target_changed = 1;
	}

	// setup color/font info 
	// hud_set_default_color();
	hud_set_gauge_color(HUD_MESSAGE_BOX);

	// check for multiplayer mode - this is really a special case checker for support ship requesting and aborting
	if((Game_mode & GM_MULTIPLAYER) && !(Net_player->flags & NETINFO_FLAG_AM_MASTER) && (Squad_msg_mode == SM_MODE_REPAIR_REARM || Squad_msg_mode == SM_MODE_REPAIR_REARM_ABORT)){
		char *subsys_name;
//		int who_to_sig;
		ushort net_sig;
		
		// who_to_sig = Objects[Ships[shipnum].objnum].net_signature;
		if(Player_ai->target_objnum != -1)
			net_sig = Objects[Player_ai->target_objnum].net_signature;
		else 
			net_sig = 0;

      if ((Player_ai->targeted_subsys != NULL) && (Player_ai->targeted_subsys->current_hits > 0.0f))
			subsys_name = Player_ai->targeted_subsys->system_info->subobj_name;
		else
			subsys_name = NULL;
		
		// send the correct packet
		if(Squad_msg_mode == SM_MODE_REPAIR_REARM)		
			send_player_order_packet(SQUAD_MSG_SHIP, 0, REARM_REPAIR_ME_ITEM);
		else
			send_player_order_packet(SQUAD_MSG_SHIP, 0, ABORT_REARM_REPAIR_ITEM);

		// make sure to toggle the mode off
		hud_squadmsg_toggle();
		
		return 1;
	}

	// draw top of frame
	if ( Mbox_gauge[0].first_frame >= 0 ) {
		GR_AABITMAP(Mbox_gauge[0].first_frame, Mbox_top_coords[gr_screen.res][0], Mbox_top_coords[gr_screen.res][1]);		
	}

	switch( Squad_msg_mode ) {

	case SM_MODE_TYPE_SELECT:
		hud_squadmsg_type_select();
		break;

	case SM_MODE_SHIP_SELECT:
		hud_squadmsg_ship_select();
		break;

	case SM_MODE_WING_SELECT:
		hud_squadmsg_wing_select();
		break;

	case SM_MODE_SHIP_COMMAND:
		hud_squadmsg_ship_command();
		break;

	case SM_MODE_WING_COMMAND:
		hud_squadmsg_wing_command();
		break;

	case SM_MODE_REINFORCEMENTS:
		hud_squadmsg_reinforcement_select();
		break;		
		
	case SM_MODE_REPAIR_REARM:
		//if((Game_mode & GM_MULTIPLAYER) && (Net_player->flags & NETINFO_FLAG_AM_MASTER) && (addr != NULL)){
		//	hud_squadmsg_repair_rearm(1,&Objects[Net_players[player_num].player->objnum]);
		//} else {
			hud_squadmsg_repair_rearm(1);				// note we return right away.  repair/rearm code handles messaging, etc
		//}	
		break;

	case SM_MODE_REPAIR_REARM_ABORT:
		//if((Game_mode & GM_MULTIPLAYER) && (Net_player->flags & NETINFO_FLAG_AM_MASTER) && (addr != NULL)){
		//	hud_squadmsg_repair_rearm_abort(1,&Objects[Net_players[player_num].player->objnum]);
		//} else {
			hud_squadmsg_repair_rearm_abort(1);		// note we return right away.  repair/rearm code handles messaging, etc
		//}
		break;

	case SM_MODE_ALL_FIGHTERS:
		hud_squadmsg_msg_all_fighters();
		break;

	default:
		Int3();		// get allender -- invalid mode in messaging system
		break;

	}

	// be sure to reset the clip region
	HUD_reset_clip();		// JAS: Is this needed?

	if ( Msg_key_used || target_changed ) {
		Msg_mode_timestamp = timestamp(DEFAULT_MSG_TIMEOUT);
		return 1;
	} else
		return 0;
}

void hud_add_issued_order(char *name, int order, char *target)
{
	Squadmsg_history[squadmsg_history_index].ship = get_parse_name_index(name);
	Squadmsg_history[squadmsg_history_index].order = order;
	if (target)
		Squadmsg_history[squadmsg_history_index].target = get_parse_name_index(target);
	else
		Squadmsg_history[squadmsg_history_index].target = -1;

	squadmsg_history_index++;
	if (squadmsg_history_index >= SQUADMSG_HISTORY_MAX)
		squadmsg_history_index = 0;
}

int hud_query_order_issued(char *name, char *order, char *target)
{
	int i, o=-1, ship, t;

	ship = get_parse_name_index(name);
	t = -1;
	if (target)
		t = get_parse_name_index(target);

	for (i = 0; i < NUM_COMM_ORDER_ITEMS; i++)
		if (!stricmp(order, Comm_orders[i].name))
			o = Comm_orders[i].item;

	// Goober5000 - if not found, check compatibility
	if (o == -1)
	{
		if (!stricmp(order, "Attack my target"))
		{
			i = 0;	// it maps to option 0, "Destroy my target"
			o = Comm_orders[i].item;
		}
	}

	Assert(o != -1);
	for (i = 0; i < SQUADMSG_HISTORY_MAX; i++)
		if (Squadmsg_history[i].order == o)
			if (ship == Squadmsg_history[i].ship)
				if (Squadmsg_history[i].target == t)
					return 1;

	return 0;
}


void hudsquadmsg_page_in() 
{
	int i;

	for ( i = 0; i < NUM_MBOX_FRAMES; i++ ) {
		bm_page_in_aabitmap( Mbox_gauge[i].first_frame, Mbox_gauge[i].num_frames );
	}
}
