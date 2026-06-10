#ifndef IMU_HEALTH_H
#define IMU_HEALTH_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    IMU_HEALTH_OK,
    IMU_HEALTH_DROP_RECORDED,
    IMU_HEALTH_EMPTY_RECORDED,
    IMU_HEALTH_FAULT
} ImuHealthResult;

typedef struct
{
    uint32_t drop_fault_threshold;
    uint32_t empty_receive_fault_threshold;
    uint32_t queued_sample_count;
    uint32_t queue_drop_count;
    uint32_t empty_receive_count;
    uint32_t consecutive_empty_receive_count;
    uint32_t last_sequence;
    uint32_t last_sample_tick;
    bool has_sample;
    bool overload_fault_latched;
    bool freshness_fault_latched;
} ImuHealth;

void imu_health_init(
    ImuHealth *health,
    uint32_t drop_fault_threshold,
    uint32_t empty_receive_fault_threshold);
ImuHealthResult imu_health_record_queued_sample(
    ImuHealth *health,
    uint32_t sequence,
    uint32_t now_tick);
ImuHealthResult imu_health_record_queue_drop(ImuHealth *health);
ImuHealthResult imu_health_record_empty_receive(ImuHealth *health);

#endif
