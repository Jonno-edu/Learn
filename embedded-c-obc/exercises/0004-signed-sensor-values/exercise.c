#include <assert.h>
#include <stdint.h>
#include <stdio.h>

enum {
    ACCEL_MILLI_G_PER_COUNT = 61
};

static int16_t accel_counts_from_bytes(uint8_t msb, uint8_t lsb)
{
    uint16_t raw = ((uint16_t) msb << 8) | (uint16_t) lsb;
    int16_t counts = (int16_t) raw;
    return counts;
}

static int32_t accel_milli_g_from_counts(int16_t counts)
{
    return (int32_t) counts * ACCEL_MILLI_G_PER_COUNT;
}

static int32_t accel_milli_g_from_bytes(uint8_t msb, uint8_t lsb)
{
    return accel_milli_g_from_counts(accel_counts_from_bytes(msb, lsb));
}

int main(void)
{
    assert(accel_counts_from_bytes(0x00u, 0x00u) == 0);
    assert(accel_counts_from_bytes(0x00u, 0x64u) == 100);
    assert(accel_counts_from_bytes(0xffu, 0x38u) == -200);
    assert(accel_counts_from_bytes(0x7fu, 0xffu) == 32767);
    assert(accel_counts_from_bytes(0x80u, 0x00u) == -32768);

    assert(accel_milli_g_from_counts(0) == 0);
    assert(accel_milli_g_from_counts(100) == 6100);
    assert(accel_milli_g_from_counts(-200) == -12200);
    assert(accel_milli_g_from_counts(32767) == 1998787);
    assert(accel_milli_g_from_counts(-32768) == -1998848);

    assert(accel_milli_g_from_bytes(0x00u, 0x64u) == 6100);
    assert(accel_milli_g_from_bytes(0xffu, 0x38u) == -12200);

    puts("PASS: signed sensor values exercise");
    return 0;
}
