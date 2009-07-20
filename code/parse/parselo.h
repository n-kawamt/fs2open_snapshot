/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

#ifndef _PARSELO_H
#define _PARSELO_H

#include "globalincs/globals.h"
#include "cfile/cfile.h"
#include "globalincs/pstypes.h"

#include <csetjmp>
#include <cstdio>
#include <string>

// NOTE: although the main game doesn't need this anymore, FRED2 still does
#define	MISSION_TEXT_SIZE	1000000

extern char	*Mission_text;
extern char	*Mission_text_raw;
extern char	*Mp;
extern char	*token_found;
extern int fred_parse_flag;
extern int Token_found_flag;
extern jmp_buf parse_abort;


#define	COMMENT_CHAR	(char)';'
#define	EOF_CHAR			(char)-128
#define	EOLN				(char)0x0a

#define	F_NAME					1
#define	F_DATE					2
#define	F_NOTES					3
#define	F_FILESPEC				4
#define	F_MULTITEXTOLD			5	// needed for backwards compatability with old briefing format
#define	F_SEXP					6
#define	F_PATHNAME				7
#define	F_SHIPCHOICE			8
#define	F_MESSAGE				9	// this is now obsolete for mission messages - all messages in missions should now use $MessageNew and stuff strings as F_MULTITEXT
#define	F_MULTITEXT				10
#define F_RAW					11	// for any internal parsing use. Just strips whitespace and copies the text.
#define F_LNAME					12	//Filenames

#define PARSE_BUF_SIZE			4096

//For modular TBL files -C
#define MAX_TBL_PARTS 32

// 1K on the stack? seems to work...
// JH: 1k isn't enough!  Command briefs can be 16k max, so changed this.
#define MAX_TMP_STRING_LENGTH 16384


#define	SHIP_TYPE			0	// used to identify which kind of array to do a search for a name in
#define	SHIP_INFO_TYPE		1
#define	WEAPON_LIST_TYPE	2	//	to parse an int_list of weapons
#define	RAW_INTEGER_TYPE	3	//	to parse a list of integers
#define	WEAPON_POOL_TYPE	4

// Karajorma - Used by the stuff_ship_list and stuff_weapon_list SEXPs
#define NOT_SET_BY_SEXP_VARIABLE	-1

#define MISSION_LOADOUT_SHIP_LIST		0
#define MISSION_LOADOUT_WEAPON_LIST		1
#define CAMPAIGN_LOADOUT_SHIP_LIST		2
#define CAMPAIGN_LOADOUT_WEAPON_LIST	3

#define SEXP_SAVE_MODE				1
#define SEXP_ERROR_CHECK_MODE		2

// Goober5000 - this seems to be a pretty universal function
extern bool end_string_at_first_hash_symbol(char *src);
extern char *get_pointer_to_first_hash_symbol(char *src);

// white space
extern int is_white_space(char ch);
extern void ignore_white_space();
extern void drop_trailing_white_space(char *str);
extern void drop_leading_white_space(char *str);
extern char *drop_white_space(char *str);

// gray space
void ignore_gray_space();

// error
extern int get_line_num();
extern char *next_tokens();
extern void diag_printf(char *format, ...);
extern void error_display(int error_level, char *format, ...);

// skip
extern int skip_to_string(char *pstr, char *end = NULL);
extern int skip_to_start_of_string(char *pstr, char *end = NULL);
extern int skip_to_start_of_string_either(char *pstr1, char *pstr2, char *end = NULL);
extern void advance_to_eoln(char *terminators);
extern void skip_token();

// required
extern int required_string(char *pstr);
extern int optional_string(char *pstr);
extern int optional_string_either(char *str1, char *str2);
extern int required_string_either(char *str1, char *str2);
extern int required_string_3(char *str1, char *str2, char *str3);
extern int required_string_4(char *str1, char *str2, char *str3, char *str4);

// stuff
extern void copy_to_eoln(char *outstr, char *more_terminators, char *instr, int max);
extern void copy_text_until(char *outstr, char *instr, char *endstr, int max_chars);
extern void stuff_string_white(char *pstr, int len = 0);
extern void stuff_string_until(char *pstr, char *endstr, int len = 0);
extern void stuff_string(char *pstr, int type, int len, char *terminators = NULL);
extern void stuff_string_line(char *pstr, int len);

//alloc
extern char* alloc_block(char* startstr, char* endstr, int extra_chars = 0);

