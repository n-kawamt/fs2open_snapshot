#include <stdio.h>
#include <stdarg.h>
#include "parse/scripting.h"
#include "parse/lua.h"
#include "parse/parselo.h"
#include "globalincs/version.h"
#include "gamesequence/gamesequence.h"
#include "bmpman/bmpman.h"
#include "globalincs/systemvars.h"
#include "hud/hud.h"

//tehe. Declare the main event
script_state Script_system("FS2_Open Scripting");
bool Output_scripting_meta = false;

//*************************Scripting hook globals*************************
script_hook Script_splashhook;
script_hook Script_simulationhook;
script_hook Script_hudhook;
script_hook Script_globalhook;
script_hook Script_gameinithook;

//*************************Scripting init and handling*************************

int script_test(script_state *st)
{
	int rval;
	if ((rval = setjmp(parse_abort)) != 0)
	{
		mprintf(("Unable to parse scripting.tbl!  Code = %i.\n", rval));
		return 0;
	}
	else
	{	
		read_file_text("scripting.tbl");
		reset_parse();
	}

	if(optional_string("#Global Hooks"))
	{
		if(optional_string("$Global:")) {
			Script_globalhook = st->ParseChunk("Global");
		}

		if(optional_string("$Splash:")) {
			Script_splashhook = st->ParseChunk("Splash");
		}

		if(optional_string("$GameInit:")) {
			Script_gameinithook = st->ParseChunk("GameInit");
		}

		if(optional_string("$Simulation:")) {
			Script_simulationhook = st->ParseChunk("Simulation");
		}

		if(optional_string("$HUD:")) {
			Script_hudhook = st->ParseChunk("HUD");
		}

		required_string("#End");
	}

	if(optional_string("#State Hooks"))
	{
		while(optional_string("$State:")) {
			char buf[NAME_LENGTH];
			int idx;
			stuff_string(buf, F_NAME);

			idx = gameseq_get_state_idx(buf);

			if(optional_string("$Hook:"))
			{
				if(idx > -1) {
					GS_state_hooks[idx] = st->ParseChunk(buf);
				} else {
					st->ParseChunk(buf);
				}
			}
		}
		required_string("#End");
	}

	return 1;
}

//Initializes the (global) scripting system, as well as any subsystems.
//script_close is handled by destructors
void script_init (void)
{
	mprintf(("SCRIPTING: Beginning initialization sequence...\n"));

	mprintf(("SCRIPTING: Beginning Lua initialization...\n"));
	Script_system.CreateLuaState();

	if(Output_scripting_meta)
	{
		mprintf(("SCRIPTING: Outputting scripting metadata...\n"));
		Script_system.OutputMeta("scripting.html");
	}
	mprintf(("SCRIPTING: Beginning main hook parse sequence....\n"));
	script_test(&Script_system);
	mprintf(("SCRIPTING: Inititialization complete.\n"));
}

//*************************CLASS: script_state*************************
//Most of the icky stuff is here. Lots of #ifdefs
#ifndef USE_PYTHON
#pragma message("NOTE: Python is not compiled in")
#endif

void script_state::SetGlobal(char *name, char format, void *data)
{
	Assert(data != NULL);
	if(LuaState != NULL)
	{
		char fmt[2] = {format, '\0'};

		//ERRORS? LOOK HERE!!!
		//--------------------
		//WMC - Now THIS has to be the nastiest hack I've made
		//Basically, I tell it to copy over enough stack
		//for a script_lua_odata object. If you pass
		//_anything_ larger as a stack object, this will not work.
		//You'll get memory corruption
		lua_set_args(LuaState, fmt, *(script_lua_odata*)data);
		//--------------------
		//WMC - This was a separate function
		//lua_set_arg(LuaState, format, data);
		lua_setglobal(LuaState, name);
	}
}

//WMC - data can be NULL, if we just want to know if it exists
bool script_state::GetGlobal(char *name, char format, void *data)
{
	bool got_global = false;
	if(LuaState != NULL)
	{
		//Construct format string
		char fmt[3] = {'|', format, '\0'};

		lua_getglobal(LuaState, name);
		//Does global exist?
		if(!lua_isnil(LuaState, -1))
		{
			if(data != NULL) {
				lua_get_args(LuaState, fmt, data);
			}
			got_global = true;
		}
	}

	return got_global;
}

void script_state::RemGlobal(char *name)
{
	if(LuaState != NULL)
	{
		//WMC - Quick and clean. :)
		lua_pushnil(LuaState);
		lua_setglobal(LuaState, name);
	}
}

int script_state::LoadBm(char *name)
{
	for(int i = 0; i < (int)ScriptImages.size(); i++)
	{
		if(!stricmp(name, ScriptImages[i].fname))
			return ScriptImages[i].handle;
	}

	image_desc id;
	int idx = bm_load(name);

	if(idx > -1) {
		id.handle = idx;
		strcpy(id.fname, name);
		ScriptImages.push_back(id);
	}

	return idx;
}

void script_state::UnloadImages()
{
	for(int i = 0; i < (int)ScriptImages.size(); i++)
	{
		bm_unload(ScriptImages[i].handle);
	}

	ScriptImages.clear();
}

