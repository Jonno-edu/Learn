#include "isr_queue_handoff.h"

#include <stddef.h>

static IsrQueueHandoff *g_imu_isr_handoff;

extern ImuSample imu_dma_read_sample(void);

void imu_dma_isr_bind_handoff(IsrQueueHandoff *handoff)
{
    g_imu_isr_handoff = handoff;
}

void IMU_DMA_IRQHandler(void)
{
    if (g_imu_isr_handoff == NULL)
    {
        return;
    }

    ImuSample sample = imu_dma_read_sample();
    BaseType_t higher_priority_task_woken = pdFALSE;

    (void)imu_sample_ready_from_isr(
        g_imu_isr_handoff,
        &sample,
        &higher_priority_task_woken);

    portYIELD_FROM_ISR(higher_priority_task_woken);
}
