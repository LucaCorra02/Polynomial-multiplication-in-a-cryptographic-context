#include "../../munit/munit.h"
#include "f3Utils.h"
#include "f9Utils.h"

/*
 * Le funzioni di test ritornano MUNIT_OK se il test passa,
 * altrimenti generano un'asserzione fallita.
 */

static MunitResult test_kthbit(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int input[] = {0b1011, 0b1010, 0b1110};
    int expected[] = {0b1, 0b0, 0b0};
    int dim = 3;

    for (int i = 0; i < dim; ++i) {
        int ris = kth_bit(input[i], 0);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_swapbits(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int input[] = {0b00, 0b01, 0b10, 0b11};
    int expected[] = {0b00, 0b10, 0b01, 0b00};
    int dim = 4;

    for (int i = 0; i < dim; ++i){
        int ris = swap_bits(input[i]);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_int_to_f3(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int input[] = {0, 1, 2, 3, 1000, -1, -2, -3, -1000};
    int expected[] = {0, 1, 2, 0, 1, 2, 1, 0, 2};
    int dim = 9;

    for (int i = 0; i < dim; ++i){
        int ris = int_to_f3(input[i]);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_f3_sum(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int a[] = {0, 1, 2, 3, 1000, -1, -2, -3, -1000};
    int b[] = {0, 1, 2, 3, 1000, -1, -2, -3, -1000};
    int expected[] = {0, 2, 1, 0, 2, 1, 2, 0, 1};
    int dim = 9;

    for (int i = 0; i < dim; ++i){
        unsigned int ris = f3_sum(int_to_f3(a[i]),int_to_f3(b[i]));
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_kthbit", test_kthbit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_swapbits", test_swapbits, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_int_to_f3", test_int_to_f3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_int_f3_sum", test_f3_sum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/f3Utils_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}