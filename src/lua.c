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
static int ltdd_constraint_tostring(lua_State *L);
static int ltdd_eval_is_equal_to(lua_State *L);
static int ltdd_eval_is_not_equal_to(lua_State *L);
static int ltdd_eval_is_greater_than(lua_State* L);
static int ltdd_eval_is_less_than(lua_State* L);
static int ltdd_eval_is_nil(lua_State *L);
static int ltdd_eval_is_not_nil(lua_State *L);
static int ltdd_eval_is_false(lua_State *L);
static int ltdd_eval_is_true(lua_State *L);
static int ltdd_is_equal_to(lua_State *L);
static int ltdd_is_not_equal_to(lua_State *L);
static int ltdd_is_greater_than(lua_State* L);
static int ltdd_is_less_than(lua_State* L);
static int ltdd_is_nil(lua_State *L);
static int ltdd_is_not_nil(lua_State *L);
static int ltdd_is_false(lua_State *L);
static int ltdd_is_true(lua_State *L);
static void ltdd_push_constraint(lua_State *L, lua_CFunction eval, const char *name);
static void ltdd_replace_tostring(lua_State *L);

static const struct luaL_Reg lib_ltdd[] = {
	{"assert_that", ltdd_assert_that},
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
	lua_pushvalue(L, 2); // f
	lua_pcall(L, 0, 1, 0); // C
	lua_pushvalue(L, -1); // C C
	lua_pushvalue(L, 1); // C C A
	if (none3) {
		lua_pushnil(L); // C C A n
	} else {
		lua_pushvalue(L, 3); // C C A B
	}
	lua_pcall(L, 2, 1, 0); // C b
	if (!lua_toboolean(L, -1)) {
		lua_pushliteral(L, "assertion failed: ["); // C b s
		lua_pushvalue(L, 1); // C b s A
		ltdd_replace_tostring(L); // C b s s
		lua_pushliteral(L, "] ["); // C b s s s
		lua_pushvalue(L, -5); // C b s s s C
		ltdd_replace_tostring(L); // C b s s s s
		if (none3) {
			lua_pushliteral(L, "]"); // C b s s s s s
			lua_concat(L, 5); // C b s
		} else {
			lua_pushliteral(L, "] ["); // C b s s s s s
			lua_pushvalue(L, 3); // C b s s s s s B
			ltdd_replace_tostring(L); // C b s s s s s s
			lua_pushliteral(L, "]"); // C b s s s s s s s
			lua_concat(L, 7); // C b s
		}
		return lua_error(L);
	}
	return 0;
}

static int ltdd_constraint_tostring(lua_State *L) {
	lua_getmetatable(L, 1); // t
	lua_getfield(L, -1, "constraint"); // t s
	return 1;
}

static int ltdd_eval_is_equal_to(lua_State *L) {
	lua_pushboolean(L, lua_compare(L, 2, 3, LUA_OPEQ));
	return 1;
}

static int ltdd_eval_is_not_equal_to(lua_State *L) {
	lua_pushboolean(L, !lua_compare(L, 2, 3, LUA_OPEQ));
	return 1;
}

static int ltdd_eval_is_greater_than(lua_State* L) {
	lua_pushboolean(L, !lua_compare(L, 2, 3, LUA_OPLE));
	return 1;
}

static int ltdd_eval_is_less_than(lua_State* L) {
	lua_pushboolean(L, lua_compare(L, 2, 3, LUA_OPLT));
	return 1;
}

static int ltdd_eval_is_nil(lua_State *L) {
	lua_pushboolean(L, lua_isnoneornil(L, 2));
	return 1;
}

static int ltdd_eval_is_not_nil(lua_State *L) {
	lua_pushboolean(L, !lua_isnoneornil(L, 2));
	return 1;
}

static int ltdd_eval_is_false(lua_State *L) {
	lua_pushboolean(L, !lua_toboolean(L, 2));
	return 1;
}

static int ltdd_eval_is_true(lua_State *L) {
	lua_pushboolean(L, lua_toboolean(L, 2));
	return 1;
}

static int ltdd_is_equal_to(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_equal_to, "is_equal_to");
	return 1;
}

static int ltdd_is_not_equal_to(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_not_equal_to, "is_not_equal_to");
	return 1;
}

static int ltdd_is_greater_than(lua_State* L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_greater_than, "is_greater_than");
	return 1;
}

static int ltdd_is_less_than(lua_State* L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_less_than, "is_less_than");
	return 1;
}

static int ltdd_is_nil(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_nil, "is_nil");
	return 1;
}

static int ltdd_is_not_nil(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_not_nil, "is_not_nil");
	return 1;
}

static int ltdd_is_false(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_false, "is_false");
	return 1;
}

static int ltdd_is_true(lua_State *L) {
	ltdd_push_constraint(L,
		ltdd_eval_is_true, "is_true");
	return 1;
}

static void ltdd_push_constraint(lua_State *L, lua_CFunction eval, const char *name) {
	lua_newtable(L); // t
	lua_newtable(L); // t t
	lua_pushliteral(L, "__call"); // t t s
	lua_pushcfunction(L, eval); // t t s f
	lua_settable(L, -3); // t t
	lua_pushliteral(L, "__tostring"); // t t s
	lua_pushcfunction(L, ltdd_constraint_tostring); // t t s f
	lua_settable(L, -3); // t t
	lua_pushliteral(L, "constraint"); // t t s
	lua_pushstring(L, name); // t t s s
	lua_settable(L, -3); // t t
	lua_setmetatable(L, -2); // t
}

static void ltdd_replace_tostring(lua_State *L) {
	// V
	if (luaL_getmetafield(L, -1, "__tostring") == LUA_TFUNCTION) { // V f
		lua_pushvalue(L, -2); // V f V
		lua_pcall(L, 1, 1, 0); // V s
		lua_remove(L, -2); // s
	} else {
		int old = lua_gettop(L);
		lua_tostring(L, -1);
		if (old != lua_gettop(L)) {
			lua_remove(L, -2);
		}
	}
}
