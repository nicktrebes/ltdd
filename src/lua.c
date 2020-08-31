/*
MIT License

lua.c
Copyright (c) 2020 Nick Trebes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ltdd.h>

static void *ltdd_alloc(void *ud, void *ptr, size_t oz, size_t nz);

static int ltdd_assert_that(lua_State *L);
static int ltdd_constraint_name(lua_State *L);
static int ltdd_is_equal_to(lua_State *L);
static int ltdd_is_not_equal_to(lua_State *L);
static int ltdd_is_greater_than(lua_State* L);
static int ltdd_is_less_than(lua_State* L);
static int ltdd_is_nil(lua_State *L);
static int ltdd_is_not_nil(lua_State *L);
static int ltdd_is_false(lua_State *L);
static int ltdd_is_true(lua_State *L);

static const struct luaL_Reg lib_ltdd[] = {
	{"assert_that", ltdd_assert_that},
	{"constraint_name", ltdd_constraint_name},
	{"is_equal_to", ltdd_is_equal_to},
	{"is_not_equal_to", ltdd_is_not_equal_to},
	{"is_greater_than", ltdd_is_greater_than},
	{"is_less_than", ltdd_is_less_than},
	{"is_nil", ltdd_is_nil},
	{"is_not_nil", ltdd_is_not_nil},
	{"is_false", ltdd_is_false},
	{"is_true", ltdd_is_true},
	{NULL, NULL}
};

lua_State *ltdd_lua_open_libs(void) {
	lua_State *L = lua_newstate(ltdd_alloc, NULL);
	luaL_openlibs(L);
	ltdd_lua_open_ltdd(L);
	return L;
}

void ltdd_lua_open_ltdd(lua_State *L) {
	luaL_newlibtable(L, lib_ltdd);
	luaL_setfuncs(L, lib_ltdd, 0);
	lua_setglobal(L, "ltdd");
}

static void *ltdd_alloc(void *ud, void *ptr, size_t oz, size_t nz) {
	(void)ud;
	(void)oz;

	return realloc(ptr, nz);
}

static int ltdd_assert_that(lua_State *L) {
	int none3 = lua_isnone(L, 3);
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 1);
	if (none3) {
		lua_pushnil(L);
	} else {
		lua_pushvalue(L, 3);
	}
	lua_pcall(L, 2, 1, 0);
	if (!lua_toboolean(L, -1)) {
		lua_pushliteral(L, "assertion failed: [");

		lua_pushvalue(L, 1);
		lua_tostring(L, -1);

		lua_pushliteral(L, "] [");

		lua_getglobal(L, "ltdd");
		lua_getfield(L, -1, "constraint_name");
		lua_remove(L, -2);
		lua_pushvalue(L, 2);
		lua_pcall(L, 1, 1, 0);

		lua_pushliteral(L, "]");

		if (none3) {
			lua_concat(L, 5);
		} else {
			lua_pushliteral(L, " [");

			lua_pushvalue(L, 3);
			lua_tostring(L, -1);

			lua_pushliteral(L, "]");
			lua_concat(L, 8);
		}

		return lua_error(L);
	}
	return 0;
}

static int ltdd_constraint_name(lua_State *L) {
	lua_CFunction fn = lua_tocfunction(L, 1);
	const char *name = NULL;
	if (fn == ltdd_is_equal_to) {
		name = "is_equal_to";
	} else if (fn == ltdd_is_not_equal_to) {
		name = "is_not_equal_to";
	} else if (fn == ltdd_is_nil) {
		name = "is_nil";
	} else if (fn == ltdd_is_not_nil) {
		name = "is_not_nil";
	} else if (fn == ltdd_is_greater_than) {
		name = "is_greater_than";
	} else if (fn == ltdd_is_less_than) {
		name = "is_less_than";
	} else if (fn == ltdd_is_false) {
		name = "is_false";
	} else if (fn == ltdd_is_true) {
		name = "is_true";
	} else {
		return 0;
	}
	lua_pushstring(L, name);
	return 1;
}

static int ltdd_is_equal_to(lua_State *L) {
	lua_pushboolean(L, lua_compare(L, 1, 2, LUA_OPEQ));
	return 1;
}

static int ltdd_is_not_equal_to(lua_State *L) {
	lua_pushboolean(L, !lua_compare(L, 1, 2, LUA_OPEQ));
	return 1;
}

static int ltdd_is_greater_than(lua_State* L) {
	return 0;
}

static int ltdd_is_less_than(lua_State* L) {
	return 0;
}

static int ltdd_is_nil(lua_State *L) {
	lua_pushboolean(L, lua_isnoneornil(L, 1));
	return 1;
}

static int ltdd_is_not_nil(lua_State *L) {
	lua_pushboolean(L, !lua_isnoneornil(L, 1));
	return 1;
}

static int ltdd_is_false(lua_State *L) {
	lua_pushboolean(L, !lua_toboolean(L, 1));
	return 1;
}

static int ltdd_is_true(lua_State *L) {
	lua_pushboolean(L, lua_toboolean(L, 1));
	return 1;
}
