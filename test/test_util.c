#include "test.h"

Describe(Util);
BeforeEach(Util) {}
AfterEach(Util) {}

Ensure(Util, parse_args_returns_zero_on_no_args) {
	int srcc, tstc;
	assert_that(ltdd_util_parse_args(0, NULL, &srcc, NULL, &tstc, NULL), is_equal_to(0));
}

Ensure(Util, parse_args_sets_srcc_zero_on_no_args) {
	int srcc = 1, tstc;
	ltdd_util_parse_args(0, NULL, &srcc, NULL, &tstc, NULL);
	assert_that(srcc, is_equal_to(0));
}

Ensure(Util, parse_args_sets_tstc_zero_on_no_args) {
	int srcc, tstc = 1;
	ltdd_util_parse_args(0, NULL, &srcc, NULL, &tstc, NULL);
	assert_that(tstc, is_equal_to(0));
}

TestSuite *test_util() {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, Util, parse_args_returns_zero_on_no_args);
	add_test_with_context(suite, Util, parse_args_sets_srcc_zero_on_no_args);
	add_test_with_context(suite, Util, parse_args_sets_tstc_zero_on_no_args);

	return suite;
}
