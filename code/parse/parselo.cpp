/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Source: /cvs/cvsroot/fs2open/fs2_open/code/parse/parselo.cpp,v $
 * $Revision: 2.57 $
 * $Author: Goober5000 $
 * $Date: 2005-11-21 03:47:51 $
 *
 * low level parse routines common to all types of parsers
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.56  2005/11/08 01:04:00  wmcoolmon
 * More warnings instead of Int3s/Asserts, better Lua scripting, weapons_expl.tbl is no longer needed nor read, added "$Disarmed ImpactSnd:", fire-beam fix
 *
 * Revision 2.55  2005/10/29 09:02:13  wmcoolmon
 * Better alloc_block function
 *
 * Revision 2.54  2005/10/22 20:17:19  wmcoolmon
 * mission-set-nebula fixage; remainder of python code
 *
 * Revision 2.53  2005/10/09 06:10:58  wmcoolmon
 * Added sexps set-object-speed-x, set-object-speed-y, set-object-speed-z,
 * and ship-create
 *
 * Revision 2.52  2005/10/08 18:26:40  wmcoolmon
 * Better readability for parse errors
 *
 * Revision 2.51  2005/09/30 03:19:57  Goober5000
 * parsing stuff
 * --Goober5000
 *
 * Revision 2.50  2005/09/29 04:26:08  Goober5000
 * parse fixage
 * --Goober5000
 *
 * Revision 2.49  2005/09/20 04:51:45  wmcoolmon
 * New parsing functions that I'll be using for XMTs once I get them
 * working
 *
 * Revision 2.48  2005/09/17 01:36:29  Goober5000
 * It is a strange fate that we should suffer so much fear and doubt over so small a thing.
 * Such a little thing...
 *
 * Revision 2.47  2005/09/06 00:32:19  Kazan
 * fixed a bug related to multiplayer table validation and modular tables
 *
 * Revision 2.46  2005/08/24 07:14:52  Goober5000
 * faster version of stristr
 * --Goober5000
 *
 * Revision 2.45  2005/08/22 22:24:21  Goober5000
 * some tweaks to parselo, plus ensure that Unicode files don't crash
 * --Goober5000
 *
 * Revision 2.44  2005/07/23 21:47:46  Goober5000
 * bah - fixed subsystem comparison
 * --Goober5000
 *
 * Revision 2.43  2005/06/03 22:36:57  wmcoolmon
 * I *think* this should fix bool lists
 *
 * Revision 2.42  2005/05/13 02:41:24  phreak
 * forgot a vm_strdup in place of a strdup
 *
 * Revision 2.41  2005/05/12 17:49:16  taylor
 * use vm_malloc(), vm_free(), vm_realloc(), vm_strdup() rather than system named macros
 *   fixes various problems and is past time to make the switch
 *
 * Revision 2.40  2005/05/08 20:23:28  wmcoolmon
 * "backspace" function
 *
 * Revision 2.39  2005/04/28 01:36:46  wmcoolmon
 * More parsing flexibility
 *
 * Revision 2.38  2005/04/28 01:12:19  wmcoolmon
 * Added stuff_bool_list; Internationalized stuff_boolean.
 *
 * Revision 2.37  2005/04/18 06:59:16  Goober5000
 * better subsystem comparison
 * --Goober5000
 *
 * Revision 2.36  2005/04/05 05:53:22  taylor
 * s/vector/vec3d/g, better support for different compilers (Jens Granseuer)
 *
 * Revision 2.35  2005/03/25 06:57:37  wmcoolmon
 * Big, massive, codebase commit. I have not removed the old ai files as the ones I uploaded aren't up-to-date (But should work with the rest of the codebase)
 *
 * Revision 2.34  2005/03/12 03:09:22  wmcoolmon
 * New commandline option "-noparseerrors"
 *
 * Revision 2.33  2005/03/10 08:00:12  taylor
 * change min/max to MIN/MAX to fix GCC problems
 * add lab stuff to Makefile
 * build unbreakage for everything that's not MSVC++ 6
 * lots of warning fixes
 * fix OpenGL rendering problem with ship insignias
 * no Warnings() in non-debug mode for Linux (like Windows)
 * some campaign savefile fixage to stop reverting everyones data
 *
 * Revision 2.32  2005/02/23 05:05:38  taylor
 * compiler warning fixes (for MSVC++ 6)
 * have the warp effect only load as many LODs as will get used
 * head off strange bug in release when corrupt soundtrack number gets used
 *    (will still Assert in debug)
 * don't ever try and save a campaign savefile in multi or standalone modes
 * first try at 32bit->16bit color conversion for TGA code (for TGA only ship textures)
 *
 * Revision 2.31  2005/02/04 20:06:06  taylor
 * merge with Linux/OSX tree - p0204-2
 *
 * Revision 2.30  2005/01/30 01:38:26  wmcoolmon
 * If a required string doesn't exist, give an error instead of a warning...doi.
 *
 * Revision 2.29  2005/01/25 22:47:37  Goober5000
 * more cool parsing stuff
 * --Goober5000
 *
 * Revision 2.28  2005/01/25 22:21:45  Goober5000
 * separated one parsing function into two
 * --Goober5000
 *
 * Revision 2.27  2005/01/25 21:28:58  Goober5000
 * streamlined some redundant stuff
 * --Goober5000
 *
 * Revision 2.26  2004/12/25 09:25:18  wmcoolmon
 * Fix to modular tables workaround with Fs2NetD
 *
 * Revision 2.25  2004/12/14 17:23:52  Goober5000
 * new version of stristr that doesn't need to allocate memory
 * --Goober5000
 *
 * Revision 2.24  2004/10/31 21:57:30  taylor
 * support external parsing sources without hurting currently parsing file (for EFF code)
 *
 * Revision 2.23  2004/09/05 19:23:24  Goober5000
 * fixed a few warnings
 * --Goober5000
 *
 * Revision 2.22  2004/07/26 20:47:47  Kazan
 * remove MCD complete
 *
 * Revision 2.21  2004/07/12 16:33:01  Kazan
 * MCD - define _MCD_CHECK to use memory tracking
 *
 * Revision 2.20  2004/05/31 08:32:25  wmcoolmon
 * Custom HUD support, better loading, etc etc.
 *
 * Revision 2.19  2004/05/29 03:01:00  wmcoolmon
 * Spotted something that might be a problem.
 *
 * Revision 2.18  2004/05/29 02:52:17  wmcoolmon
 * Added stuff_float_list
 *
 * Revision 2.17  2004/05/11 02:52:11  Goober5000
 * completed the FRED import conversion stuff that I started ages ago
 * --Goober5000
 *
 * Revision 2.16  2004/03/05 09:02:08  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.15  2004/02/07 01:25:14  Goober5000
 * hehe, fixed the subsystem compare so it's not destructive :-p
 * and also fixed the model checking routine
 * --Goober5000
 *
 * Revision 2.14  2004/02/07 00:48:52  Goober5000
 * made FS2 able to account for subsystem mismatches between ships.tbl and the
 * model file - e.g. communication vs. communications
 * --Goober5000
 *
 * Revision 2.13  2004/02/04 09:02:43  Goober5000
 * got rid of unnecessary double semicolons
 * --Goober5000
 *
 * Revision 2.12  2004/01/30 07:39:09  Goober5000
 * whew - I just went through all the code I ever added (or at least, that I could
 * find that I commented with a Goober5000 tag) and added a bunch of Asserts
 * and error-checking
 * --Goober5000
 *
 * Revision 2.11  2003/11/17 06:52:52  bobboau
 * got assert to work again
 *
 * Revision 2.10  2003/09/30 04:05:09  Goober5000
 * updated FRED to import FS1 default weapons loadouts as well as missions
 * --Goober5000
 *
 * Revision 2.9  2003/09/28 21:22:58  Goober5000
 * added the option to import FSM missions, added a replace function, spruced
 * up my $player, $rank, etc. code, and fixed encrypt being misspelled as 'encrpyt'
 * --Goober5000
 *
 * Revision 2.8  2003/08/25 04:45:57  Goober5000
 * added replacement of $rank with the player's rank in any string that appears
 * in-game (same as with $callsign); also bumped the limit on the length of text
 * allowed per entry in species.tbl
 * --Goober5000
 *
 * Revision 2.7  2003/08/22 07:01:57  Goober5000
 * implemented $callsign to add the player callsign in a briefing, message, or whatever
 * --Goober5000
 *
 * Revision 2.6  2003/03/02 06:10:58  penguin
 * Made a debug error message less confusing
 *  - penguin
 *
 * Revision 2.5  2003/01/30 23:19:33  phreak
 * cleaned up debug output
 *
 * Revision 2.4  2003/01/19 01:07:42  bobboau
 * redid the way glowmaps are handeled, you now must set the global int GLOWMAP (no longer an array) before you render a poly that uses a glow map then set  GLOWMAP to -1 when you're done with, fixed a few other misc bugs it
 *
 * Revision 2.3  2003/01/17 07:59:08  Goober5000
 * fixed some really strange behavior with strings not being truncated at the
 * # symbol
 * --Goober5000
 *
 * Revision 2.2  2003/01/05 23:41:51  bobboau
 * disabled decals (for now), removed the warp ray thingys,
 * made some better error mesages while parseing weapons and ships tbls,
 * and... oh ya, added glow mapping
 *
 * Revision 2.1  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:27  penguin
 * Warpcore CVS sync
 *
 * Revision 1.3  2002/05/21 15:46:58  mharris
 * Reformat some debug strings
 *
 * Revision 1.2  2002/05/03 22:07:09  mharris
 * got some stuff to compile
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 12    8/10/99 6:54p Dave
 * Mad optimizations. Added paging to the nebula effect.
 * 
 * 11    6/02/99 2:22p Andsager
 * Clean up warning.
 * 
 * 10    5/20/99 11:25a Andsager
 * Added error checking for parsing table files.
 * 
 * 9     2/23/99 11:18a Andsager
 * Localize launcher using strings.tbl
 * 
 * 8     2/03/99 6:06p Dave
 * Groundwork for FS2 PXO usertracker support.  Gametracker support next.
 * 
 * 7     11/05/98 4:18p Dave
 * First run nebula support. Beefed up localization a bit. Removed all
 * conditional compiles for foreign versions. Modified mission file
 * format.
 * 
 * 6     10/29/98 12:49p Dave
 * Intermediate checkin for Fred hash table stuff. 
 * 
 * 5     10/28/98 11:30a Dave
 * Temporary checkin
 * 
 * 4     10/22/98 6:14p Dave
 * Optimized some #includes in Anim folder. Put in the beginnings of
 * parse/localization support for externalized strings and tstrings.tbl
 * 
 * 3     10/14/98 1:15p Andsager
 * Fix fred
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:50a Dave
 * 
 * 98    9/21/98 2:37p Adam
 * fixed font translation bug
 * 
 * 97    7/29/98 9:39a Hoffoss
 * Fixed bug with stuff_and_malloc_string
 * 
 * 96    6/22/98 11:18a Hoffoss
 * Fixed bug where mission notes field gets an extra linefeed with each
 * save.
 * 
 * 95    6/19/98 3:53p Lawrance
 * account for some new foreign chars
 * 
 * 94    6/12/98 7:37p Hoffoss
 * Made �translate to ss, since we don't have this character in our font.
 * 
 * 93    6/12/98 4:52p Hoffoss
 * Added support for special characters in in forgeign languages.
 * 
 * 92    5/21/98 3:26p Dave
 * Fixed bug in new split string function.  Newline as last character did
 * strange things.
 * 
 * 91    5/21/98 3:01p Dave
 * Make sure split_str handles 0 length strings correctly.
 * 
 * 90    5/21/98 2:14a Hoffoss
 * Rewrote split_str() to solve a problem and it was too hard for me to
 * figure out (oow, my head hurts still!)
 * 
 * $NoKeywords: $
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <setjmp.h>

