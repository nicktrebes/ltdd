#include "test.h"

Describe(Lua);
BeforeEach(Lua) {}
AfterEach(Lua) {}

Ensure(Lua, open_libs_provides_valid_state) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "_VERSION");
	assert_that(lua_tostring(L, -1), is_equal_to_string(LUA_VERSION));
}

Ensure(Lua, open_libs_creates_ltdd_table) {
	lua_State *L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
	assert_that(lua_type(L, -1), is_equal_to(LUA_TTABLE));
}

TestSuite *test_lua(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, Lua, open_libs_provides_valid_state);
	add_test_with_context(suite, Lua, open_libs_creates_ltdd_table);

	return suite;
}
