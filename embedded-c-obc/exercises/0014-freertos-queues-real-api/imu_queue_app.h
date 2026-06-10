#ifndef IMU_QUEUE_APP_H
#define IMU_QUEUE_APP_H

#include <stdint.h>

#include "FreeRTOS.h"
#include "queue.h"

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
    uint32_t sent_sample_count;
    uint32_t received_sample_count;
    uint32_t dropped_sample_count;
} ImuQueueApp;

QueueHandle_t imu_queue_create(void);
void imu_queue_app_init(ImuQueueApp *app, QueueHandle_t sample_queue);
BaseType_t imu_sensor_send_sample(ImuQueueApp *app, const ImuSample *sample);
BaseType_t imu_flight_receive_sample(ImuQueueApp *app, ImuSample *out_sample);

#endif