//returns 0 on failure (Parse error), 1 on success
int script_state::RunBytecode(script_hook &hd, char format, void *data)
{
	if(hd.index >= 0)
	{
		// if this is the hook for the hud, and the hud is disabled or we are in freelook mode, then don't run the script
		// (admittedly this is wrong, but I'm not sure where else to put this check and have it work properly. hopefully
		//  WMCoolmon can get some time to come back over this and fix the issues, or just make it better period. - taylor)
		if (hd.index == Script_hudhook.index) {
			if ( (Viewer_mode & VM_FREECAMERA) || hud_disabled() ) {
				return 1;
			}
		}

		if(hd.language == SC_LUA)
		{
			int args_start=0;
			if(data != NULL) {
				args_start = lua_gettop(LuaState);
			}
			lua_pushcfunction(GetLuaSession(), lua_friendly_error);
			lua_getref(GetLuaSession(), hd.index);
			if(lua_pcall(GetLuaSession(), 0, format!='\0' ? 1 : 0, -2) != 0)
			{
				return 0;
			}

			//WMC - Just allow one argument for now.
			if(data != NULL)
			{
				char fmt[2] = {format, '\0'};
				Lua_get_args_skip = args_start;
				lua_get_args(LuaState, fmt, data);
				Lua_get_args_skip = 0;
			}

			//WMC - Pop anything leftover from the function from the stack
			args_start = lua_gettop(LuaState) - args_start;
			for(; args_start > 0; args_start--) lua_pop(LuaState, 1);
		}
		else if(hd.language == SC_PYTHON)
		{
#ifdef USE_PYTHON
			PyObject *chk = PyBytecodeLib.Get(hd.index);
			if(chk != NULL)
			{
				PyEval_EvalCode(PyBytecodeLib.Get(hd.index), GetPyGlobals(), GetPyLocals());
				return 1;
			}
#endif
		}
	}

	return 1;
}

void script_state::Clear()
{
	StateName[0] = '\0';
	Langs = 0;

	//Don't close this yet
	LuaState = NULL;
	LuaLibs = NULL;
#ifdef USE_PYTHON
	Py_XDECREF(PyGlb);
	PyGlb = NULL;
	Py_XDECREF(PyLoc);
	PyLoc = NULL;
#endif
}

script_state::script_state(char *name)
{
	strncpy(StateName, name, sizeof(StateName)-1);

	Langs = 0;

	LuaState = NULL;
	LuaLibs = NULL;

	PyGlb = NULL;
	PyLoc = NULL;
}

script_state& script_state::operator=(script_state &in)
{
	Error(LOCATION, "SESSION COPY ATTEMPTED");

	return *this;
}

script_state::~script_state()
{
	if(LuaState != NULL) {
		lua_close(LuaState);
	}

	Clear();
}

void script_state::SetLuaSession(lua_State *L)
{
	if(LuaState != NULL)
	{
		lua_close(LuaState);
	}
	LuaState = L;
	if(LuaState != NULL) {
		Langs |= SC_LUA;
	}
	else if(Langs & SC_LUA) {
		Langs &= ~SC_LUA;
	}
}

void script_state::SetPySession(PyObject *loc, PyObject *glb)
{
#ifdef USE_PYTHON
	//set variables
	if(PyGlb != NULL)
	{
		Py_XDECREF(PyGlb);
		PyGlb = glb;
	}

	if(PyLoc != NULL)
	{
		Py_XDECREF(PyLoc);
		PyLoc = loc;
	}

	//Add or remove python note
	if(PyGlb != NULL || PyLoc != NULL)
	{
		Langs |= SC_PYTHON;
	}
	else if(Langs & SC_PYTHON)
	{
		Langs &= ~SC_PYTHON;
	}
#endif
}

int script_state::OutputMeta(char *filename)
{
	FILE *fp = fopen(filename,"w");

	if(fp == NULL)
	{
		return 0; 
	}

	fprintf(fp, "<html>\n<head>\n\t<title>Script output: %d.%d.%d (%s)</title>\n</head>\n", FS_VERSION_MAJOR, FS_VERSION_MINOR, FS_VERSION_BUILD, StateName);
	fputs("<body>", fp);
	fprintf(fp,"\t<h1>Script Output - Build %d.%d.%d (%s)</h1>\n", FS_VERSION_MAJOR, FS_VERSION_MINOR, FS_VERSION_BUILD, StateName);
	
	//Scripting languages links
	fputs("<dl>", fp);
	fputs("<dt><b>Scripting languages</b></dt>", fp);
	if(Langs & SC_PYTHON) {
		fputs("<dd><a href=\"#Python\">Python</a></dd>", fp);
	}
	if(Langs & SC_LUA) {
		fputs("<dd><a href=\"#Lua\">Lua</a></dd>", fp);
	}
	fputs("</dl>", fp);

	//Languages
	fputs("<dl>", fp);
	if(Langs & SC_LUA) {
		fputs("<dt><H2><a name=\"#Lua\">Lua</a></H2></dt>", fp);

		fputs("<dd>", fp);
		OutputLuaMeta(fp);
		fputs("</dd>", fp);
	}
	/*
	if(Langs & SC_PYTHON) {
		OutputPyMeta(fp);
	}*/
	fputs("</dl></body></html>", fp);

	fclose(fp);

	return 1;
}

