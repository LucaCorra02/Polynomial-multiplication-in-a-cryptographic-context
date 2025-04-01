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

static MunitResult test_schoolbook_f9(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element p1[] = {
        get_f9_element(1,2), get_f9_element(0,0), get_f9_element(1,1), get_f9_element(0,0), get_f9_element(0,1),
        get_f9_element(2,0), get_f9_element(1,2), get_f9_element(2,2), get_f9_element(1,2), get_f9_element(0,2)
    };
    f9_element p2[] = {
        get_f9_element(2,2), get_f9_element(1,2), get_f9_element(0,1), get_f9_element(2,0), get_f9_element(1,0),
        get_f9_element(2,0), get_f9_element(0,2), get_f9_element(1,0), get_f9_element(2,2), get_f9_element(1,0)
    };
    f9_element expected[] = {
        get_f9_element(0,2), get_f9_element(1,0), get_f9_element(2,2), get_f9_element(1,2), get_f9_element(2,2),
        get_f9_element(2,0), get_f9_element(1,1), get_f9_element(2,0), get_f9_element(1,0), get_f9_element(1,0),
        get_f9_element(1,2), get_f9_element(1,1), get_f9_element(2,2), get_f9_element(2,0), get_f9_element(2,2),
        get_f9_element(0,2), get_f9_element(1,0), get_f9_element(0,0), get_f9_element(2,0)
    };
    int dim = 10;
    int dim_ris = 2*dim -1;

    f9_element* ris = schoolbook_f9(dim, p1, p2);

    for (int j = 0; j < dim_ris; ++j) {
        munit_assert_int(ris[j], ==, expected[j]);
    }
    return MUNIT_OK;
}

static MunitResult test_poly_sum_f9(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element p1[] = {
        get_f9_element(1,2), get_f9_element(0,0), get_f9_element(1,1), get_f9_element(1,0)
    };
    f9_element p2[] = {
        get_f9_element(2,2), get_f9_element(1,2)
    };
    f9_element expected[] = {
        get_f9_element(0,1), get_f9_element(1,2), get_f9_element(1,1), get_f9_element(1,0)

    };

    f9_element ris[4] = {0, 0, 0, 0};
    int dim_p1 = 4;
    int dim_p2 = 2;
    sum_poly(dim_p1, dim_p2, p1, p2, ris);
    for (int j = 0; j < dim_p1; ++j) {
      munit_assert_int(ris[j], ==, expected[j]);
    }
    return MUNIT_OK;
}

static MunitResult test_poly_diff_f9(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element p1[] = {
        get_f9_element(1,2), get_f9_element(0,0), get_f9_element(2,2), get_f9_element(1,0)
    };
    f9_element p2[] = {
        get_f9_element(2,1), get_f9_element(1,2), get_f9_element(1,2)
    };
    f9_element expected[] = {
        get_f9_element(2,1), get_f9_element(2,1), get_f9_element(1,0), get_f9_element(1,0)

    };

    f9_element ris[4] = {0,0,0,0};
    int dim_p1 = 4;
    int dim_p2 = 3;
    diff_poly(dim_p1, dim_p2, p1, p2, ris);
    for (int j = 0; j < dim_p1; ++j) {
        munit_assert_int(ris[j], ==, expected[j]);
    }

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_split_params", test_split_params, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_schoolbook_f9", test_schoolbook_f9, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_poly_sum_f9", test_poly_sum_f9, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_poly_diff_f9", test_poly_diff_f9, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/3split_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    munit_suite_main(&suite, NULL, argc, argv);
    f9_element p1[] = {
        get_f9_element(1,2), get_f9_element(0,0), get_f9_element(1,1), get_f9_element(0,0), get_f9_element(0,1),
        get_f9_element(2,0), get_f9_element(1,2)
    };
    f9_element p2[] = {
        get_f9_element(2,2), get_f9_element(1,2), get_f9_element(0,1), get_f9_element(2,0), get_f9_element(1,0),
        get_f9_element(2,0), get_f9_element(0,2)
    };
    f9_element* ris = split_3_f9(7, p1,p2);
    if (ris != NULL){
        print_vector_f9(ris, 7*2-1);
    }
}

