#ifndef LTDD_TEST_H
#define LTDD_TEST_H

#include <cgreen/cgreen.h>
#include <ltdd.h>

TestSuite *test_lua_api(void);
TestSuite *test_lua_constraints(void);
TestSuite *test_lua_open_libs(void);
TestSuite *test_util(void);

#endif /* LTDD_TEST_H */