bool script_state::EvalString(char* string, char *format, void *rtn, char *debug_str)
{
	char *lcp = &string[strlen(string)-1];
	char lastchar = *lcp;

	if(string[0] == '{')
	{
#ifdef USE_PYTHON
		if(lastchar == '}')
		{
			*lcp = '\0';
		}
		else
		{
			return false;
		}

		//WMC - Whoever comes next to Python...needs to fix this.
		Py_RunString(string, Py_file_input, PyGlb, PyLoc);

		*lcp = lastchar;
		return true;
#else
		return false;
#endif
	}

	char *s = string;
	if(string[0] != '[' && rtn != NULL)
	{
		s = new char[strlen(string) + 8];
		strcpy(s, "return ");
		strcpy(s, string);
	}
	else if(string[0] == ']' && lastchar != ']')
	{
		return false;
	}
	else if(string[0] == ']')
	{
		s++;
		*lcp = '\0';
	}

	//WMC - So we can pop extra return values
	int args_start = lua_gettop(LuaState);

	//WMC - Push error handling function
	lua_pushcfunction(LuaState, lua_friendly_error);
	//Parse string
	luaL_loadbuffer(LuaState, s, strlen(s), debug_str);
	//Call function
	if(lua_pcall(LuaState, 0, LUA_MULTRET, -2))
	{
		return false;
	}

	//Only get args if we can put them someplace
	if(rtn != NULL)
	{
		lua_get_args(LuaState, format, *(script_lua_odata*)rtn);
	}

	//WMC - Pop anything leftover from the function from the stack
	args_start = lua_gettop(LuaState) - args_start;
	for(; args_start > 0; args_start--) lua_pop(LuaState, 1);

	if(lastchar == ']')
		*lcp = lastchar;

	return true;
}

script_hook script_state::ParseChunk(char* debug_str)
{
	static int total_parse_calls = 0;
	char buf[PARSE_BUF_SIZE] = {0};
	char debug_buf[128];
	script_hook rval;

	total_parse_calls++;

	//DANGER! This code means the debug_str must be used only before parsing
	if(!debug_str)
	{
		debug_str = debug_buf;
		sprintf(debug_str, "script_parse() count %d", total_parse_calls);
	}

	if(check_for_string("[["))
	{
		//Lua from file

		//Lua
		rval.language = SC_LUA;

		char *filename = alloc_block("[[", "]]");

		//Load from file
		CFILE *cfp = cfopen(filename, "rb", CFILE_NORMAL, CF_TYPE_SCRIPTS );
		if(cfp == NULL)
		{
			Warning(LOCATION, "Could not load lua script file '%s'", filename);
		}
		else
		{
			int len = cfilelength(cfp);

			char *raw_lua = (char*)vm_malloc(len+1);
			raw_lua[len] = '\0';

			cfread(raw_lua, len, 1, cfp);
			cfclose(cfp);

			luaL_loadbuffer(GetLuaSession(), raw_lua, len, debug_str);
			//luaL_loadfile(GetLuaSession(), filename);

			rval.index = luaL_ref(GetLuaSession(), LUA_REGISTRYINDEX);
			vm_free(raw_lua);
		}
		//dealloc
		//WMC - For some reason these cause crashes
		//vm_free(filename);
	}
	else if(check_for_string("["))
	{
		//Lua string

		//Assume Lua
		rval.language = SC_LUA;

		//Allocate raw script
		char* raw_lua = alloc_block("[", "]");

		//Load it into a buffer & parse it
		luaL_loadbuffer(GetLuaSession(), raw_lua, strlen(raw_lua), debug_str);

		//Stick it in the registry
		rval.index = luaL_ref(GetLuaSession(), LUA_REGISTRYINDEX);

		//free the mem
		//vm_free(raw_lua);
	}
	else if(check_for_string("{"))
	{
		//Python string

		//Assume python
		rval.language = SC_PYTHON;

		//Get the block
		char* raw_python = alloc_block("{","}");
#ifdef USE_PYTHON
		//Add it to the lib
		rval.index = PyBytecodeLib.Add(PyBytecode(Py_CompileString(raw_python, debug_str, Py_file_input)));
#endif
		vm_free(raw_python);
	}
	else
	{
		//Assume lua
		rval.language = SC_LUA;

		strcpy(buf, "return ");

		//Stuff it
		stuff_string(buf+strlen(buf), F_RAW, NULL, sizeof(buf)-1);

		//Load it into a buffer & parse it
		luaL_loadbuffer(GetLuaSession(), buf, strlen(buf), debug_str);

		//Stick it in the registry
		rval.index = luaL_ref(GetLuaSession(), LUA_REGISTRYINDEX);
	}

	if(optional_string("+Override:"))
		stuff_boolean(&rval.total_override);

	return rval;
}
