#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum {
    BMP280_STATUS_IM_UPDATE = 1u << 0,
    BMP280_STATUS_MEASURING = 1u << 3,
    BMP280_PRESS_MSB_SHIFT = 12u,
    BMP280_PRESS_LSB_SHIFT = 4u,
    BMP280_PRESS_XLSB_SHIFT = 4u,
    BMP280_RAW_PRESSURE_MAX = 0xfffffu
};

static bool bmp280_is_measuring(uint8_t status)
{
    return (status & BMP280_STATUS_MEASURING) == BMP280_STATUS_MEASURING;
}

static bool bmp280_is_image_update_running(uint8_t status)
{
    return (status & BMP280_STATUS_IM_UPDATE) == BMP280_STATUS_IM_UPDATE;
}

static uint32_t bmp280_raw_pressure(uint8_t press_msb, uint8_t press_lsb, uint8_t press_xlsb)
{
    return 
    ((uint32_t)press_msb << BMP280_PRESS_MSB_SHIFT) |
    ((uint32_t)press_lsb << BMP280_PRESS_LSB_SHIFT)  | 
    ((uint32_t)press_xlsb >> BMP280_PRESS_XLSB_SHIFT);

}

int main(void)
{
    assert(!bmp280_is_measuring(0u));
    assert(bmp280_is_measuring(BMP280_STATUS_MEASURING));
    assert(bmp280_is_measuring(BMP280_STATUS_MEASURING | BMP280_STATUS_IM_UPDATE));
    assert(!bmp280_is_measuring(BMP280_STATUS_IM_UPDATE));

    assert(!bmp280_is_image_update_running(0u));
    assert(bmp280_is_image_update_running(BMP280_STATUS_IM_UPDATE));
    assert(bmp280_is_image_update_running(BMP280_STATUS_MEASURING | BMP280_STATUS_IM_UPDATE));
    assert(!bmp280_is_image_update_running(BMP280_STATUS_MEASURING));

    assert(bmp280_raw_pressure(0x00u, 0x00u, 0x00u) == 0x00000u);
    assert(bmp280_raw_pressure(0x00u, 0x00u, 0xf0u) == 0x0000fu);
    assert(bmp280_raw_pressure(0x12u, 0x34u, 0x50u) == 0x12345u);
    assert(bmp280_raw_pressure(0xabu, 0xcdu, 0xe0u) == 0xabcdeu);
    assert(bmp280_raw_pressure(0xffu, 0xffu, 0xffu) == BMP280_RAW_PRESSURE_MAX);

    puts("PASS: real sensor register exercise");
    return 0;
}
