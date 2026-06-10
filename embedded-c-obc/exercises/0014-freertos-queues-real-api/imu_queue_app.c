#include "imu_queue_app.h"

#include <stddef.h>

#define IMU_SAMPLE_QUEUE_DEPTH ((UBaseType_t)3)

QueueHandle_t imu_queue_create(void)
{    
    return xQueueCreate(IMU_SAMPLE_QUEUE_DEPTH, sizeof(ImuSample));
}

void imu_queue_app_init(ImuQueueApp *app, QueueHandle_t sample_queue)
{
    if (app == NULL)
    {
        return;
    }

    app->sample_queue = sample_queue;
    app->sent_sample_count = 0u;
    app->received_sample_count = 0u;
    app->dropped_sample_count = 0u;
    
}

BaseType_t imu_sensor_send_sample(ImuQueueApp *app, const ImuSample *sample)
{
    if ((app == NULL) || (sample == NULL) || (app->sample_queue == NULL))
    {
        return pdFAIL;
    }

    BaseType_t sent = xQueueSend(app->sample_queue, sample, (TickType_t)0);

    if (sent == pdPASS)
    {
        app->sent_sample_count += 1u;
    }
    else
    {
        app->dropped_sample_count += 1u;
    }
    return sent;
}

BaseType_t imu_flight_receive_sample(ImuQueueApp *app, ImuSample *out_sample)
{
    if ((app == NULL) || (out_sample == NULL) || (app->sample_queue == NULL))
    {
        return pdFAIL;
    }

    BaseType_t received = xQueueReceive(app->sample_queue, out_sample, portMAX_DELAY);

    if (received == pdPASS)
    {
        app->received_sample_count += 1u;
    }

    return received;
}