#include "parse/parselo.h"
#include "parse/sexp.h"
#include "mission/missionparse.h"
#include "ctype.h"
#include "parse/encrypt.h"
#include "localization/localize.h"
#include "localization/fhash.h"
#include "cfile/cfile.h"
#include "ship/ship.h"
#include "weapon/weapon.h"



#define	ERROR_LENGTH	64
#define	RS_MAX_TRIES	5

//To keep people from bypassing table checksums with modular tables -C
bool	Modular_tables_loaded = false;
bool	Module_ship_weapons_loaded = false;

char	parse_error_text[64];//for my better error mesages-Bobboau
char		Current_filename[128];
char		Error_str[ERROR_LENGTH];
int		my_errno;
int		Warning_count, Error_count;
int		fred_parse_flag = 0;
int		Token_found_flag;
jmp_buf	parse_abort;

char	Mission_text[MISSION_TEXT_SIZE];
char	Mission_text_raw[MISSION_TEXT_SIZE];
char	*Mp, *ex_Mp;
char	*token_found;

//	Return true if this character is white space, else false.
int is_white_space(char ch)
{
	return ((ch == ' ') || (ch == '\t') || (ch == EOLN));
}

// Returns true if this character is gray space, else false (gray space is white space except for EOLN).
int is_gray_space(char ch)
{
	return ((ch == ' ') || (ch == '\t'));
}

//	Advance global Mp (mission pointer) past all current white space.
//	Leaves Mp pointing at first non white space character.
void ignore_white_space()
{
	while ((*Mp != EOF_CHAR) && is_white_space(*Mp))
		Mp++;
}

// same as ignore_white_space() but with specific text
void ignore_white_space_ex()
{
	if (ex_Mp == NULL)
		return;

	while ((*ex_Mp != EOF_CHAR) && is_white_space(*ex_Mp))
		ex_Mp++;
}

void ignore_gray_space()
{
	while ((*Mp != EOF_CHAR) && is_gray_space(*Mp))
		Mp++;
}

void ignore_gray_space_ex()
{
	while ((*ex_Mp != EOF_CHAR) && is_gray_space(*ex_Mp))
		ex_Mp++;
}

//	Truncate *str, eliminating all trailing white space.
//	Eg: "abc   "   becomes "abc"
//		 "abc abc " becomes "abc abc"
//		 "abc \t"   becomes "abc"
void drop_trailing_white_space(char *str)
{
	int	i;

	i = strlen(str) - 1;

	while ((i >= 0) && is_white_space(str[i]))
		i--;

	str[i+1] = 0;
}

//	Eliminate any leading whitespace in str
void drop_leading_white_space(char *str)
{
	int len, i;

	len = strlen(str);
	i = 0;

	while ((i < len) && is_white_space(str[i]))
		i++;

	memmove(str, str+i, len-i);
	str[len-i] = 0;
}

// eliminates all leading and trailing white space from a string.  Returns pointer passed in.
char *drop_white_space(char *str)
{
	int s, e;

	s = 0;
	while (str[s] && is_white_space(str[s]))
		s++;

	e = strlen(str) - 1;
	while (e > s) {
		if (!is_white_space(str[e]))
			break;

		e--;
	}

	if (e > s)
		memmove(str, str + s, e - s + 1);

	str[e - s + 1] = 0;
	return str;
}

//	Advances Mp past current token.
void skip_token()
{
	ignore_white_space();

	while ((*Mp != EOF_CHAR) && !is_white_space(*Mp))
		Mp++;
}

//	Advances ex_Mp past current token.
void skip_token_ex()
{
	ignore_white_space_ex();

	while ((*ex_Mp != EOF_CHAR) && !is_white_space(*ex_Mp))
		ex_Mp++;
}

//	Display a diagnostic message if Verbose is set.
//	(Verbose is set if -v command line switch is present.)
void diag_printf(char *format, ...)
{
	char	buffer[8192];
	va_list args;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	nprintf(("Parse", "%s", buffer));
}

//	Grab and return (a pointer to) a bunch of tokens, terminating at
// ERROR_LENGTH chars, or end of line.
char *next_tokens()
{
	int	count = 0;
	char	*pstr = Mp;
	char	ch;

	while (((ch = *pstr++) != EOLN) && (ch != EOF_CHAR) && (count < ERROR_LENGTH-1))
		Error_str[count++] = ch;

	Error_str[count] = 0;
	return Error_str;
}

//	Return the line number given by the current mission pointer, ie Mp.
//	A very slow function (scans all processed text), but who cares how long
//	an error reporting function takes?
int get_line_num()
{
	int	count = 1;
	int	incomment = 0;
	int	multiline = 0;
	char	*stoploc;
	char	*p;

	p = Mission_text_raw;
	stoploc = (Mp - Mission_text) + p;

	while (p < stoploc)
	{
		if (*p == EOF_CHAR)
			Assert(0);

		if ( !incomment && (*p == COMMENT_CHAR) )
			incomment = 1;

		if ( !incomment && (*p == '/') && (*(p+1) == '*') ) {
			multiline = 1;
			incomment = 1;
		}

		if ( incomment )
			stoploc++;

		if ( multiline && (*(p-1) == '*') && (*p == '/') ) {
			multiline = 0;
			incomment = 0;
		}

		if (*p++ == EOLN) {
			if ( !multiline && incomment )
				incomment = 0;
			count++;
		}
	}

	return count;
}

//	Call this function to display an error message.
//	error_level == 0 means this is just a warning.
//	!0 means it's an error message.
//	Prints line number and other useful information.
extern int Cmdline_noparseerrors;
void error_display(int error_level, char *format, ...)
{
	char	buffer[1024];
	char	error_text[128];
	va_list args;

	if (error_level == 0) {
		strcpy(error_text, "Warning");
		Warning_count++;
	} else {
		strcpy(error_text, "Error");
		Error_count++;
	}

	nprintf((error_text, "%s(line %i:%s: ", Current_filename, get_line_num(), error_text));

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);
	Assert(strlen(buffer) < 1024);

	nprintf((error_text, "%s", buffer));
	if(error_level == 0 || Cmdline_noparseerrors)
		Warning(LOCATION, "%s(line %i:\n%s: %s", Current_filename, get_line_num(), error_text, buffer);
	else
		Error(LOCATION, "%s(line %i:\n%s: %s", Current_filename, get_line_num(), error_text, buffer);
}

//	Advance Mp to the next eoln character.
void advance_to_eoln(char *more_terminators)
{
	char	terminators[128];

	Assert((more_terminators == NULL) || (strlen(more_terminators) < 125));

	terminators[0] = EOLN;
	terminators[1] = (char)EOF_CHAR;
	if (more_terminators != NULL)
		strcpy(&terminators[2], more_terminators);
	else
		terminators[2] = 0;

	while (strchr(terminators, *Mp) == NULL)
		Mp++;
}

