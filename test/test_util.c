#include "test.h"

Describe(Util);
BeforeEach(Util) {}
AfterEach(Util) {}

Ensure(Util, list_dir_throws_on_invalid_dir) {
	int fc;
	assert_that(ltdd_util_list_dir("/DoesNotExist", &fc, NULL), is_not_equal_to(0));
}

Ensure(Util, list_dir_returns_zero_on_valid_dir) {
	char **fv;
	int fc;
	assert_that(ltdd_util_list_dir("dummy", &fc, &fv), is_equal_to(0));
}

Ensure(Util, list_dir_sets_fc_on_valid_dir) {
	char **fv;
	int fc = 0;
	ltdd_util_list_dir("dummy", &fc, &fv);
	assert_that(fc, is_equal_to(3));
}

Ensure(Util, list_dir_provides_entry_paths) {
	char **fv = NULL;
	int fc = 0;
	ltdd_util_list_dir("dummy", &fc, &fv);

	assert_that(fv, is_not_equal_to(NULL));

	int file0 = 0, file1 = 0, file2 = 0;
	for (int i = 0; i < fc; ++i) {
		if (strcmp(fv[i], "dummy/file0") == 0) {
			file0 = 1;
		} else if (strcmp(fv[i], "dummy/file1") == 0) {
			file1 = 1;
		} else if (strcmp(fv[i], "dummy/file2") == 0) {
			file2 = 1;
		}
	}

	assert_that(file0+file1+file2, is_equal_to(fc));
}

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

Ensure(Util, parse_args_provides_src_given_files) {
	char *argv[] = {".", "-ftest0.lua", "-ftest1.lua", "-ftest2.lua"};
	char **srcv, **tstv;
	int srcc = 0, tstc;
	ltdd_util_parse_args(4, argv, &srcc, &srcv, &tstc, &tstv);
	assert_that(srcc, is_equal_to(3));
	assert_that(srcv, is_not_equal_to(NULL));
	assert_that(srcv[0], is_equal_to_string("test0.lua"));
	assert_that(srcv[1], is_equal_to_string("test1.lua"));
	assert_that(srcv[2], is_equal_to_string("test2.lua"));
}

Ensure(Util, parse_args_provides_src_given_dir) {
	char *argv[] = {".", "-ddummy"};
	char **srcv, **tstv;
	int srcc = 0, tstc;
	ltdd_util_parse_args(2, argv, &srcc, &srcv, &tstc, &tstv);
	assert_that(srcc, is_equal_to(3));
	assert_that(srcv, is_not_equal_to(NULL));

	int file0 = 0, file1 = 0, file2 = 0;
	for (int i = 0; i < srcc; ++i) {
		if (strcmp(srcv[i], "dummy/file0") == 0) {
			file0 = 1;
		} else if (strcmp(srcv[i], "dummy/file1") == 0) {
			file1 = 1;
		} else if (strcmp(srcv[i], "dummy/file2") == 0) {
			file2 = 1;
		}
	}

	assert_that(file0+file1+file2, is_equal_to(srcc));
}

Ensure(Util, parse_args_provides_tst_given_tests) {
	char *argv[] = {".", "test0", "test1", "test2"};
	char **srcv, **tstv;
	int srcc, tstc = 0;
	ltdd_util_parse_args(4, argv, &srcc, &srcv, &tstc, &tstv);
	assert_that(tstc, is_equal_to(3));
	assert_that(tstv, is_not_equal_to(NULL));
	assert_that(tstv[0], is_equal_to_string("test0"));
	assert_that(tstv[1], is_equal_to_string("test1"));
	assert_that(tstv[2], is_equal_to_string("test2"));
}

Ensure(Util, parse_args_throws_on_invalid_switch) {
	char *argv[] = {".", "-x"};
	char **srcv, **tstv;
	int srcc, tstc = 0;
	assert_that(ltdd_util_parse_args(4, argv, &srcc, &srcv, &tstc, &tstv), is_not_equal_to(0));
}

TestSuite *test_util() {
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, Util, list_dir_throws_on_invalid_dir);
	add_test_with_context(suite, Util, list_dir_returns_zero_on_valid_dir);
	add_test_with_context(suite, Util, list_dir_sets_fc_on_valid_dir);
	add_test_with_context(suite, Util, list_dir_provides_entry_paths);
	add_test_with_context(suite, Util, parse_args_returns_zero_on_no_args);
	add_test_with_context(suite, Util, parse_args_sets_srcc_zero_on_no_args);
	add_test_with_context(suite, Util, parse_args_sets_tstc_zero_on_no_args);
	add_test_with_context(suite, Util, parse_args_provides_src_given_files);
	add_test_with_context(suite, Util, parse_args_provides_src_given_dir);
	add_test_with_context(suite, Util, parse_args_provides_tst_given_tests);
	add_test_with_context(suite, Util, parse_args_throws_on_invalid_switch);

	return suite;
}
