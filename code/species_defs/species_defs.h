/*
 * Species_Defs.h
 * Extended Species Support for FS2 Open
 *
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 *
 */

/*
 * $Logfile: /Freespace2/code/species_defs/species_defs.h $
 * $Revision: 1.11 $
 * $Date: 2005-09-25 20:31:42 $
 * $Author: Goober5000 $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.10  2005/09/25 18:48:25  taylor
 * GCC fixage, my Whiffle Bat that was saved for Bobboau's constant breaking is currently getting "Goober5000" etched into it :)
 *
 * Revision 1.9  2005/09/25 08:25:16  Goober5000
 * Okay, everything should now work again. :p Still have to do a little more with the asteroids.
 * --Goober5000
 *
 * Revision 1.8  2005/09/25 07:07:34  Goober5000
 * partial commit; hang on
 * --Goober5000
 *
 * Revision 1.7  2005/09/25 05:13:07  Goober5000
 * hopefully complete species upgrade
 * --Goober5000
 *
 * Revision 1.6  2005/09/25 02:15:02  Goober5000
 * meh for consistency
 * --Goober5000
 *
 * Revision 1.5  2005/09/24 07:07:17  Goober5000
 * another species overhaul
 * --Goober5000
 *
 * Revision 1.4  2005/07/13 03:35:35  Goober5000
 * remove PreProcDefine #includes in FS2
 * --Goober5000
 *
 * Revision 1.3  2005/01/31 10:34:39  taylor
 * merge with Linux/OSX tree - p0131
 *
 * Revision 1.2  2004/08/11 05:06:34  Kazan
 * added preprocdefines.h to prevent what happened with fred -- make sure to make all fred2 headers include this file as the _first_ include -- i have already modified fs2 files to do this
 *
 * Revision 1.1  2003/10/15 22:03:27  Kazan
 * Da Species Update :D
 *
 *
 *
 *
 */

#ifndef _SPECIES_DEFS_H_
#define _SPECIES_DEFS_H_

#include "globalincs/pstypes.h"
#include "globalincs/globals.h"
#include "bmpman/bmpman.h"
#include "gamesnd/gamesnd.h"
#include "hud/hud.h"
#include "mission/missionbriefcommon.h"
#include "asteroid/asteroid.h"

typedef struct thrust_pair {
	generic_anim normal;
	generic_anim afterburn;
} thrust_pair;

typedef struct thrust_info {
	thrust_pair flames;
	thrust_pair glow;
} thrust_info;


// Currently the only species-specific feature not in species_info is ship debris.  This is because
// ship debris chunks are treated as asteroids and tied so tightly into the asteroid code that
// separating them makes the code much more complicated.

typedef struct species_info {

	char species_name[NAME_LENGTH];

	generic_bitmap debris_texture;
	generic_anim shield_anim;
	thrust_info thruster_info;

	float awacs_multiplier;

	union {
		struct {
			int r, g, b;
		} rgb;
		int a1d[3];
	} fred_color;


	// if this will not be parsed in species_defs.tbl, move it below the following comment
#ifdef NEW_HUD
	hud_info hud;
#endif


	// the members below this comment are not parsed in species_defs.tbl

	game_snd snd_flyby_fighter;
	game_snd snd_flyby_bomber;

	hud_frames icon_bitmaps[MAX_BRIEF_ICONS];
	hud_anim icon_highlight_anims[MAX_BRIEF_ICONS];
	hud_anim icon_fade_anims[MAX_BRIEF_ICONS];


	// constructor to initialize everything to 0
	species_info()
	{
		memset(this, 0, sizeof(species_info));
	}

} species_info;


extern int Num_species;
extern species_info Species_info[MAX_SPECIES];


// load up the species_defs.tbl into the correct data areas
// IMPORTANT: If Num_species != 3, icons.tbl, asteroid.tbl, and sounds.tbl have to be modified to compensate!
void species_init();

#endif