//	Advance external Mp to the next eoln character.
void advance_to_eoln_ex(char *more_terminators)
{
	char	terminators[128];

	Assert((more_terminators == NULL) || (strlen(more_terminators) < 125));

	terminators[0] = EOLN;
	terminators[1] = (char)EOF_CHAR;
	if (more_terminators != NULL)
		strcpy(&terminators[2], more_terminators);
	else
		terminators[2] = 0;

	while (strchr(terminators, *ex_Mp) == NULL)
		ex_Mp++;
}

// Advance Mp to the next white space (ignoring white space inside of " marks)
void advance_to_next_white()
{
	int in_quotes = 0;

	while ((*Mp != EOLN) && (*Mp != EOF_CHAR)) {
		if (*Mp == '\"')
			in_quotes = !in_quotes;

		if (!in_quotes && is_white_space(*Mp))
			break;
		Mp++;
	}
}

// Search for specified string, skipping everything up to that point.  Returns 1 if found,
// 0 if string wasn't found (and hit end of file), or -1 if not found, but end of checking
// block was reached.
int skip_to_string(char *pstr, char *end)
{
	int len, len2 = 0;

	ignore_white_space();
	len = strlen(pstr);
	if (end)
		len2 = strlen(end);

	while ((*Mp != EOF_CHAR) && strnicmp(pstr, Mp, len)) {
		if (end && *Mp == '#')
			return 0;

		if (end && !strnicmp(end, Mp, len2))
			return -1;

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR))
		return 0;

	Mp += strlen(pstr);
	return 1;
}

// Goober5000
// Advance to start of pstr.  Return 0 is successful, otherwise return !0
int skip_to_start_of_string(char *pstr, char *end)
{
	int len, endlen;

	ignore_white_space();
	len = strlen(pstr);
	if(end)
		endlen = strlen(end);
	else
		endlen = 0;

	while ( (*Mp != EOF_CHAR) && strnicmp(pstr, Mp, len) ) {
		if (end && *Mp == '#')
			return 0;

		if (end && !strnicmp(end, Mp, endlen))
			return 0;

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR))
		return 0;

	return 1;
}

// Advance to start of either pstr1 or pstr2.  Return 0 is successful, otherwise return !0
int skip_to_start_of_string_either(char *pstr1, char *pstr2, char *end)
{
	int len1, len2, endlen;

	ignore_white_space();
	len1 = strlen(pstr1);
	len2 = strlen(pstr2);
	if(end)
		endlen = strlen(end);
	else
		endlen = 0;

	while ( (*Mp != EOF_CHAR) && strnicmp(pstr1, Mp, len1) && strnicmp(pstr2, Mp, len2) ) {
		if (end && *Mp == '#')
			return 0;

		if (end && !strnicmp(end, Mp, endlen))
			return 0;

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR))
		return 0;

	return 1;
}

// Find a required string.
// If not found, display an error message, but try up to RS_MAX_TRIES times
// to find the string.  (This is the groundwork for ignoring non-understood
// lines.
//	If unable to find the required string after RS_MAX_TRIES tries, then
//	abort using longjmp to parse_abort.
int required_string(char *pstr)
{
	int	count = 0;

	ignore_white_space();

	while (strnicmp(pstr, Mp, strlen(pstr)) && (count < RS_MAX_TRIES)) {
		error_display(1, "Required token = [%s], found [%.32s] %s.\n", pstr, next_tokens(), parse_error_text);
		advance_to_eoln(NULL);
		ignore_white_space();
		count++;
	}

	if (count == RS_MAX_TRIES) {
		nprintf(("Error", "Error: Unable to find required token [%s] %s\n", pstr, parse_error_text));
		Warning(LOCATION, "Error: Unable to find required token [%s] %s\n", pstr, parse_error_text);
		longjmp(parse_abort, 1);
	}

	Mp += strlen(pstr);
	diag_printf("Found required string [%s]\n", token_found = pstr);
	return 1;
}

// Find a required string
// same as required_string() above but you must pass the text to be evaluated in ex_Mp.
int required_string_ex(char *pstr)
{
	int	count = 0;

	if (ex_Mp == NULL)
		return 1;

	ignore_white_space_ex();

	while (strnicmp(pstr, ex_Mp, strlen(pstr)) && (count < RS_MAX_TRIES)) {
	//	error_display(1, "Required token = [%s], found [%.32s] %s.\n", pstr, next_tokens(), parse_error_text);
		advance_to_eoln_ex(NULL);
		ignore_white_space_ex();
		count++;
	}

	if (count == RS_MAX_TRIES) {
	//	nprintf(("Error", "Error: Unable to find required token [%s] %s\n", pstr, parse_error_text));
	//	Warning(LOCATION, "Error: Unable to find required token [%s] %s\n", pstr, parse_error_text);
		nprintf(("Error", "Error: Unable to find required token [%s]\n", pstr));
	//	longjmp(parse_abort, 1);
	}

	ex_Mp += strlen(pstr);
//	diag_printf("Found required string [%s]\n", token_found = pstr);
	return 1;
}

// similar to optional_string, but just checks if next token is a match.
// It doesn't advance Mp except to skip past white space.
//
int check_for_string(char *pstr)
{
	ignore_white_space();

	if (!strnicmp(pstr, Mp, strlen(pstr)))
		return 1;

	return 0;
}

// like check for string, but doesn't skip past any whitespace
int check_for_string_raw(char *pstr)
{
	if (!strnicmp(pstr, Mp, strlen(pstr))){
		return 1;
	}

	return 0;
}

// Find an optional string.
//	If found, return 1, else return 0.
//	If found, point past string, else don't update pointer.
int optional_string(char *pstr)
{
	ignore_white_space();
//	mprintf(("lookint for optional string %s",pstr));

	if (!strnicmp(pstr, Mp, strlen(pstr))) {
		Mp += strlen(pstr);
//		mprintf((", found it\n"));
		return 1;
	}
//	mprintf((", didin't find it it\n"));

	return 0;
}

// ex_Mp version of optional_string()
int optional_string_ex(char *pstr)
{
	ignore_white_space_ex();
//	mprintf(("lookint for optional string %s",pstr));

	if (!strnicmp(pstr, ex_Mp, strlen(pstr))) {
		ex_Mp += strlen(pstr);
//		mprintf((", found it\n"));
		return 1;
	}
//	mprintf((", didin't find it it\n"));

	return 0;
}

int required_string_fred(char *pstr, char *end)
{
	char *backup = Mp;

	token_found = pstr;
	if (fred_parse_flag)
		return 0;

	ignore_white_space();
	while (*Mp != EOF_CHAR && strnicmp(pstr, Mp, strlen(pstr))) {
		if ((*Mp == '#') || (end && !strnicmp(end, Mp, strlen(end)))) {
			Mp = NULL;
			break;
		}

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR)) {
		diag_printf("Required string [%s] not found\n", pstr);
		Mp = backup;
		Token_found_flag = 0;
		return 0;
	}

	Mp += strlen(pstr);
	diag_printf("Found required string [%s]\n", pstr);
	Token_found_flag = 1;
	return 1;
}

// attempt to find token in buffer.  It might not exist, however, in which case we don't need
// to do anything.  If it is found, then we advance the pointer to just after the token.  To
// further complicate things, we should only search to a certain point, since we don't want
// a token that belongs to another section which might match the token we want.  Thus, we
// also pass in an ending token, which marks the point we should stop looking at.
int optional_string_fred(char *pstr, char *end, char *end2)
{
	char *mp_save = Mp;

	token_found = pstr;
	if (fred_parse_flag)
		return 0;

	ignore_white_space();
	while ((*Mp != EOF_CHAR) && strnicmp(pstr, Mp, strlen(pstr))) {
		if ((*Mp == '#') || (end && !strnicmp(end, Mp, strlen(end))) ||
			(end2 && !strnicmp(end2, Mp, strlen(end2)))) {
			Mp = NULL;
			break;
		}

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR)) {
		diag_printf("Optional string [%s] not found\n", pstr);
		Mp = mp_save;
		Token_found_flag = 0;
		return 0;
	}

	Mp += strlen(pstr);
	diag_printf("Found optional string [%s]\n", pstr);
	Token_found_flag = 1;
	return 1;
}

//	Return 0 or 1 for str1 match, str2 match.  Return -1 if neither matches.
//	Does not update Mp if token found.  If not found, advances, trying to
//	find the string.  Doesn't advance past the found string.
int required_string_either(char *str1, char *str2)
{
	int	count = 0;

	ignore_white_space();

	while (count < RS_MAX_TRIES) {
		if (strnicmp(str1, Mp, strlen(str1)) == 0) {
			// Mp += strlen(str1);
			diag_printf("Found required string [%s]\n%s", token_found = str1, parse_error_text);
			return 0;
		} else if (strnicmp(str2, Mp, strlen(str2)) == 0) {
			// Mp += strlen(str2);
			diag_printf("Found required string [%s]\n%s", token_found = str2, parse_error_text);
			return 1;
		}

		error_display(1, "Required token = [%s] or [%s], found [%.32s] %s.\n", str1, str2, next_tokens(), parse_error_text);

		advance_to_eoln(NULL);
		ignore_white_space();
		count++;
	}

	if (count == RS_MAX_TRIES) {
		nprintf(("Error", "Error: Unable to find either required token [%s] or [%s]\n", str1, str2));
		Warning(LOCATION, "Error: Unable to find either required token [%s] or [%s]\n", str1, str2);
		longjmp(parse_abort, 2);
	}

	return -1;
	// exit (1);
}

