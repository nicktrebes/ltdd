#include "test.h"

static lua_State *L = NULL;

Describe(lua_api);

BeforeEach(lua_api) {
	L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd"); // t
}

AfterEach(lua_api) {
	lua_close(L);
}

Ensure(lua_api, assert_that_throws_error_on_failed_constraint) {
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 2); // t f i f i
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_pcall(L, 2, 0, 0), is_not_equal_to(LUA_OK));
}

Ensure(lua_api, assert_that_throws_formatted_error_string_1arg) {
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_nil"); // t f i f
	lua_pcall(L, 2, 0, 0);
	assert_that(lua_tostring(L, -1), is_equal_to_string("assertion failed: [1] [is_nil]"));
}

Ensure(lua_api, assert_that_throws_formatted_error_string_2arg) {
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 2); // t f i f i
	lua_pcall(L, 1, 1, 0);
	lua_pcall(L, 2, 0, 0);
	assert_that(lua_tostring(L, -1), is_equal_to_string("assertion failed: [1] [is_equal_to] [2]"));
}

Ensure(lua_api, assert_that_passes_on_fulfilled_constraint) {
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 1); // t f i f i
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_pcall(L, 2, 0, 0), is_equal_to(LUA_OK));
}

Ensure(lua_api, create_context_returns_context_object) {
	lua_getfield(L, -1, "create_context"); // t f
	lua_pcall(L, 0, 1, 0); // t t
	assert_that(luaL_getmetafield(L, -1, "__index"), is_not_equal_to(LUA_TNIL)); // t t t
	assert_that(lua_compare(L, -1, -3, LUA_OPEQ), is_not_equal_to(0));
	lua_pop(L, 1); // t t
	luaL_getmetafield(L, -1, "__tostring"); // t t f
	lua_pushvalue(L, -2); // t t f t
	assert_that(lua_pcall(L, 1, 1, 0), is_equal_to(LUA_OK)); // t t s
	const char *tostring_value = lua_tostring(L, -1);
	assert_that(tostring_value, is_equal_to_string("[C]"));
}

TestSuite *test_lua_api(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, lua_api, assert_that_throws_error_on_failed_constraint);
	add_test_with_context(suite, lua_api, assert_that_throws_formatted_error_string_1arg);
	add_test_with_context(suite, lua_api, assert_that_throws_formatted_error_string_2arg);
	add_test_with_context(suite, lua_api, assert_that_passes_on_fulfilled_constraint);
	add_test_with_context(suite, lua_api, create_context_returns_context_object);

	return suite;
}
