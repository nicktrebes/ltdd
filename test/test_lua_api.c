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

TestSuite *test_lua_api(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, lua_api, assert_that_throws_error_on_failed_constraint);
	add_test_with_context(suite, lua_api, assert_that_throws_formatted_error_string_1arg);
	add_test_with_context(suite, lua_api, assert_that_throws_formatted_error_string_2arg);
	add_test_with_context(suite, lua_api, assert_that_passes_on_fulfilled_constraint);

	return suite;
}
