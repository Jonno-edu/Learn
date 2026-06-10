#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum {
    OBC_SOF0 = 0xa5u,
    OBC_SOF1 = 0x5au,
    OBC_MSG_ID_IMU = 0x42u,
    OBC_IMU_PAYLOAD_LEN = 13u,
    OBC_IMU_FRAME_LEN = 18u,
    OBC_CHECKSUM_INDEX = 17u,
    OBC_CHECKSUM_LEN = 1u
};

typedef enum {
    FLIGHT_STATE_IDLE = 0,
    FLIGHT_STATE_BOOST = 1,
    FLIGHT_STATE_COAST = 2,
    FLIGHT_STATE_DESCENT = 3
} FlightState;

typedef struct {
    int16_t accel_x_mg;
    int16_t accel_y_mg;
    int16_t accel_z_mg;
    int16_t gyro_x_dps;
    int16_t gyro_y_dps;
    int16_t gyro_z_dps;
} ImuSample;

/* Return the low byte of the sum of a run of packet bytes. */
static uint8_t checksum(const uint8_t *bytes, size_t len)
{
    uint8_t checksum_count = 0;

    size_t i;
    for (i = 0; i < len; i++)
    {
        checksum_count += bytes[i];
    }

    return checksum_count;
}

/* Write one signed 16-bit value into two output bytes in little-endian order. */
static void pack_i16_le(uint8_t *dst, int16_t value)
{
    dst[0] = (uint8_t)(value & 0xff);
    dst[1] = (uint8_t)((value >> 8u) & 0xff);
}

/* Return true only for flight states that the telemetry protocol accepts. */
static bool is_valid_flight_state(FlightState state)
{
    return state >= FLIGHT_STATE_IDLE && state <= FLIGHT_STATE_DESCENT;
}

/* Pack one IMU sample and flight state into a bounded telemetry frame. */
static bool pack_imu_packet(const ImuSample *imu,
                            FlightState state,
                            uint8_t *out_frame,
                            size_t out_capacity,
                            size_t *out_len)
{

    if (imu == NULL || out_frame == NULL || out_len == NULL)
    {
        return false;
    }

    if (out_capacity < OBC_IMU_FRAME_LEN)
    {
        return false;
    }

    if (!is_valid_flight_state(state))
    {
        return false;
    }    


    out_frame[0] = OBC_SOF0;
    out_frame[1] = OBC_SOF1;
    out_frame[2] = OBC_MSG_ID_IMU;
    out_frame[3] = OBC_IMU_PAYLOAD_LEN;
    out_frame[4] = state;

    pack_i16_le(&out_frame[5], imu->accel_x_mg);
    pack_i16_le(&out_frame[7], imu->accel_y_mg);
    pack_i16_le(&out_frame[9], imu->accel_z_mg);
    pack_i16_le(&out_frame[11], imu->gyro_x_dps);
    pack_i16_le(&out_frame[13], imu->gyro_y_dps);
    pack_i16_le(&out_frame[15], imu->gyro_z_dps);

    out_frame[OBC_CHECKSUM_INDEX] = checksum(&out_frame[2], 15u);
    *out_len = OBC_IMU_FRAME_LEN;

    return true;
}

/* Run the exercise checks that define the packet packing contract. */
int main(void)
{
    const ImuSample imu = {
        .accel_x_mg = -200,
        .accel_y_mg = 0,
        .accel_z_mg = 981,
        .gyro_x_dps = 12,
        .gyro_y_dps = -34,
        .gyro_z_dps = 56
    };

    uint8_t frame[OBC_IMU_FRAME_LEN] = {0};
    size_t frame_len = 0u;

    assert(checksum((const uint8_t[]){0x42u, 0x0du, 0x01u}, 3u) == 0x50u);

    uint8_t packed_negative[2] = {0};
    pack_i16_le(packed_negative, -200);
    assert(packed_negative[0] == 0x38u);
    assert(packed_negative[1] == 0xffu);

    uint8_t packed_positive[2] = {0};
    pack_i16_le(packed_positive, 981);
    assert(packed_positive[0] == 0xd5u);
    assert(packed_positive[1] == 0x03u);

    assert(is_valid_flight_state(FLIGHT_STATE_IDLE));
    assert(is_valid_flight_state(FLIGHT_STATE_BOOST));
    assert(is_valid_flight_state(FLIGHT_STATE_COAST));
    assert(is_valid_flight_state(FLIGHT_STATE_DESCENT));
    assert(!is_valid_flight_state((FlightState)4));

    assert(!pack_imu_packet(NULL, FLIGHT_STATE_BOOST, frame, sizeof(frame), &frame_len));
    assert(!pack_imu_packet(&imu, FLIGHT_STATE_BOOST, NULL, sizeof(frame), &frame_len));
    assert(!pack_imu_packet(&imu, FLIGHT_STATE_BOOST, frame, sizeof(frame), NULL));
    assert(!pack_imu_packet(&imu, (FlightState)4, frame, sizeof(frame), &frame_len));
    assert(!pack_imu_packet(&imu, FLIGHT_STATE_BOOST, frame, OBC_IMU_FRAME_LEN - 1u, &frame_len));

    assert(pack_imu_packet(&imu, FLIGHT_STATE_BOOST, frame, sizeof(frame), &frame_len));
    assert(frame_len == OBC_IMU_FRAME_LEN);
    assert(frame[0] == OBC_SOF0);
    assert(frame[1] == OBC_SOF1);
    assert(frame[2] == OBC_MSG_ID_IMU);
    assert(frame[3] == OBC_IMU_PAYLOAD_LEN);
    assert(frame[4] == FLIGHT_STATE_BOOST);

    assert(frame[5] == 0x38u);
    assert(frame[6] == 0xffu);
    assert(frame[7] == 0x00u);
    assert(frame[8] == 0x00u);
    assert(frame[9] == 0xd5u);
    assert(frame[10] == 0x03u);
    assert(frame[11] == 0x0cu);
    assert(frame[12] == 0x00u);
    assert(frame[13] == 0xdeu);
    assert(frame[14] == 0xffu);
    assert(frame[15] == 0x38u);
    assert(frame[16] == 0x00u);
    assert(frame[17] == 0x80u);

    puts("PASS: pack IMU telemetry exercise");
    return 0;
}
