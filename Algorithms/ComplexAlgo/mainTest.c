#include "3split.h"
#include "../../munit/munit.h"

/*
 * Le funzioni di test ritornano MUNIT_OK se il test passa, altrimenti generano un'asserzione fallita.
*/

static MunitResult test_split_params(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int input[] = {6, 33, 1024, 2048, 499, 324, 323};
    int expected_n[] = {2, 11, 342, 683, 167, 108, 108};
    int expected_k[] = {2, 11, 340, 682, 165, 108, 107};
    int dim = 7;
    int i = 3;

    for (int j = 0; j < dim; ++j) {
        int m = input[j];
        int n = get_split_n_param(m, i);
        int k = get_split_k_param(m, n);
        munit_assert_int(n, ==, expected_n[j]);
        munit_assert_int(k, ==, expected_k[j]);
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_split_params", test_split_params, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/3split_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

