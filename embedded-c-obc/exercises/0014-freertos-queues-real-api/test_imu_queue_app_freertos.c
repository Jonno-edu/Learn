#include "imu_queue_app.h"

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
    QueueHandle_t queue = imu_queue_create();
    assert(queue != NULL);

    ImuQueueApp app;
    imu_queue_app_init(&app, queue);
    assert(app.sample_queue == queue);
    assert(app.sent_sample_count == 0u);
    assert(app.received_sample_count == 0u);
    assert(app.dropped_sample_count == 0u);

    ImuSample sample0 = make_sample(0u);
    ImuSample sample1 = make_sample(1u);
    ImuSample sample2 = make_sample(2u);
    ImuSample sample3 = make_sample(3u);

    assert(imu_sensor_send_sample(&app, &sample0) == pdPASS);
    assert(imu_sensor_send_sample(&app, &sample1) == pdPASS);
    assert(imu_sensor_send_sample(&app, &sample2) == pdPASS);
    assert(app.sent_sample_count == 3u);

    assert(imu_sensor_send_sample(&app, &sample3) == pdFAIL);
    assert(app.dropped_sample_count == 1u);

    for (uint32_t expected = 0u; expected < 3u; expected++)
    {
        ImuSample received = { 0 };
        assert(imu_flight_receive_sample(&app, &received) == pdPASS);
        assert(received.sequence == expected);
    }

    assert(app.received_sample_count == 3u);
    assert(imu_sensor_send_sample(NULL, &sample0) == pdFAIL);
    assert(imu_sensor_send_sample(&app, NULL) == pdFAIL);
    assert(imu_flight_receive_sample(NULL, &sample0) == pdFAIL);
    assert(imu_flight_receive_sample(&app, NULL) == pdFAIL);

    vQueueDelete(queue);
    puts("PASS: lesson 0014 real FreeRTOS queue exercise");
    return 0;
}
