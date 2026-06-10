#ifndef IMU_QUEUE_OVERFLOW_H
#define IMU_QUEUE_OVERFLOW_H

#include <stdint.h>

#include "FreeRTOS.h"
#include "queue.h"

#include "drop_policy.h"

typedef struct
{
    uint32_t sequence;
    int16_t accel_mg[3];
    int16_t gyro_mdps[3];
    TickType_t sampled_at_tick;
} ImuSample;

typedef struct
{
    QueueHandle_t sample_queue;
    ImuDropPolicy drop_policy;
} ImuQueueOverflow;

void imu_queue_overflow_init(
    ImuQueueOverflow *runtime,
    QueueHandle_t sample_queue,
    uint32_t drop_fault_threshold);

ImuDropPolicyResult imu_queue_send_with_policy(
    ImuQueueOverflow *runtime,
    const ImuSample *sample,
    TickType_t wait_ticks);

#endif
