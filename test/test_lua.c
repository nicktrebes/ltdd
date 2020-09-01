#include "test.h"

Describe(Lua);
BeforeEach(Lua) {}
AfterEach(Lua) {}

static void test_function_created(const char *name);

Ensure(Lua, open_libs_provides_valid_state) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "_VERSION");
	assert_that(lua_tostring(L, -1), is_equal_to_string(LUA_VERSION));
	lua_close(L);
}

Ensure(Lua, open_libs_creates_ltdd_table) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	assert_that(lua_type(L, -1), is_equal_to(LUA_TTABLE));
	lua_close(L);
}

Ensure(Lua, open_libs_creates_ltdd_assert_that) {
	test_function_created("assert_that");
}

Ensure(Lua, open_libs_creates_ltdd_is_equal_to) {
	test_function_created("is_equal_to");
}

Ensure(Lua, open_libs_creates_ltdd_is_not_equal_to) {
	test_function_created("is_not_equal_to");
}

Ensure(Lua, open_libs_creates_ltdd_is_greater_than) {
	test_function_created("is_greater_than");
}

Ensure(Lua, open_libs_creates_ltdd_is_less_than) {
	test_function_created("is_less_than");
}

Ensure(Lua, open_libs_creates_ltdd_is_nil) {
	test_function_created("is_nil");
}

Ensure(Lua, open_libs_creates_ltdd_is_not_nil) {
	test_function_created("is_not_nil");
}

Ensure(Lua, open_libs_creates_ltdd_is_false) {
	test_function_created("is_false");
}

Ensure(Lua, open_libs_creates_ltdd_is_true) {
	test_function_created("is_true");
}

Ensure(Lua, open_libs_creates_ltdd_is_of_type) {
	test_function_created("is_of_type");
}

Ensure(Lua, assert_that_throws_error_on_failed_constraint) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd"); // t
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 2); // t f i f i
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_pcall(L, 2, 0, 0), is_not_equal_to(LUA_OK));
}

Ensure(Lua, assert_that_throws_formatted_error_string_1arg) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd"); // t
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_nil"); // t f i f
	lua_pcall(L, 2, 0, 0);
	assert_that(lua_tostring(L, -1), is_equal_to_string("assertion failed: [1] [is_nil]"));
}

Ensure(Lua, assert_that_throws_formatted_error_string_2arg) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd"); // t
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 2); // t f i f i
	lua_pcall(L, 1, 1, 0);
	lua_pcall(L, 2, 0, 0);
	assert_that(lua_tostring(L, -1), is_equal_to_string("assertion failed: [1] [is_equal_to] [2]"));
}

Ensure(Lua, assert_that_passes_on_fulfilled_constraint) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd"); // t
	lua_getfield(L, -1, "assert_that"); // t f
	lua_pushinteger(L, 1); // t f i
	lua_getfield(L, -3, "is_equal_to"); // t f i f
	lua_pushinteger(L, 1); // t f i f i
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_pcall(L, 2, 0, 0), is_equal_to(LUA_OK));
}

Ensure(Lua, is_equal_to_evals_true_if_equal) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_equal_to_evals_false_if_not_equal) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_not_equal_to_evals_true_if_not_equal) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_not_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_not_equal_to_evals_false_if_equal) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_not_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_greater_than_evals_true_if_greater_than) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_greater_than");
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_greater_than_evals_false_if_not_greater_than) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_greater_than");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_less_than_evals_true_if_less_than) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_less_than");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_less_than_evals_false_if_not_less_than) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_less_than");
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_nil_evals_true_if_nil) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushnil(L);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_nil_evals_false_if_not_nil) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_not_nil_evals_true_if_not_nil) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_not_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_not_nil_evals_false_if_nil) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_not_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushnil(L);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_false_evals_true_if_false) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_false");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_false_evals_false_if_true) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_false");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

Ensure(Lua, is_true_evals_true_if_true) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_true");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
	lua_close(L);
}

Ensure(Lua, is_true_evals_false_if_false) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, "is_true");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
	lua_close(L);
}

TestSuite *test_lua(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, Lua, open_libs_provides_valid_state);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_table);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_assert_that);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_equal_to);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_not_equal_to);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_greater_than);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_less_than);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_nil);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_not_nil);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_false);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_true);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_is_of_type);
	add_test_with_context(suite, Lua, assert_that_throws_error_on_failed_constraint);
	add_test_with_context(suite, Lua, assert_that_throws_formatted_error_string_1arg);
	add_test_with_context(suite, Lua, assert_that_throws_formatted_error_string_2arg);
	add_test_with_context(suite, Lua, assert_that_passes_on_fulfilled_constraint);
	add_test_with_context(suite, Lua, is_equal_to_evals_true_if_equal);
	add_test_with_context(suite, Lua, is_equal_to_evals_false_if_not_equal);
	add_test_with_context(suite, Lua, is_greater_than_evals_true_if_greater_than);
	add_test_with_context(suite, Lua, is_greater_than_evals_false_if_not_greater_than);
	add_test_with_context(suite, Lua, is_less_than_evals_true_if_less_than);
	add_test_with_context(suite, Lua, is_less_than_evals_false_if_not_less_than);
	add_test_with_context(suite, Lua, is_not_equal_to_evals_true_if_not_equal);
	add_test_with_context(suite, Lua, is_not_equal_to_evals_false_if_equal);
	add_test_with_context(suite, Lua, is_nil_evals_true_if_nil);
	add_test_with_context(suite, Lua, is_nil_evals_false_if_not_nil);
	add_test_with_context(suite, Lua, is_not_nil_evals_true_if_not_nil);
	add_test_with_context(suite, Lua, is_not_nil_evals_false_if_nil);
	add_test_with_context(suite, Lua, is_false_evals_true_if_false);
	add_test_with_context(suite, Lua, is_false_evals_false_if_true);
	add_test_with_context(suite, Lua, is_true_evals_true_if_true);
	add_test_with_context(suite, Lua, is_true_evals_false_if_false);

	return suite;
}

static void test_function_created(const char *name) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, name);
	assert_that(lua_type(L, -1), is_equal_to(LUA_TFUNCTION));
	lua_close(L);
}