//	Return 0 or 1 for str1 match, str2 match.  Return -1 if neither matches.
//	Does not update Mp if token found.  If not found, advances, trying to
//	find the string.  Doesn't advance past the found string.
int required_string_3(char *str1, char *str2, char *str3)
{
	int	count = 0;

	ignore_white_space();

	while (count < RS_MAX_TRIES) {
		if (strnicmp(str1, Mp, strlen(str1)) == 0) {
			// Mp += strlen(str1);
			diag_printf("Found required string [%s]\n", token_found = str1);
			return 0;
		} else if (strnicmp(str2, Mp, strlen(str2)) == 0) {
			// Mp += strlen(str2);
			diag_printf("Found required string [%s]\n", token_found = str2);
			return 1;
		} else if (strnicmp(str3, Mp, strlen(str3)) == 0) {
			diag_printf("Found required string [%s]\n", token_found = str3);
			return 2;
		}

		error_display(1, "Required token = [%s], [%s] or [%s], found [%.32s].\n", str1, str2, str3, next_tokens());

		advance_to_eoln(NULL);
		ignore_white_space();
		count++;
	}

	return -1;
	// exit (1);
}

int required_string_either_fred(char *str1, char *str2)
{
	ignore_white_space();

	while (*Mp != EOF_CHAR) {
		if (!strnicmp(str1, Mp, strlen(str1))) {
			// Mp += strlen(str1);
			diag_printf("Found required string [%s]\n", token_found = str1);
			return fred_parse_flag = 0;
		
		} else if (!strnicmp(str2, Mp, strlen(str2))) {
			// Mp += strlen(str2);
			diag_printf("Found required string [%s]\n", token_found = str2);
			return fred_parse_flag = 1;
		}

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (*Mp == EOF_CHAR)
		diag_printf("Unable to find either required token [%s] or [%s]\n", str1, str2);

	return -1;
	// exit (1);
}

//	Copy characters from instr to outstr until eoln is found, or until max
//	characters have been copied (including terminator).
void copy_to_eoln(char *outstr, char *more_terminators, char *instr, int max)
{
	int	count = 0;
	char	ch;
	char	terminators[128];

	Assert((more_terminators == NULL) || (strlen(more_terminators) < 125));

	terminators[0] = EOLN;
	terminators[1] = (char)EOF_CHAR;
	if (more_terminators != NULL)
		strcpy(&terminators[2], more_terminators);
	else
		terminators[2] = 0;

	while (((ch = *instr++) != 0) && (strchr(terminators, ch) == NULL)  && (count < max)) {
		*outstr++ = ch;
		count++;
	}

	if (count == max)
		error_display(0, "Token too long: [%s].  Length = %i.  Max is %i.\n", next_tokens(), strlen(next_tokens()), max);

	*outstr = 0;
}

//	Copy characters from instr to outstr until next white space is found, or until max
//	characters have been copied (including terminator).
void copy_to_next_white(char *outstr, char *instr, int max)
{
	int	count = 0;
	int	in_quotes = 0;
	char	ch;

	while (((ch = *instr++)>0) && (ch != EOLN) && (ch != EOF_CHAR) && (count < max)) {
		if ( ch == '\"' ) {
			in_quotes = !in_quotes;
			continue;
		}
		if ( !in_quotes && is_white_space(ch) )	// not in quotes, white space terminates string
			break;
		*outstr++ = ch;
		count++;
	}

	if (count == max)
		error_display(0, "Token too long: [%s].  Length = %i.  Max is %i.\n", next_tokens(), strlen(next_tokens()), max);

	*outstr = 0;
}

//Returns a null-terminated character string allocated with vm_malloc() with the data
char* alloc_text_until(char* instr, char* endstr)
{
	Assert(instr && endstr);
	char *foundstr = stristr(instr, endstr);
	if(foundstr == NULL)
	{
		Error(LOCATION, "Missing [%s] in file");
		longjmp(parse_abort, 3);
	}
	else
	{
		char* rstr = NULL;
		rstr = (char*) vm_malloc((foundstr - instr)*sizeof(char));

		if(rstr != NULL) {
			strncpy(rstr, instr, foundstr-instr);
			rstr[foundstr-instr] = '\0';
		} else {
			Error(LOCATION, "Could not allocate enough memory in alloc_text_until");
		}

		return rstr;
	}
}

//	Copy text until a certain string is matched.
//	For example, this is used to copy mission notes, scanning until $END NOTES:
// is found.
void copy_text_until(char *outstr, char *instr, char *endstr, int max_chars)
{
	char *foundstr;
	Assert(outstr && instr && endstr);

	foundstr = stristr(instr, endstr);

	if (foundstr == NULL) {
		nprintf(("Error", "Error.  Looking for [%s], but never found it.\n", endstr));
		longjmp(parse_abort, 3);
	}

	if (foundstr - instr + strlen(endstr) < (uint) max_chars) {
		strncpy(outstr, instr, foundstr - instr);
		outstr[foundstr - instr] = 0;

	} else {

		nprintf(("Error", "Error.  Too much text (%i chars, %i allowed) before %s\n",
			foundstr - instr - strlen(endstr), max_chars, endstr));

		longjmp(parse_abort, 4);
	}

	diag_printf("Here's the partial wad of text:\n%.30s\n", outstr);
}

// stuffs a string into a buffer.  Can get a string between " marks and stops
// when whitespace in encounted -- not to end of line
void stuff_string_white(char *pstr, int len)
{
	if(!len)
		len = NAME_LENGTH-1;

	ignore_white_space();
	copy_to_next_white(pstr, Mp, len);
	advance_to_next_white();
}

// Goober5000
void stuff_string_until(char *pstr, char *endstr, int len)
{
	if(!len)
		len = NAME_LENGTH-1;

	ignore_gray_space();
	copy_text_until(pstr, Mp, endstr, len);
	Mp += strlen(pstr);
	drop_trailing_white_space(pstr);
}

//WMC
//Used for allocating large blocks, eg of Python code
//Returns a null-terminated string allocated with malloc(),
//or NULL on failure
//Does depth checks for the start and end strings
char* alloc_block(char* startstr, char* endstr)
{
	Assert(startstr != NULL && endstr != NULL);
	Assert(stricmp(startstr, endstr));

	char* rval = NULL;
	uint elen = strlen(endstr);
	uint slen = strlen(startstr);
	uint flen = 0;

	//Skip the opening thing and any extra stuff
	required_string(startstr);
	ignore_white_space();

	//Allocate it
	char* pos = Mp;

	//Depth checking
	int level = 1;
	while(*pos++ != EOF_CHAR)
	{
		if(!strnicmp(pos, startstr, slen))
		{
			level++;
		}
		else if(!strnicmp(pos, endstr, elen))
		{
			level--;
		}

		if(level<=0)
		{
			break;
		}
	}

	//Check that we left the file
	if(level > 0)
	{
		Error(LOCATION, "Unclosed pair of \"%s\" and \"%s\" in file", startstr, endstr);
		longjmp(parse_abort, 3);
	}
	else
	{
		//Set final length for faster calcs
		flen = pos-Mp;

		//Allocate the memory
		rval = (char*) vm_malloc((flen)*sizeof(char));

		//Copy the text (if memory was allocated)
		if(rval != NULL) {
			strncpy(rval, Mp, flen);
			rval[flen] = '\0';
		} else {
			return NULL;
		}
	}

	//Skip the copied stuff
	Mp += flen;
	required_string(endstr);
	return rval;
}

//	Stuff a string into a string buffer.
//	Supports various FreeSpace primitive types.  If 'len' is supplied, it will override
// the default string length if using the F_NAME case.
void stuff_string(char *pstr, int type, char *terminators, int len)
{	
	char read_str[PARSE_BUF_SIZE] = "";
	int read_len = PARSE_BUF_SIZE;
	int final_len = len;
	int tag_id;

	switch (type) {
		case F_RAW:
			ignore_gray_space();
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;
		case F_NAME:
			if (!len){
				final_len = NAME_LENGTH;
			}
			ignore_gray_space();
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;

		case F_DATE:
			ignore_gray_space();			
			final_len = DATE_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;

		case F_NOTES:
			ignore_white_space();
			final_len = NOTES_LENGTH;
			copy_text_until(read_str, Mp, "$End Notes:", read_len);
			Mp += strlen(read_str);
			required_string("$End Notes:");
			break;

		case F_FILESPEC:
			ignore_gray_space();
			final_len = FILESPEC_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;
		// F_MULTITEXTOLD keeping for backwards compatability with old missions
		// can be deleted once all missions are using new briefing format

		case F_MULTITEXTOLD:		
			ignore_white_space();
			final_len = NOTES_LENGTH;
			copy_text_until(read_str, Mp, "$End Briefing Text:", read_len);
			Mp += strlen(read_str);
			required_string("$End Briefing Text:");
			break;

		case F_MULTITEXT:		
			if (!len){
				final_len = MULTITEXT_LENGTH;
			}
			ignore_white_space();
			copy_text_until(read_str, Mp, "$end_multi_text", read_len);
			Mp += strlen(read_str);
			drop_trailing_white_space(read_str);
			required_string("$end_multi_text");
			break;

		case F_PATHNAME:
			ignore_gray_space();
			final_len = PATHNAME_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;

		case F_MESSAGE:
			ignore_gray_space();
			final_len = MESSAGE_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;		

		default:
			Assert(0);
	}

	// now we want to do any final localization
	if(type != F_RAW)
	{
		lcl_ext_localize(read_str, pstr, final_len, &tag_id);

		// if the hash localized text hash table is active and we have a valid external string - hash it
		if(fhash_active() && (tag_id > -2)){
			fhash_add_str(pstr, tag_id);
		}
	}
	else
	{
		strcpy(pstr, read_str);
	}

	diag_printf("Stuffed string = [%.30s]\n", pstr);
}

// stuff a string from a given source rather than global
void stuff_string_ex(char *pstr, int type, char *terminators, int len)
{	
	char read_str[PARSE_BUF_SIZE] = "";
	int read_len = PARSE_BUF_SIZE;
	int final_len = len;
	int tag_id;

	switch (type) {
		case F_NAME:
			if (!len){
				final_len = NAME_LENGTH;
			}
			ignore_gray_space_ex();
			copy_to_eoln(read_str, terminators, ex_Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln_ex(terminators);
			break;
/*
		case F_DATE:
			ignore_gray_space_ex(ex_Mp);			
			final_len = DATE_LENGTH;
			copy_to_eoln(read_str, terminators, ex_Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln_ex(ex_Mp, terminators);
			break;

		case F_NOTES:
			ignore_white_space_ex(ex_Mp);
			final_len = NOTES_LENGTH;
			copy_text_until(read_str, Mp, "$End Notes:", read_len);
			ex_Mp += strlen(read_str);
			required_string("$End Notes:");
			break;

		case F_FILESPEC:
			ignore_gray_space();
			final_len = FILESPEC_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;
		// F_MULTITEXTOLD keeping for backwards compatability with old missions
		// can be deleted once all missions are using new briefing format

		case F_MULTITEXTOLD:		
			ignore_white_space();
			final_len = NOTES_LENGTH;
			copy_text_until(read_str, Mp, "$End Briefing Text:", read_len);
			Mp += strlen(read_str);
			required_string("$End Briefing Text:");
			break;

		case F_MULTITEXT:		
			if (!len){
				final_len = MULTITEXT_LENGTH;
			}
			ignore_white_space();
			copy_text_until(read_str, Mp, "$end_multi_text", read_len);
			Mp += strlen(read_str);
			drop_trailing_white_space(read_str);
			required_string("$end_multi_text");
			break;

		case F_PATHNAME:
			ignore_gray_space();
			final_len = PATHNAME_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;

		case F_MESSAGE:
			ignore_gray_space();
			final_len = MESSAGE_LENGTH;
			copy_to_eoln(read_str, terminators, Mp, read_len);
			drop_trailing_white_space(read_str);
			advance_to_eoln(terminators);
			break;		
*/
		default:
			Assert(0);
	}

	// now we want to do any final localization
	lcl_ext_localize(read_str, pstr, final_len, &tag_id);

	// if the hash localized text hash table is active and we have a valid external string - hash it
	if(fhash_active() && (tag_id > -2)){
		fhash_add_str(pstr, tag_id);
	}

	diag_printf("Stuffed string = [%.30s]\n", pstr);
}

// stuff a string, but only until the end of a line. don't ignore leading whitespace. close analog of fgets()/cfgets()
void stuff_string_line(char *pstr, int len)
{
	char read_str[PARSE_BUF_SIZE] = "";
	int read_len = PARSE_BUF_SIZE;
	int final_len = len;
	int tag_id;
	
	// read in a line
	final_len = len;
	copy_to_eoln(read_str, "\n", Mp, read_len);
	drop_trailing_white_space(read_str);
	advance_to_eoln("");
	Mp++;
			
	// now we want to do any final localization
	lcl_ext_localize(read_str, pstr, final_len, &tag_id);

	// if the hash localized text hash table is active and we have a valid external string - hash it
	if(fhash_active() && (tag_id > -2)){
		fhash_add_str(pstr, tag_id);
	}

	diag_printf("Stuffed string = [%.30s]\n", pstr);
}

// Exactly the same as stuff string only Malloc's the buffer. 
//	Supports various FreeSpace primitive types.  If 'len' is supplied, it will override
// the default string length if using the F_NAME case.
char *stuff_and_malloc_string( int type, char *terminators, int len)
{
	int l;

	char tmp_result[MAX_TMP_STRING_LENGTH];

	stuff_string(tmp_result, type, terminators, len);
	drop_white_space(tmp_result);

	l = strlen(tmp_result);
	Assert(l < MAX_TMP_STRING_LENGTH);		// Get John!!
	if (l < 1)
		return NULL;

	return vm_strdup(tmp_result);
}

void stuff_malloc_string(char **dest, int type, char *terminators, int len)
{
	Assert(dest != NULL); //wtf?
	
	char *new_val = stuff_and_malloc_string(type, terminators, len);
	
	if(new_val != NULL)
	{
		if((*dest) != NULL) {
			vm_free(*dest);
		}
		
		(*dest) = new_val;
	}
}

// After reading a multitext string, you can call this function to convert any newlines into
// spaces, so it's a one paragraph string (I.e. as in MS-Word).
//
void compact_multitext_string(char *str)
{
	unsigned int i;

	for (i=0; i<strlen(str); i++)
		if (str[i] == '\n')
			str[i] = ' ';
}

int maybe_convert_foreign_character(int ch)
{
	// time to do some special foreign character conversion			
	switch (ch) {
		case -4:
			ch = 129;
			break;

		case -28:
			ch = 132;
			break;

		case -10:
			ch = 148;
			break;

		case -23:
			ch = 130;
			break;

		case -30:
			ch = 131;
			break;

		case -25:
			ch = 135;
			break;

		case -21:
			ch = 137;
			break;

		case -24:
			ch = 138;
			break;

		case -17:
			ch = 139;
			break;

		case -18:
			ch = 140;
			break;

		case -60:
			ch = 142;
			break;

		case -55:
			ch = 144;
			break;

		case -12:
			ch = 147;
			break;

		case -14:
			ch = 149;
			break;

		case -5:
			ch = 150;
			break;

		case -7:
			ch = 151;
			break;

		case -42:
			ch = 153;
			break;

		case -36:
			ch = 154;
			break;

		case -31:
			ch = 160;
			break;

		case -19:
			ch = 161;
			break;

		case -13:
			ch = 162;
			break;

		case -6:
			ch = 163;
			break;

		case -32:
			ch = 133;
			break;

		case -22:
			ch = 136;
			break;

		case -20:
			ch = 141;
			break;
	}
	
	return ch;
}

// Strip comments from a line of input.
int strip_comments(char *readp, int in_comment)
{	
	int	ch;
	char	*writep = readp;

	while ((ch = *readp) != COMMENT_CHAR) {
		if (*readp == 0) {
			*writep = 0;
			return in_comment;
		}

		if (!in_comment) {
			if (Fred_running)
				*writep = (char) ch;
			else
				*writep = (char) maybe_convert_foreign_character(ch);

			writep++;
		}
		
		readp++;	
	}

	*writep = EOLN;
	writep[1] = 0;
	
	return in_comment;	
}

/*#if 0
void strip_all_comments( char *readp, char *writep )
{
	int	ch;
	//char	*writep = readp;

	while ( *readp != EOF_CHAR ) {
		ch = *readp;
		if ( ch == COMMENT_CHAR ) {
			while ( *readp != EOLN )
				readp++;

			*writep = EOLN;
			writep++;
			// get to next character after EOLN
			readp++;
		} else if ( (ch == '/') && (readp[1] == '*')) {			// Start of multi-line comment
			int done;
			
			done = 0;
			while ( !done ) {
				while ( *readp != '*' )
					readp++;
				if ( readp[1] == '/' ) {
					readp += 2;
					done = 1;
				} else {
					readp++;
				}
			}
		} else {
			*writep = (char)ch;
			*writep++;
			readp++;
		}
	}

	*writep = (char)EOF_CHAR;
}
#endif*/

int parse_get_line(char *lineout, int max_line_len, char *start, int max_size, char *cur)
{
	char * t = lineout;
	int i, num_chars_read=0;
	char c;


	for ( i = 0; i < max_line_len-1; i++ ) {
		do {
			if ( (cur - start) >= max_size ) {
				*lineout = 0;
				if ( lineout > t ) {		
					return num_chars_read;
				} else {
					return 0;
				}
			}
			c = *cur++;
			num_chars_read++;
		} while ( c == 13 );

		*lineout++ = c;
		if ( c=='\n' ) break;
	}

	*lineout++ = 0;
	return  num_chars_read;
}

//	Read mission text, stripping comments.
//	When a comment is found, it is removed.  If an entire line
//	consisted of a comment, a blank line is left in the input file.
// Goober5000 - added ability to read somewhere other than Mission_text
void read_file_text(char *filename, int mode, char *processed_text, char *raw_text)
{
	// copy the filename
	if (!filename)
		longjmp(parse_abort, 10);
	strcpy(Current_filename, filename);

	// read the raw text
	read_raw_file_text(filename, mode, raw_text);

	// process it (strip comments)
	process_raw_file_text(processed_text, raw_text);
}

// Goober5000
void read_file_text_from_array(char *array, char *processed_text, char *raw_text)
{
	// we have no filename, so copy a substitute
	strcpy(Current_filename, "internal default file");

	// if we have no raw buffer, set it as the array
	if (raw_text == NULL)
		raw_text = array;

	// copy text in the array (but only if the raw text and the array are not the same)
	if (raw_text != array)
		strcpy(raw_text, array);

	// process the text
	process_raw_file_text(processed_text, raw_text);
}

// Goober5000
int is_unicode(char *text)
{
	if (!strncmp(text, "\xEF\xBB\xBF", 3))		// UTF-8
		return 1;

	if (!strncmp(text, "\xFE\xFF", 2))			// UTF-16 big-endian
		return 1;

	if (!strncmp(text, "\xFF\xFE", 2))			// UTF-16 little-endian
		return 1;

	if (!strncmp(text, "\x00\x00\xFE\xFF", 4))	// UTF-32 big-endian
		return 1;

	if (!strncmp(text, "\xFF\xFE\x00\x00", 4))	// UTF-32 little-endian
		return 1;

	return 0;
}

// Goober5000
void read_raw_file_text(char *filename, int mode, char *raw_text)
{
	CFILE	*mf;
	int	file_is_encrypted;
	int file_is_unicode;

	Assert(filename);

	mf = cfopen(filename, "rb", CFILE_NORMAL, mode);
	if (mf == NULL)
	{
		nprintf(("Error", "Wokka!  Error opening file (%s)!\n", filename));
		longjmp(parse_abort, 5);
	}

	// read the entire file in
	int file_len = cfilelength(mf);

	//	If you hit this assert, it is probably telling you the obvious.  The file
	//	you are trying to read is truly too large.  Look at *filename to see the file name.
	Assert(file_len < MISSION_TEXT_SIZE);

	// read first 10 bytes to determine if file is encrypted
	cfread(raw_text, MIN(file_len, 10), 1, mf);
	file_is_encrypted = is_encrypted(raw_text);
	cfseek(mf, 0, CF_SEEK_SET);

	// Goober5000 - also determine if file is Unicode
	file_is_unicode = is_unicode(raw_text);
	if ( file_is_unicode )
	{
		nprintf(("Error", "Wokka!  File (%s) is in Unicode format!\n", filename));
		longjmp(parse_abort, 5);
	}

	if ( file_is_encrypted )
	{
		int	unscrambled_len;
		char	*scrambled_text;
		scrambled_text = (char*)vm_malloc(file_len+1);
		Assert(scrambled_text);
		cfread(scrambled_text, file_len, 1, mf);
		// unscramble text
		unencrypt(scrambled_text, file_len, raw_text, &unscrambled_len);
		file_len = unscrambled_len;
		vm_free(scrambled_text);
	}
	else
	{
		cfread(raw_text, file_len, 1, mf);
	}

	cfclose(mf);
}

// Goober5000
void process_raw_file_text(char *processed_text, char *raw_text)
{
	char	*mp;
	char	*mp_raw;
	char outbuf[PARSE_BUF_SIZE], *str;
	int in_comment = 0;
	int raw_text_len = strlen(raw_text);

	mp = processed_text;
	mp_raw = raw_text;

	// strip comments from raw text, reading into file_text
	int num_chars_read = 0;
	while ( (num_chars_read = parse_get_line(outbuf, PARSE_BUF_SIZE, raw_text, raw_text_len, mp_raw)) != 0 ) {
		mp_raw += num_chars_read;

		in_comment = strip_comments(outbuf, in_comment);

		str = outbuf;
		while (*str) {
			if (*str == -33) {
				*mp++ = 's';
				*mp++ = 's';
				str++;

			} else
				*mp++ = *str++;
		}

//		strcpy(mp, outbuf);
//		mp += strlen(outbuf);
	}

	*mp = *mp_raw = (char)EOF_CHAR;
/*
	while (cfgets(outbuf, PARSE_BUF_SIZE, mf) != NULL) {
		if (strlen(outbuf) >= PARSE_BUF_SIZE-1)
			error_display(0, "Input string too long.  Max is %i characters.\n%.256s\n", PARSE_BUF_SIZE, outbuf);

		//	If you hit this assert, it is probably telling you the obvious.  The file
		//	you are trying to read is truly too large.  Look at *filename to see the file name.
		Assert(mp_raw - file_text_raw + strlen(outbuf) < MISSION_TEXT_SIZE);
		strcpy(mp_raw, outbuf);
		mp_raw += strlen(outbuf);

		in_comment = strip_comments(outbuf, in_comment);
		strcpy(mp, outbuf);
		mp += strlen(outbuf);
	}
	
	*mp = *mp_raw = (char)EOF_CHAR;
*/

}

void debug_show_mission_text()
{
	char	*mp = Mission_text;
	char	ch;

	while ((ch = *mp++) != EOF_CHAR)
		printf("%c", ch);
}

float atof2()
{
	char	ch;

	my_errno = 0;
	ignore_white_space();

	ch = *Mp;

	if ((ch != '.') && (ch != '-') && (ch != '+') && ((ch < '0') || (ch > '9'))) {
		error_display(1, "Expecting float, found [%.32s].\n", next_tokens());
		my_errno = 1;
		return 0.0f;
	} else
		return (float)atof(Mp);

}

int atoi2()
{
	char	ch;

	my_errno = 0;

	ignore_white_space();

	ch = *Mp;

	if ((ch != '-') && (ch != '+') && ((ch < '0') || (ch > '9'))) {
		error_display(1, "Expecting int, found [%.32s].\n", next_tokens());
		my_errno = 1;
		return 0;
	} else
		return atoi(Mp);

}

int atoi2_ex()
{
	char	ch;

//	my_errno = 0;

	ignore_white_space_ex();

	ch = *ex_Mp;

	if ((ch != '-') && (ch != '+') && ((ch < '0') || (ch > '9'))) {
//		error_display(1, "Expecting int, found [%.32s].\n", next_tokens());
//		my_errno = 1;
		return 0;
	} else
		return atoi(ex_Mp);

}

//	Stuff a floating point value pointed at by Mp.
//	Advances past float characters.
void stuff_float(float *f)
{
	*f = atof2();

	if (my_errno)
		skip_token();
	else
		Mp += strspn(Mp, "+-0123456789.");

	if (*Mp ==',')
		Mp++;

	diag_printf("Stuffed float: %f\n", *f);
}

int stuff_float_optional(float *f)
{
	int skip_len;
	bool comma = false;
	
	ignore_white_space();
	skip_len = strspn(Mp, "+-0123456789.");
	if(*(Mp+skip_len) == ',') {
		comma = true;
	}
	
	if(skip_len < 0)
	{
		if(comma) {
			Mp++;
			return 1;
		} else {
			return 0;
		}
	}

	stuff_float(f);
	return 2;
}

//	Stuff an integer value pointed at by Mp.
//	Advances past integer characters.
void stuff_int(int *i)
{
	*i = atoi2();

	if (my_errno)
		skip_token();
	else
		Mp += strspn(Mp, "+-0123456789");

	if (*Mp ==',')
		Mp++;

	diag_printf("Stuffed int: %i\n", *i);
}

// Stuff an integer value pointed at by ex_Mp.
void stuff_int_ex(int *i)
{
	*i = atoi2_ex();

	ex_Mp += strspn(ex_Mp, "+-0123456789");

	if (*ex_Mp ==',')
		ex_Mp++;

//	diag_printf("Stuffed int: %i\n", *i);
}

//Stuffs boolean value.
//Passes things off to stuff_boolean(bool)
void stuff_boolean(int *i, bool a_to_eol)
{
	bool tempb;
	stuff_boolean(&tempb, a_to_eol);
	if(tempb)
		*i = 1;
	else
		*i = 0;
}

// Stuffs a boolean value pointed at by Mp.  
// YES/NO (supporting 1/0 now as well)
// Now supports localization :) -WMC

void stuff_boolean(bool *b, bool a_to_eol)
{
	char token[32];
	stuff_string_white(token, sizeof(token)/sizeof(char));
	if(a_to_eol)
		advance_to_eoln(NULL);

	if( isdigit(token[0]))
	{
		if(token[0] != '0')
			*b = true;
		else
			*b = false;
	}
	else
	{
		if(!stricmp(token, "yes")
			|| !stricmp(token, "true")
			|| !stricmp(token, "ja")		//German
			|| !stricmp(token, "Oui")		//French
			|| !stricmp(token, "si")		//Spanish
			|| !stricmp(token, "ita vero")	//Latin
			|| !stricmp(token, "HIja'") || !stricmp(token, "HISlaH"))	//Klingon
		{
			*b = true;
		}
		else if(!stricmp(token, "no")
			|| !stricmp(token, "false")
			|| !stricmp(token, "nein")		//German
			|| !stricmp(token, "Non")		//French
			//I don't know spanish for "no"
			//But according to altavista, spanish for "No" is "no"
			//Go figure.
			|| !stricmp(token, "minime")	//Latin
			|| !stricmp(token, "ghobe'"))	//Klingon
		{
			*b = false;
		}
		else
		{
			*b = false;
			Warning(LOCATION, "Boolean '%s' type unknown; assuming 'no/false'",token);
		}
	}

	diag_printf("Stuffed bool: %b\n", *b);
}

int stuff_bool_list(bool *blp, int max_bools)
{
	int count = 0;
	bool trash_buf = false;

	ignore_white_space();
	
	if (*Mp != '(') {
		error_display(1, "Reading boolean list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;

	ignore_white_space();

	while(*Mp != ')')
	{
		if(count < max_bools)
		{
			stuff_boolean(&blp[count++], false);
			ignore_white_space();
			
			//Since Bobb has set a precedent, allow commas for bool lists -WMC
			if(*Mp == ',')
			{
				Mp++;
				ignore_white_space();
			}
		}
		else
		{
			trash_buf = true;
			break;
		}
	}

	if(trash_buf)
	{
		error_display(0, "Boolean list has more than allowed arguments; max is %d. Arguments over max will be ignored.", max_bools);
		while(*Mp != ')')
		{
			stuff_boolean(&trash_buf, false);
			ignore_white_space();
		}
	}

	Mp++;

	return count;
}


//	Stuff an integer value pointed at by Mp.
//	Advances past integer characters.
void stuff_ubyte(ubyte *i)
{
	int	temp;

	temp = atoi2();

	*i = (ubyte)temp;

	if (my_errno)
		skip_token();
	else
		Mp += strspn(Mp, "+-0123456789");

	if (*Mp == ',')
		Mp++;

	diag_printf("Stuffed byte: %i\n", *i);
}

// Stuffs a list of strings
int stuff_string_list(char slp[][NAME_LENGTH], int max_strings)
{
	int count = 0;
	ignore_white_space();

	if ( *Mp != '(' ) {
		error_display(1, "Reading string list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 100);
	}

	Mp++;

	ignore_white_space();

	while (*Mp != ')') {
		assert ( count < max_strings );
		Assert ( *Mp == '\"' );					// should always be enclosed in quotes

		get_string( slp[count++] );
		ignore_white_space();
	}

	Mp++;

	return count;
}

//	Stuffs an integer list.
//	This is of the form ( i* )
//	  where i is an integer.
// For example, (1) () (1 2 3) ( 1 ) are legal integer lists.
int stuff_int_list(int *ilp, int max_ints, int lookup_type)
{
	int	count = 0, ok_flag = 1, dummy;
	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Reading integer list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;
	ignore_white_space();

	while (*Mp != ')') {
		Assert(count < max_ints);
		if (*Mp == '"') {
			int num = 0;
			char str[128];

			get_string(str);
			switch (lookup_type) {
				case SHIP_TYPE:
					num = ship_name_lookup(str);	// returns index of Ship[] entry with name
					break;

				case SHIP_INFO_TYPE:
					ok_flag = 1;
					num = ship_info_lookup(str);	// returns index of Ship_info[] entry with name
					if (num < 0)
						ok_flag = 0;
					break;

				case WEAPON_POOL_TYPE:
					ok_flag = 1;
					num = weapon_info_lookup(str);
					if (num < 0)
						ok_flag = 0;
					break;

				case WEAPON_LIST_TYPE:
					num = weapon_info_lookup(str);
					if (num < 0)
						num = -2;
					break;

				case RAW_INTEGER_TYPE:
					num = atoi(str);
					break;

				default:
					Error(LOCATION,"Unknown lookup_type in stuff_int_list");
					break;
			}

			if (ok_flag) {
				if (num == -1) {
					Error(LOCATION, "Unable to find string \"%s\" in stuff_int_list\n\nMany possible sources for this error.  Get a programmer!\n", str);
				} else if (num == -2) {
					if (strlen(str) > 0) {
						if(strlen(parse_error_text) > 0){
							Warning(LOCATION, "Unable to find WEAPON_LIST_TYPE string \"%s\" %s.\n", str, parse_error_text);
						}else{
							Warning(LOCATION, "Unable to find WEAPON_LIST_TYPE string \"%s\" in stuff_int_list\n\nMany possible sources for this error.  Get a programmer!\n", str);
						}
					}
				}

				if (num < 0)  // other negatives used to bypass the above error trap, but should be -1
					num = -1;

				ilp[count++] = num;
			}

		} else {
			if (ok_flag)
				stuff_int(&ilp[count++]);
			else
				stuff_int(&dummy);
		}
		
		ignore_white_space();
	}

	Mp++;

	return count;
}

//Stuffs an integer list like stuff_int_list.
int stuff_float_list(float* flp, int max_floats)
{
	int count = 0;
	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Reading float list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;
	ignore_white_space();
	while(*Mp != ')')
	{
		Assert(count < max_floats);
		stuff_float(&flp[count++]);
		ignore_white_space();
	}

	Mp++;

	return count;
}

//	Marks an integer list.
//	This is of the form ( i* )
//	  where i is an integer.
//	If a specified string is found in the lookup and its value is 7, then the 7th value
//	in the array is set.
void mark_int_list(int *ilp, int max_ints, int lookup_type)
{
	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Marking integer list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;
	ignore_white_space();

	while (*Mp != ')') {
		if (*Mp == '"') {
			int num = 0;
			char str[128];

			get_string(str);
			switch(lookup_type) {
				case SHIP_TYPE:
					num = ship_name_lookup(str);	// returns index of Ship[] entry with name
					break;
			
				case SHIP_INFO_TYPE:
					num = ship_info_lookup(str);	// returns index of Ship_info[] entry with name
					break;
	
				case WEAPON_LIST_TYPE:
					num = weapon_info_lookup(str);
					break;

				default:
					Error(LOCATION,"Unknown lookup_type in stuff_int_list");
					break;
			}

			if ( (num < 0) || (num >= max_ints) )
				Error(LOCATION, "Unable to find string \"%s\" in mark_int_list.\n", str);

//			ilp[num] = 1;
		
		} else {
			int	tval;

			stuff_int(&tval);
			Assert((tval >= 0) && (tval < max_ints));
			ilp[tval] = 1;
		}
		
		ignore_white_space();
	}

	Mp++;

}


//	Stuff a vector, which is 3 floats.
void stuff_vector(vec3d *vp)
{
	stuff_float(&vp->xyz.x);
	stuff_float(&vp->xyz.y);
	stuff_float(&vp->xyz.z);
}

void stuff_parenthesized_vector(vec3d *vp)
{
	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Reading parenthesized vec3d.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 11);
	} else {
		Mp++;
		stuff_vector(vp);
		ignore_white_space();
		if (*Mp != ')') {
			error_display(1, "Reading parenthesized vec3d.  Found [%c].  Expecting ')'.\n", *Mp);
			longjmp(parse_abort, 12);
		}
		Mp++;
	}

}

//	Stuffs vector list.
//	This is of the form ( (vector)* )
//	  where vector is a vector
// For example, ( (1 2 3) (2 3 4) (2 3 5) )
//		 is a vector list of three vectors.
int stuff_vector_list(vec3d *vlp, int max_vecs)
{
	int	count = 0;

	ignore_white_space();

	if (*Mp != '(') {
		error_display(1, "Reading integer list.  Found [%c].  Expecting '('.\n", *Mp);
		longjmp(parse_abort, 6);
	}

	Mp++;

	ignore_white_space();

	while (*Mp != ')') {
		Assert(count < max_vecs);
		stuff_parenthesized_vector(&vlp[count++]);
		
		ignore_white_space();
	}

	Mp++;

	return count;
}


//	Stuff a matrix, which is 3 vectors.
void stuff_matrix(matrix *mp)
{
	stuff_vector(&mp->vec.rvec);
	stuff_vector(&mp->vec.uvec);
	stuff_vector(&mp->vec.fvec);
}


//	Given a string, find it in a string array.
//	*descrtiption is only used for diagnostics in case it can't be found.
//	*str1 is the string to be found.
//	*strlist is the list of strings to search.
//	max is the number of entries in *strlist to scan.
int string_lookup(char *str1, char *strlist[], int max, char *description, int say_errors)
{
	int	i;

	for (i=0; i<max; i++) {
		Assert(strlen(strlist[i]) != 0);

		if (!stricmp(str1, strlist[i]))
			return i;
	}

	if (say_errors)
		error_display(0, "Unable to find [%s] in %s list.\n", str1, description);

	return -1;
}

//	Find a required string (*id), then stuff the text of type f_type that
// follows it at *addr.  *strlist[] contains the strings it should try to
// match.
void find_and_stuff(char *id, int *addr, int f_type, char *strlist[], int max, char *description)
{
	char	token[128];

	required_string(id);
	stuff_string(token, f_type, NULL);
	*addr = string_lookup(token, strlist, max, description, 1);
}

void find_and_stuff_optional(char *id, int *addr, int f_type, char *strlist[], int max, char *description)
{
	char token[128];
	
	if(optional_string(id))
	{
		stuff_string(token, f_type, NULL);
		*addr = string_lookup(token, strlist, max, description, 1);
	}
}

//	Mp points at a string.
//	Find the string in the list of strings *strlist[].
// Returns the index of the match, -1 if none.
int match_and_stuff(int f_type, char *strlist[], int max, char *description)
{
	char	token[128];

	stuff_string(token, f_type, NULL);
	return string_lookup(token, strlist, max, description, 0);
}

void find_and_stuff_or_add(char *id, int *addr, int f_type, char *strlist[], int *total,
	int max, char *description)
{
	char	token[128];

	*addr = -1;
	required_string(id);
	stuff_string(token, f_type, NULL);
	if (*total)
		*addr = string_lookup(token, strlist, *total, description, 0);

	if (*addr == -1)  // not in list, so lets try and add it.
	{
		Assert(*total < max);
		strcpy(strlist[*total], token);
		*addr = (*total)++;
	}
}

void reset_parse()
{
	Mp = Mission_text;

	Warning_count = 0;
	Error_count = 0;

	strcpy(parse_error_text, "");//better error mesages-Bobboau
}

void reset_parse_ex(char *text)
{
	ex_Mp = text;
}

// Display number of warnings and errors at the end of a parse.
void display_parse_diagnostics()
{
	nprintf(("Parse", "\nParse complete.\n"));
	nprintf(("Parse", "%i errors.  %i warnings.\n", Error_count, Warning_count));
}

// Splits a string into 2 lines if the string is wider than max_pixel_w pixels.  A null
// terminator is placed where required to make the first line <= max_pixel_w.  The remaining
// text is returned (leading whitespace removed).  If the line doesn't need to be split,
// NULL is returned.
char *split_str_once(char *src, int max_pixel_w)
{
	char *brk = NULL;
	int i, w, len, last_was_white = 0;

	Assert(src);
	Assert(max_pixel_w > 0);
	
	gr_get_string_size(&w, NULL, src);
	if ( w <= max_pixel_w )
		return NULL;  // string doesn't require a cut

	len = strlen(src);
	for (i=0; i<len; i++) {
		gr_get_string_size(&w, NULL, src, i);
		if ( w > max_pixel_w )
			break;

		if (src[i] == '\n') {  // reached natural end of line
			src[i] = 0;
			return src + i + 1;
		}

		if (is_white_space(src[i])) {
			if (!last_was_white)
				brk = src + i;

			last_was_white = 1;

		} else {
			last_was_white = 0;
		}
	}

	if (!brk) {
		brk = src + i;
	}

	*brk = 0;
	src = brk + 1;
	while (is_white_space(*src))
		src++;

	if (!*src)
		return NULL;  // end of the string anyway
		
	if (*src == '\n')
		src++;

	return src;
}

#define SPLIT_STR_BUFFER_SIZE	512

// --------------------------------------------------------------------------------------
// split_str() 
//
// A general function that will split a string into several lines.  Lines are allowed up
// to max_pixel_w pixels.  Breaks are found in white space.
//
// Supports \n's in the strings!
//
// parameters:		src			=>		source string to be broken up
//						max_pixel_w	=>		max width of line in pixels
//						n_chars		=>		output array that will hold number of characters in each line
//						p_str			=>		output array of pointers to start of lines within src
//						max_lines	=>		limit of number of lines to break src up into
//						ignore_char	=>		OPTIONAL parameter (default val -1).  Ignore words starting with this character
//												This is useful when you want to ignore embedded control information that starts
//												with a specific character, like $ or #
//
//	returns:			number of lines src is broken into
//						-1 is returned when an error occurs
//
int split_str(char *src, int max_pixel_w, int *n_chars, char **p_str, int max_lines, char ignore_char)
{
	char buffer[SPLIT_STR_BUFFER_SIZE];
	char *breakpoint = NULL;
	int sw, new_line = 1, line_num = 0, last_was_white = 0;
	int ignore_until_whitespace, buf_index;
	
	// check our assumptions..
	Assert(src != NULL);
	Assert(n_chars != NULL);
	Assert(p_str != NULL);
	Assert(max_lines > 0);
	Assert(max_pixel_w > 0);
	
	memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);
	buf_index = 0;
	ignore_until_whitespace = 0;

	// get rid of any leading whitespace
	while (is_white_space(*src))
		src++;

	new_line = 1;
	p_str[0] = NULL;

	// iterate through chars in line, keeping track of most recent "white space" location that can be used
	// as a line splitting point if necessary
	for (; *src; src++) {
		if (line_num >= max_lines)
			return line_num;  // time to bail out

		// starting a new line of text, init stuff for that
		if (new_line) {
			p_str[line_num] = NULL;
			if (is_gray_space(*src))
				continue;

			p_str[line_num] = src;
			breakpoint = NULL;
			new_line = 0;
		}

		// maybe skip leading whitespace
		if (ignore_until_whitespace) {
			if ( is_white_space(*src) )
				ignore_until_whitespace = 0;

			continue;
		}

		// if we have a newline, split the line here
		if (*src == '\n') {
			n_chars[line_num] = src - p_str[line_num];  // track length of line
			line_num++;
			p_str[line_num] = NULL;
			new_line = 1;

			memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);
			buf_index = 0;
			continue;
		}

		if (*src == ignore_char) {
			ignore_until_whitespace = 1;
			continue;
		}

		if (is_gray_space(*src)) {
			if (!last_was_white)  // track at first whitespace in a series of whitespace
				breakpoint = src;

			last_was_white = 1;

		} else {
			// indicate next time around that this wasn't a whitespace character
			last_was_white = 0;
		}

		// throw it in our buffer
		buffer[buf_index] = *src;
		buf_index++;
		buffer[buf_index] = 0;  // null terminate it
	
		gr_get_string_size(&sw, NULL, buffer);
		if (sw >= max_pixel_w) {
			char *end;

			if (breakpoint) {
				end = src = breakpoint;

			} else {
				end = src;  // force a split here since to whitespace
				src--;  // reuse this character in next line
			}

			n_chars[line_num] = end - p_str[line_num];  // track length of line
			Assert(n_chars[line_num]);
			line_num++;
			p_str[line_num] = NULL;
			new_line = 1;

			memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);
			buf_index = 0;
			continue;
		}
	}	// end for

	if (p_str[line_num]) {
		n_chars[line_num] = src - p_str[line_num];  // track length of line
		Assert(n_chars[line_num]);
		line_num++;
	}

	return line_num;
}

