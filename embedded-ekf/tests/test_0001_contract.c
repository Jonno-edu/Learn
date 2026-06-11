#include "eskf/eskf_types.h"

#include <stddef.h>
#include <stdio.h>

static int expect_int(const char *name, int actual, int expected)
{
    if (actual != expected) {
        (void)printf("FAIL %s: got %d, expected %d\n", name, actual, expected);
        return 1;
    }

    (void)printf("PASS %s\n", name);
    return 0;
}

static int test_dimensions(void)
{
    int failures = 0;

    failures += expect_int("ESKF_VEC3_DIM", ESKF_VEC3_DIM, 3);
    failures += expect_int("ESKF_QUAT_DIM", ESKF_QUAT_DIM, 4);
    failures += expect_int("ESKF_NOMINAL_STATE_DIM", ESKF_NOMINAL_STATE_DIM, 16);
    failures += expect_int("ESKF_ERROR_STATE_DIM", ESKF_ERROR_STATE_DIM, 15);
    failures += expect_int("ESKF_IMU_NOISE_DIM", ESKF_IMU_NOISE_DIM, 12);
    failures += expect_int("ESKF_GPS_POS_VEL_DIM", ESKF_GPS_POS_VEL_DIM, 6);

    return failures;
}

static int test_type_contract(void)
{
    int failures = 0;

    failures += expect_int("eskf_real_t defaults to float",
                           (int)sizeof(eskf_real_t),
                           (int)sizeof(float));
    failures += expect_int("status ok is zero", ESKF_STATUS_OK, 0);
    failures += expect_int("local NED frame id is zero", ESKF_FRAME_LOCAL_NED, 0);

    return failures;
}

int main(void)
{
    int failures = 0;

    failures += test_dimensions();
    failures += test_type_contract();

    if (failures != 0) {
        (void)printf("\nLesson 0001 is intentionally red until the dimension placeholders are filled.\n");
        return 1;
    }

    (void)printf("\nLesson 0001 contract tests passed.\n");
    return 0;
}

