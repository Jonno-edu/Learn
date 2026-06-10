#include "isr_queue_handoff.h"

#include <assert.h>
#include <stdio.h>

static ImuSample make_sample(uint32_t sequence)
{
    ImuSample sample = {
        .sequence = sequence,
        .accel_mg = { 10, -20, 30 },
        .gyro_mdps = { 100, 200, -300 },
        .sampled_at_tick = (TickType_t)sequence
    };

    return sample;
}

int main(void)
{
    QueueHandle_t queue = isr_queue_create();
    assert(queue != NULL);

    IsrQueueHandoff handoff;
    isr_queue_handoff_init(&handoff, queue);
    assert(handoff.sample_queue == queue);
    assert(handoff.isr_send_count == 0u);
    assert(handoff.isr_drop_count == 0u);

    ImuSample sample = make_sample(7u);
    BaseType_t higher_priority_task_woken = pdTRUE;
    assert(imu_sample_ready_from_isr(&handoff, &sample, &higher_priority_task_woken) == pdPASS);
    assert(handoff.isr_send_count == 1u);
    assert(handoff.isr_drop_count == 0u);

    ImuSample received = make_sample(0u);
    assert(xQueueReceive(queue, &received, (TickType_t)0) == pdPASS);
    assert(received.sequence == 7u);
    assert(received.accel_mg[1] == -20);

    for (uint32_t i = 0u; i < 3u; i++)
    {
        ImuSample queued = make_sample(100u + i);
        assert(xQueueSend(queue, &queued, (TickType_t)0) == pdPASS);
    }

    ImuSample dropped = make_sample(200u);
    assert(imu_sample_ready_from_isr(&handoff, &dropped, &higher_priority_task_woken) != pdPASS);
    assert(handoff.isr_send_count == 1u);
    assert(handoff.isr_drop_count == 1u);

    assert(imu_sample_ready_from_isr(NULL, &dropped, &higher_priority_task_woken) == pdFAIL);
    assert(imu_sample_ready_from_isr(&handoff, NULL, &higher_priority_task_woken) == pdFAIL);
    assert(imu_sample_ready_from_isr(&handoff, &dropped, NULL) == pdFAIL);

    vQueueDelete(queue);

    puts("PASS: FreeRTOS ISR queue handoff exercise");
    return 0;
}