// Goober5000
void end_string_at_first_hash_symbol(char *src)
{
	Assert(src);

	char *p = get_pointer_to_first_hash_symbol(src);

	if (p)
	{
		*p = '\0';
	}
}

// Goober5000
// accounts for the dumb communications != communication, etc.
int subsystem_stricmp(const char *str1, const char *str2)
{
	Assert(str1 && str2);

	// ensure len-1 will be valid
	if (!*str1 || !*str2)
		return stricmp(str1, str2);

	// calc lengths
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	// get rid of trailing s on s1?
	if (tolower(*(str1+len1-1) == 's'))
		len1--;

	// get rid of trailing s on s2?
	if (tolower(*(str2+len2-1) == 's'))
		len2--;

	// once we remove the trailing s on both names, they should be the same length
	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;

	// now do the comparison
	return strnicmp(str1, str2, len1);
}

// Goober5000
// current algorithm adapted from http://www.codeproject.com/string/stringsearch.asp
char *stristr(const char *str, const char *substr)
{
	// check for null and insanity
	Assert(str);
	Assert(substr);
	if (str == NULL || substr == NULL || *substr == '\0')
		return NULL;

	// save both a lowercase and an uppercase version of the first character of substr
	char substr_ch_lower = tolower(*substr);
	char substr_ch_upper = toupper(*substr);

	// find the maximum distance to search
	char *upper_bound = (char *)str + strlen(str) - strlen(substr);

	// loop through every character of str
	for (char *start = (char *)str; start <= upper_bound; start++)
	{
		// check first character of substr
		if ((*start == substr_ch_upper) || (*start == substr_ch_lower))
		{
			// first character matched, so check the rest
			for (char *str_ch = start+1, *substr_ch = (char *)substr+1; *substr_ch != '\0'; str_ch++, substr_ch++)
			{
				// character match?
				if (*str_ch == *substr_ch)
					continue;

				// converted character match?
				if (tolower(*str_ch) == tolower(*substr_ch))
					continue;

				// mismatch
				goto stristr_continue_outer_loop;
			}

			// finished inner loop with success!
			return start;
		}

stristr_continue_outer_loop:
		/* NO-OP */ ;
	}

	// no match
	return NULL;
}

