#include "test.h"

static const char *ltdd_functions[] = {
	"assert_that",
	"create_context",
	"is_equal_to",
	"is_not_equal_to",
	"is_greater_than",
	"is_less_than",
	"is_of_type",
	"is_nil",
	"is_not_nil",
	"is_false",
	"is_true",
	NULL
};

static lua_State *L = NULL;

Describe(lua_open_libs);

BeforeEach(lua_open_libs) {
	L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
}

AfterEach(lua_open_libs) {
	lua_close(L);
}

Ensure(lua_open_libs, open_libs_provides_valid_state) {
	lua_getglobal(L, "_VERSION");
	assert_that(lua_tostring(L, -1), is_equal_to_string(LUA_VERSION));
}

Ensure(lua_open_libs, open_libs_creates_ltdd_table) {
	assert_that(lua_type(L, -1), is_equal_to(LUA_TTABLE));
	for (int i = 0; ltdd_functions[i] != NULL; ++i) {
		lua_getfield(L, -1, ltdd_functions[i]);
		assert_that(lua_type(L, -1), is_equal_to(LUA_TFUNCTION));
		lua_pop(L, 1);
	}
}

TestSuite *test_lua_open_libs(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, lua_open_libs, open_libs_provides_valid_state);
	add_test_with_context(suite, lua_open_libs, open_libs_creates_ltdd_table);

	return suite;
}
