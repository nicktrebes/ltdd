#include "test.h"

Describe(lua_open_libs);
BeforeEach(lua_open_libs) {}
AfterEach(lua_open_libs) {}

static void test_function_created(const char *name);

Ensure(lua_open_libs, open_libs_provides_valid_state) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "_VERSION");
	assert_that(lua_tostring(L, -1), is_equal_to_string(LUA_VERSION));
	lua_close(L);
}

Ensure(lua_open_libs, open_libs_creates_ltdd_table) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	assert_that(lua_type(L, -1), is_equal_to(LUA_TTABLE));
	lua_close(L);
}

Ensure(lua_open_libs, open_libs_creates_ltdd_assert_that) {
	test_function_created("assert_that");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_create_context) {
	test_function_created("create_context");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_equal_to) {
	test_function_created("is_equal_to");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_not_equal_to) {
	test_function_created("is_not_equal_to");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_greater_than) {
	test_function_created("is_greater_than");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_less_than) {
	test_function_created("is_less_than");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_nil) {
	test_function_created("is_nil");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_not_nil) {
	test_function_created("is_not_nil");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_false) {
	test_function_created("is_false");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_true) {
	test_function_created("is_true");
}

Ensure(lua_open_libs, open_libs_creates_ltdd_is_of_type) {
	test_function_created("is_of_type");
}

TestSuite *test_lua_open_libs(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, lua_open_libs, open_libs_provides_valid_state);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_table);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_assert_that);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_create_context);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_equal_to);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_not_equal_to);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_greater_than);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_less_than);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_nil);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_not_nil);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_false);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_true);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_is_of_type);

	return suite;
}

static void test_function_created(const char *name) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	lua_getfield(L, -1, name);
	assert_that(lua_type(L, -1), is_equal_to(LUA_TFUNCTION));
	lua_close(L);
}
