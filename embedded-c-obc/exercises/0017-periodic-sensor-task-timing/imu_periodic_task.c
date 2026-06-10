#include "sensor_timing_policy.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

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
    SensorTimingPolicy *timing_policy;
    uint32_t period_ms;
} ImuPeriodicTask;

extern bool imu_read_sample(ImuSample *out_sample);

void imu_periodic_task(void *argument)
{
    ImuPeriodicTask *task = (ImuPeriodicTask *)argument;

    if ((task == NULL) || (task->sample_queue == NULL) || (task->timing_policy == NULL))
    {
        vTaskDelete(NULL);
    }

    TickType_t last_wake = xTaskGetTickCount();
    TickType_t period_ticks = pdMS_TO_TICKS(task->period_ms);

    if (period_ticks == (TickType_t)0)
    {
        period_ticks = (TickType_t)1;
    }

    for (;;)
    {
        ImuSample sample;
        bool has_sample = imu_read_sample(&sample);
        BaseType_t sent = pdFAIL;

        if (has_sample)
        {
            sent = xQueueSend(task->sample_queue, &sample, (TickType_t)0);
        }

        (void)sensor_timing_policy_record_send(task->timing_policy, sent == pdPASS);
        vTaskDelayUntil(&last_wake, period_ticks);
    }
}