// Exactly the same as stuff string only Malloc's the buffer. 
//	Supports various FreeSpace primitive types.  If 'len' is supplied, it will override
// the default string length if using the F_NAME case.
extern char *stuff_and_malloc_string( int type, char *terminators = NULL, int len = 0);
extern void stuff_malloc_string(char **dest, int type, char *terminators = NULL, int len = 0);
extern void stuff_float(float *f);
extern int stuff_float_optional(float *f);
extern void stuff_int(int *i);
extern void stuff_sound(int *dest);
extern void stuff_ubyte(ubyte *i);
extern int stuff_string_list(SCP_vector<std::string> *slp);
extern int stuff_string_list(char slp[][NAME_LENGTH], int max_strings);
extern int parse_string_flag_list(int *dest, flag_def_list defs[], int defs_size);
extern int stuff_int_list(int *ilp, int max_ints, int lookup_type = RAW_INTEGER_TYPE);
extern int stuff_float_list(float* flp, int max_floats);
extern int stuff_vector_list(vec3d *vlp, int max_vecs);
extern int stuff_bool_list(bool *blp, int max_bools);
extern void stuff_vector(vec3d *vp);
extern void stuff_matrix(matrix *mp);
extern int string_lookup(char *str1, char *strlist[], int max, char *description = NULL, int say_errors = 0);
extern void find_and_stuff(char *id, int *addr, int f_type, char *strlist[], int max, char *description);
extern void find_and_stuff_optional(char *id, int *addr, int f_type, char *strlist[], int max, char *description);
extern int match_and_stuff(int f_type, char *strlist[], int max, char *description);
extern void find_and_stuff_or_add(char *id, int *addr, int f_type, char *strlist[], int *total,
	int max, char *description);
extern int get_string(char *str);
extern void stuff_parenthesized_vector(vec3d *vp);
extern void stuff_boolean(int *i, bool a_to_eol=true);
extern void stuff_boolean(bool *b, bool a_to_eol=true);
extern void stuff_boolean_flag(int *i, int flag, bool a_to_eol=true);
extern int check_for_string(char *pstr);
extern int check_for_string_raw(char *pstr);
extern int check_for_eof();

// from aicode.cpp
extern void parse_float_list(float *plist, int size);
extern void parse_int_list(int *ilist, int size);


// general
extern void reset_parse(char *text = NULL);
extern void display_parse_diagnostics();
extern void pause_parse();
extern void unpause_parse();
// stop parsing, basically just free's up the memory from Mission_text and Mission_text_raw
extern void stop_parse();

// utility
extern void mark_int_list(int *ilp, int max_ints, int lookup_type);
extern void compact_multitext_string(char *str);
extern void read_file_text(char *filename, int mode = CF_TYPE_ANY, char *processed_text = NULL, char *raw_text = NULL);
extern void read_file_text_from_array(char *array, char *processed_text = NULL, char *raw_text = NULL);
extern void read_raw_file_text(char *filename, int mode = CF_TYPE_ANY, char *raw_text = NULL);
extern void process_raw_file_text(char *processed_text = NULL, char *raw_text = NULL);
extern void debug_show_mission_text();
extern void convert_sexp_to_string(int cur_node, char *outstr, int mode, int max_len);
char *split_str_once(char *src, int max_pixel_w);
int split_str(char *src, int max_pixel_w, int *n_chars, char **p_str, int max_lines, char ignore_char = -1);
int split_str(char *src, int max_pixel_w, SCP_vector<int> *n_chars, SCP_vector<char*> *p_str, char ignore_char);

// fred
extern int required_string_fred(char *pstr, char *end = NULL);
extern int required_string_either_fred(char *str1, char *str2);
extern int optional_string_fred(char *pstr, char *end = NULL, char *end2 = NULL);

extern char	parse_error_text[128];

// Goober5000 - returns position of replacement or -1 for exceeded length
extern int replace_one(char *str, char *oldstr, char *newstr, unsigned int max_len, int range = 0);

// Goober5000 - returns number of replacements or -1 for exceeded length
extern int replace_all(char *str, char *oldstr, char *newstr, unsigned int max_len, int range = 0);

// Goober5000 (why is this not in the C library?)
extern char *stristr(const char *str, const char *substr);

// Goober5000
extern int subsystem_stricmp(const char *str1, const char *str2);

//WMC - compares two strings, ignoring the last extension
extern int strextcmp(const char *s1, const char *s2);

//WMC - backspaces the first character of given char pointer
extern void backspace(char *src);

// Goober5000 - prints a properly comma-separated integer to a string
extern void format_integer_with_commas(char *buf, int integer, bool use_comma_with_four_digits);

inline void parse_advance(int s){Mp+=s;}

// parse a modular table, returns the number of files matching the "name_check" filter or 0 if it did nothing
extern int parse_modular_table(char *name_check, void (*parse_callback)(char *filename), int path_type = CF_TYPE_TABLES, int sort_type = CF_SORT_REVERSE);
// to know that we are parsing a modular table
extern bool Parsing_modular_table;

//Karajorma - Parses mission and campaign ship loadouts. 
int stuff_loadout_list (int *ilp, int max_ints, int lookup_type);
int get_string_or_variable (char *str);
#define PARSING_FOUND_STRING		0
#define PARSING_FOUND_VARIABLE		1


#endif
