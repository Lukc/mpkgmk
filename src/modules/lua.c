#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <mpkgmk_private.h>

/* THE PLAN:
 *	- Use a modules.lua or init.lua or main.lua or something.lua to create
 *	  some kind of API for Lua modules, and have that read before everything
 *	  else.
 *	- If that file couldn’t be loaded, do nothing. Just close the lua_State
 *	  and ignore everything.
 *	- For each ModuleFooFunction, call every single Lua module, just like we’re
 *	  presently doing in C.
 *	- The Configuration, Source and Recipe structures will have to be
 *	  converted into Lua tables for the sake of… making it work?
 */

/* Our Lua state, made global to be kept between on_load and on_exit(). */
lua_State *l;

/*
 * Code taken from Lua’s interpreter
 */

static int traceback (lua_State *L) {
	const char *msg = lua_tostring(L, 1);
	if (msg)
		luaL_traceback(L, L, msg, 1);
	else if (!lua_isnoneornil(L, 1)) {  /* is there an error object? */
		if (!luaL_callmeta(L, 1, "__tostring"))  /* try its 'tostring' metamethod */
			lua_pushliteral(L, "(no error message)");
	}
	return 1;
}


static int docall (lua_State *L, int narg, int nres) {
	int status;
	int base = lua_gettop(L) - narg;  /* function index */
	lua_pushcfunction(L, traceback);  /* push traceback function */
	lua_insert(L, base);  /* put it under chunk and args */
	//globalL = L;  /* to be available to 'laction' */
	//signal(SIGINT, laction);
	status = lua_pcall(L, narg, nres, base);
	//signal(SIGINT, SIG_DFL);
	lua_remove(L, base);  /* remove traceback function */
	return status;
}

static int dofile (lua_State *L, const char *name) {
	int status = luaL_loadfile(L, name);
	if (status == LUA_OK) status = docall(L, 0, 0);
	return status;
}

/*
 * End of Lua’s interpreter code
 */

static void
open_lualibs(lua_State *l, struct luaL_Reg lualibs[])
{
	const luaL_Reg *lib;

	lib = lualibs;
	while (lib->func) {
		lib->func(l);
		lua_settop(l, 0);

		lib++;
	}
}

void
mpkgmk_on_load(Configuration *configuration) {
	int r;
	static struct luaL_Reg lualibs[] =
	{
		{ "base",       luaopen_base },
		{ NULL,         NULL }
	};
	char *filename = SHAREDIR "/on_load.lua";

	l = luaL_newstate();
	open_lualibs(l, lualibs);

	r = dofile(l, filename);
	if (r != LUA_OK) {
		warning("[modules/lua] %s could not be executed. Lua modules are disabled.", filename);
		lua_close(l);

		return;
	}

	struct dirent *entry;
	DIR *directory;
	directory = opendir(SHAREDIR "/lua");
	if (!directory) {
		error("[modules/lua] Could not open directory %s.", SHAREDIR "/lua");

		lua_close(l);
		return;
	}

	while ( (entry = readdir(directory)) ) {
		filename = strdup(SHAREDIR "/lua");
		filename = (char*) realloc(filename,
			strlen(SHAREDIR "/lua") + strlen(entry->d_name) + 2
		);
		strcat(filename, "/");
		strcat(filename, entry->d_name);

		if (strcmp(filename, ".") && strcmp(filename, "..")) {
			/* FIXME: check it ends by .lua and does not begin
			 *        with “.”. (at least) */
			dofile(l, filename);
		}

		free(filename);
	}
}

void
mpkgmk_on_close(Configuration *configuration, int status) {
	/* Status is ignored. */
	if (l)
		lua_close(l);
}

