#include "imu_queue_overflow.h"

#include <assert.h>
#include <stdio.h>

static ImuSample make_sample(uint32_t sequence)
{
    ImuSample sample = {
        .sequence = sequence,
        .accel_mg = { (int16_t)sequence, 0, 1000 },
        .gyro_mdps = { 0, 0, 0 },
        .sampled_at_tick = (TickType_t)sequence,
    };

    return sample;
}

int main(void)
{
    QueueHandle_t queue = xQueueCreate((UBaseType_t)1, sizeof(ImuSample));
    assert(queue != NULL);

    ImuQueueOverflow runtime;
    imu_queue_overflow_init(&runtime, queue, 1u);
    assert(runtime.sample_queue == queue);
    assert(runtime.drop_policy.dropped_sample_count == 0u);
    assert(runtime.drop_policy.fault_latched == false);

    ImuSample sample0 = make_sample(0u);
    ImuSample sample1 = make_sample(1u);

    assert(imu_queue_send_with_policy(&runtime, &sample0, (TickType_t)0) == IMU_DROP_POLICY_OK);
    assert(runtime.drop_policy.sent_sample_count == 1u);

    assert(imu_queue_send_with_policy(&runtime, &sample1, (TickType_t)0) == IMU_DROP_POLICY_FAULT);
    assert(runtime.drop_policy.dropped_sample_count == 1u);
    assert(runtime.drop_policy.fault_latched == true);

    assert(imu_queue_send_with_policy(NULL, &sample0, (TickType_t)0) == IMU_DROP_POLICY_FAULT);
    assert(imu_queue_send_with_policy(&runtime, NULL, (TickType_t)0) == IMU_DROP_POLICY_FAULT);

    vQueueDelete(queue);
    puts("PASS: lesson 0015 real FreeRTOS queue overflow exercise");
    return 0;
}
