#include "imu_queue_overflow.h"

#include <stddef.h>

void imu_queue_overflow_init(
    ImuQueueOverflow *runtime,
    QueueHandle_t sample_queue,
    uint32_t drop_fault_threshold)
{
    if (runtime == NULL)
    {
        return;
    }

    runtime->sample_queue = sample_queue;
    imu_drop_policy_init(&runtime->drop_policy, drop_fault_threshold);
}

ImuDropPolicyResult imu_queue_send_with_policy(
    ImuQueueOverflow *runtime,
    const ImuSample *sample,
    TickType_t wait_ticks)
{
    if ((runtime == NULL) || (sample == NULL) || (runtime->sample_queue == NULL))
    {
        return IMU_DROP_POLICY_FAULT;
    }

    BaseType_t sent = xQueueSend(runtime->sample_queue, sample, wait_ticks);
    if (sent == pdPASS)
    {
        return imu_drop_policy_record_send_ok(&runtime->drop_policy);
    }

    return imu_drop_policy_record_send_failed(&runtime->drop_policy);
}
