#ifndef ISR_QUEUE_HANDOFF_H
#define ISR_QUEUE_HANDOFF_H

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
    volatile uint32_t isr_send_count;
    volatile uint32_t isr_drop_count;
} IsrQueueHandoff;

QueueHandle_t isr_queue_create(void);
void isr_queue_handoff_init(IsrQueueHandoff *handoff, QueueHandle_t sample_queue);
BaseType_t imu_sample_ready_from_isr(
    IsrQueueHandoff *handoff,
    const ImuSample *sample,
    BaseType_t *out_higher_priority_task_woken);

#endif
