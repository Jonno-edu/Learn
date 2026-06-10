#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

typedef struct
{
    uint32_t sequence;
    int16_t accel_mg[3];
} SmokeImuSample;

static QueueHandle_t sample_queue;

static void producer_task(void *argument)
{
    (void)argument;

    for (uint32_t i = 0u; i < 3u; i++)
    {
        SmokeImuSample sample = {
            .sequence = i,
            .accel_mg = { (int16_t)i, 0, 1000 },
        };

        assert(xQueueSend(sample_queue, &sample, pdMS_TO_TICKS(10u)) == pdPASS);
        vTaskDelay(pdMS_TO_TICKS(1u));
    }

    vTaskDelete(NULL);
}

static void consumer_task(void *argument)
{
    (void)argument;

    for (uint32_t expected = 0u; expected < 3u; expected++)
    {
        SmokeImuSample received = { 0 };
        assert(xQueueReceive(sample_queue, &received, portMAX_DELAY) == pdPASS);
        assert(received.sequence == expected);
    }

    puts("PASS: FreeRTOS POSIX queue smoke test");
    vTaskEndScheduler();
    vTaskDelete(NULL);
}

int main(void)
{
    sample_queue = xQueueCreate((UBaseType_t)2, sizeof(SmokeImuSample));
    assert(sample_queue != NULL);

    assert(xTaskCreate(producer_task, "imu_tx", configMINIMAL_STACK_SIZE, NULL, 2u, NULL) == pdPASS);
    assert(xTaskCreate(consumer_task, "flight_rx", configMINIMAL_STACK_SIZE, NULL, 2u, NULL) == pdPASS);

    vTaskStartScheduler();

    vQueueDelete(sample_queue);
    return 0;
}
