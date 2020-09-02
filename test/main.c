#include "test.h"

int main(int argc, char **argv) {
	TestSuite *global = create_test_suite();
	TestReporter *reporter = create_text_reporter();

	add_suite(global, test_lua_open_libs());
	add_suite(global, test_lua_constraints());
	add_suite(global, test_lua_api());
	add_suite(global, test_util());

	return (argc > 1) ?
		run_single_test(global, argv[1], reporter) :
		run_test_suite(global, reporter);
}