// Goober5000
char *get_pointer_to_first_hash_symbol(char *src)
{
	Assert(src);

	return strchr(src, '#');
}

// Goober5000
int replace_one(char *str, char *oldstr, char *newstr, unsigned int max_len, int range)
{
	Assert(max_len <= MISSION_TEXT_SIZE);
	Assert(str && oldstr && newstr);

	// search
	char *ch = stristr(str, oldstr);

	// found?
	if (ch)
	{
		// not found within bounds?
		if ((range > 0) && ((ch - str) > range))
		{
			return 0;
		}

		// determine if replacement will exceed max len
		if (strlen(str) + strlen(newstr) - strlen(oldstr) > max_len)
		{
			return -1;
		}

		// allocate temp string to hold extra stuff
		char *temp = (char *) vm_malloc(sizeof(char) * max_len);

		// ensure allocation was successful
		if (temp)
		{
			// save remainder of string
			strcpy(temp, ch + strlen(oldstr));

			// replace
			strcpy(ch, newstr);

			// append rest of string
			strcpy(ch + strlen(newstr), temp);
		}

		// free temp string
		vm_free(temp);
	}
	// not found
	else
	{
		return 0;
	}

	// return pos of replacement
	return (ch - str);
}

// Goober5000
int replace_all(char *str, char *oldstr, char *newstr, unsigned int max_len, int range)
{
	int val, tally(0);

	while ((val = replace_one(str, oldstr, newstr, max_len, range)) > 0)
	{
		tally++;

		// adjust range, because the text length might have changed
		range += strlen(newstr) - strlen(oldstr);
	}

	return (val < 0) ? val : tally;
}

//WMC
void backspace(char* src)
{
	Assert(src!= NULL);		//this would be bad

	char *dest = src;
	src++;

	while(*src != '\0') {
		*dest++ = *src++;
	}

	*dest = '\0';
}


// Goober5000 - ugh, I can't see why they didn't just use stuff_*_list for these;
// the only differece is the lack of parentheses

// from aicode.cpp
// Stuff a list of floats at *plist.
void parse_float_list(float *plist, int size)
{
	int i;

	for (i=0; i<size; i++)
	{
		stuff_float(&plist[i]);
	}
}

// from aicode.cpp
// Stuff a list of ints at *plist.
void parse_int_list(int *ilist, int size)
{
	int i;

	for (i=0; i<size; i++)
	{
		stuff_int(&ilist[i]);
	}
}

