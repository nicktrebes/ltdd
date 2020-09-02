#include "test.h"

static lua_State *L = NULL;

Describe(lua_constraints);

BeforeEach(lua_constraints) {
	L = ltdd_lua_open_libs();
	lua_getglobal(L, "ltdd");
}

AfterEach(lua_constraints) {
	lua_close(L);
}

Ensure(lua_constraints, is_equal_to_evals_true_if_equal) {
	lua_getfield(L, -1, "is_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_equal_to_evals_false_if_not_equal) {
	lua_getfield(L, -1, "is_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_not_equal_to_evals_true_if_not_equal) {
	lua_getfield(L, -1, "is_not_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_not_equal_to_evals_false_if_equal) {
	lua_getfield(L, -1, "is_not_equal_to");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_greater_than_evals_true_if_greater_than) {
	lua_getfield(L, -1, "is_greater_than");
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_greater_than_evals_false_if_not_greater_than) {
	lua_getfield(L, -1, "is_greater_than");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_less_than_evals_true_if_less_than) {
	lua_getfield(L, -1, "is_less_than");
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_less_than_evals_false_if_not_less_than) {
	lua_getfield(L, -1, "is_less_than");
	lua_pushinteger(L, 0);
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_nil_evals_true_if_nil) {
	lua_getfield(L, -1, "is_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushnil(L);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_nil_evals_false_if_not_nil) {
	lua_getfield(L, -1, "is_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_not_nil_evals_true_if_not_nil) {
	lua_getfield(L, -1, "is_not_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_not_nil_evals_false_if_nil) {
	lua_getfield(L, -1, "is_not_nil");
	lua_pcall(L, 0, 1, 0);
	lua_pushnil(L);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_false_evals_true_if_false) {
	lua_getfield(L, -1, "is_false");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_false_evals_false_if_true) {
	lua_getfield(L, -1, "is_false");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_true_evals_true_if_true) {
	lua_getfield(L, -1, "is_true");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_true_evals_false_if_false) {
	lua_getfield(L, -1, "is_true");
	lua_pcall(L, 0, 1, 0);
	lua_pushboolean(L, 0);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

Ensure(lua_constraints, is_of_type_evals_true_if_type_name_matches) {
	lua_getfield(L, -1, "is_of_type");
	lua_pushliteral(L, "number");
	lua_pcall(L, 1, 1, 0);
	lua_pushinteger(L, 1);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(1));
}

Ensure(lua_constraints, is_of_type_evals_false_if_type_name_does_not_match) {
	lua_getfield(L, -1, "is_of_type");
	lua_pushliteral(L, "number");
	lua_pcall(L, 1, 1, 0);
	lua_newtable(L);
	lua_pcall(L, 1, 1, 0);
	assert_that(lua_toboolean(L, -1), is_equal_to(0));
}

TestSuite *test_lua_constraints(void) {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, lua_constraints, is_equal_to_evals_true_if_equal);
	add_test_with_context(suite, lua_constraints, is_equal_to_evals_false_if_not_equal);
	add_test_with_context(suite, lua_constraints, is_greater_than_evals_true_if_greater_than);
	add_test_with_context(suite, lua_constraints, is_greater_than_evals_false_if_not_greater_than);
	add_test_with_context(suite, lua_constraints, is_less_than_evals_true_if_less_than);
	add_test_with_context(suite, lua_constraints, is_less_than_evals_false_if_not_less_than);
	add_test_with_context(suite, lua_constraints, is_not_equal_to_evals_true_if_not_equal);
	add_test_with_context(suite, lua_constraints, is_not_equal_to_evals_false_if_equal);
	add_test_with_context(suite, lua_constraints, is_nil_evals_true_if_nil);
	add_test_with_context(suite, lua_constraints, is_nil_evals_false_if_not_nil);
	add_test_with_context(suite, lua_constraints, is_not_nil_evals_true_if_not_nil);
	add_test_with_context(suite, lua_constraints, is_not_nil_evals_false_if_nil);
	add_test_with_context(suite, lua_constraints, is_false_evals_true_if_false);
	add_test_with_context(suite, lua_constraints, is_false_evals_false_if_true);
	add_test_with_context(suite, lua_constraints, is_true_evals_true_if_true);
	add_test_with_context(suite, lua_constraints, is_true_evals_false_if_false);
	add_test_with_context(suite, lua_constraints, is_of_type_evals_true_if_type_name_matches);
	add_test_with_context(suite, lua_constraints, is_of_type_evals_false_if_type_name_does_not_match);

	return suite;
}
