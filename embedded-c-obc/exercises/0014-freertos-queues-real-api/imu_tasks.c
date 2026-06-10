#include "imu_queue_app.h"

#include "task.h"

#define IMU_SAMPLE_PERIOD_MS 10u

static ImuSample read_imu_sample(uint32_t *sequence)
{
    ImuSample sample = {
        .sequence = *sequence,
        .accel_mg = { 0, 0, 1000 },
        .gyro_mdps = { 0, 0, 0 },
        .sampled_at_tick = xTaskGetTickCount(),
    };

    *sequence += 1u;
    return sample;
}

static void process_imu_sample(const ImuSample *sample)
{
    (void)sample;
}

void imu_sensor_task(void *argument)
{
    ImuQueueApp *app = (ImuQueueApp *)argument;
    uint32_t sequence = 0u;
    const TickType_t period_ticks = pdMS_TO_TICKS(IMU_SAMPLE_PERIOD_MS);

    for (;;)
    {
        ImuSample sample = read_imu_sample(&sequence);
        (void)imu_sensor_send_sample(app, &sample);
        vTaskDelay(period_ticks);
    }
}

void imu_flight_task(void *argument)
{
    ImuQueueApp *app = (ImuQueueApp *)argument;

    for (;;)
    {
        ImuSample received;

        if (imu_flight_receive_sample(app, &received) == pdPASS)
        {
            process_imu_sample(&received);
        }
    }
}
