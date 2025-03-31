#include "../../munit/munit.h"
#include "f3Utils.h"
#include "f9Utils.h"

/*
 * Le funzioni di test ritornano MUNIT_OK se il test passa, altrimenti generano un'asserzione fallita.
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

static MunitResult test_f3_prod(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int a[] = {0, 1, 2, 3, 1000, -1, -2, -3, -1000};
    int b[] = {0, 1, 2, 3, 1000, -1, -1, -3, -1};
    int expected[] = {0, 1, 1, 0, 1, 1, 2, 0, 1};
    int dim = 9;

    for (int i = 0; i < dim; ++i){
        unsigned int ris = f3_prod(int_to_f3(a[i]),int_to_f3(b[i]));
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_get_f9_element(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    int img[] = {0, 2, 3, 10, -4, 5, 8};
    int real[] = {0, 1, 2, 3, -1, -1, -2};
    int expected[] = {0b0000, 0b1001, 0b0010, 0b0100, 0b1010, 0b1010, 0b1001};
    int dim = 7;

    for (int i = 0; i < dim; ++i){
        f9_element ris = get_f9_element(img[i], real[i]) ;
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_getter_f9(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element f9[] = {get_f9_element(0,0), get_f9_element(1,-1), get_f9_element(-1,-2), get_f9_element(7,-3) };
    int expected_img[] = {0, 1, 2, 1};
    int expected_real[] = {0, 2, 1, 0};
    int dim = 4;

    for (int i = 0; i < dim; ++i){
        unsigned int ris_img = get_imaginary_part(f9[i]);
        unsigned int ris_real = get_real_part(f9[i]);
        munit_assert_int(ris_img, ==, expected_img[i]);
        munit_assert_int(ris_real, ==, expected_real[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_f9_sum(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element a[] = {get_f9_element(0,0), get_f9_element(1,-1), get_f9_element(1,-1), get_f9_element(-134,23)};
    f9_element b[] = {get_f9_element(0,0), get_f9_element(-3,-1), get_f9_element(1,-2), get_f9_element(7, 11)};
    f9_element expected[] = {get_f9_element(0,0), get_f9_element(1,1), get_f9_element(2,0), get_f9_element(2,1)};
    int dim = 4;
    for (int i = 0; i < dim; ++i){
        f9_element ris = f9_sum(a[i],b[i]);
        //print_f9_element(ris);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_f9_prod(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element a[] = {get_f9_element(0,0), get_f9_element(1,-1), get_f9_element(1,-1), get_f9_element(-134,23)};
    f9_element b[] = {get_f9_element(0,0), get_f9_element(-3,-1), get_f9_element(1,-2), get_f9_element(8, 11)};
    f9_element expected[] = {get_f9_element(0,0), get_f9_element(2,1), get_f9_element(0,1), get_f9_element(0,2)};
    int dim = 4;
    for (int i = 0; i < dim; ++i){
        f9_element ris = f9_prod(a[i],b[i]);
        //print_f9_element(ris);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_int_to_f9_element(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element input[] = {0b0000, 0b1001, 0b1111, 0b0110, 0b0101, 0b100101};
    f9_element expected[] = {get_f9_element(0,0), get_f9_element(2,1), get_f9_element(0,0), get_f9_element(1,2), get_f9_element(1,1), get_f9_element(1,1)};
    int dim = 6;
    for (int i = 0; i < dim; ++i){
        f9_element ris = int_to_f9_element(input[i]);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_swap_f9(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    f9_element input[] = {0b0000, 0b1001, 0b1111, 0b0110, 0b0101, 0b1010};
    f9_element expected[] = {get_f9_element(0,0), get_f9_element(1,2), get_f9_element(0,0), get_f9_element(2,1), get_f9_element(2,2), get_f9_element(1,1)};
    int dim = 6;
    for (int i = 0; i < dim; ++i){
        f9_element ris = f9_neg(input[i]);
        munit_assert_int(ris, ==, expected[i]);
    }
    return MUNIT_OK;
}


static MunitTest tests[] = {
    { "/test_kthbit", test_kthbit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_swapbits", test_swapbits, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_int_to_f3", test_int_to_f3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_int_f3_sum", test_f3_sum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f3_prod", test_f3_prod, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_f9_element", test_get_f9_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_getter_f9", test_getter_f9, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f9_sum", test_f9_sum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f9_prod", test_f9_prod, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_int_to_f9_element", test_int_to_f9_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/ test_swap_f9",  test_swap_f9, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/f3Utils_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}