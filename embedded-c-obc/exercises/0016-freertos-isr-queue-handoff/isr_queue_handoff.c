#include "isr_queue_handoff.h"

#include <stddef.h>

#define IMU_ISR_QUEUE_DEPTH ((UBaseType_t)3)

QueueHandle_t isr_queue_create(void)
{
    return xQueueCreate(IMU_ISR_QUEUE_DEPTH, sizeof(ImuSample));
}

void isr_queue_handoff_init(IsrQueueHandoff *handoff, QueueHandle_t sample_queue)
{
    if (handoff == NULL)
    {
        return;
    }

    handoff->sample_queue = sample_queue;
    handoff->isr_send_count = 0u;
    handoff->isr_drop_count = 0u;
}

BaseType_t imu_sample_ready_from_isr(
    IsrQueueHandoff *handoff,
    const ImuSample *sample,
    BaseType_t *out_higher_priority_task_woken)
{
    if (out_higher_priority_task_woken != NULL)
    {
        *out_higher_priority_task_woken = pdFALSE;
    }

    /* TODO: validate inputs, call xQueueSendFromISR, and update ISR counters. */
    (void)handoff;
    (void)sample;

    return pdFAIL;
}
