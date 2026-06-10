#include "imu_health.h"

#include <stddef.h>

void imu_health_init(
    ImuHealth *health,
    uint32_t drop_fault_threshold,
    uint32_t empty_receive_fault_threshold)
{
    if (health == NULL)
    {
        return;
    }

    health->drop_fault_threshold = drop_fault_threshold;
    health->empty_receive_fault_threshold = empty_receive_fault_threshold;
    health->queued_sample_count = 0u;
    health->queue_drop_count = 0u;
    health->empty_receive_count = 0u;
    health->consecutive_empty_receive_count = 0u;
    health->last_sequence = 0u;
    health->last_sample_tick = 0u;
    health->has_sample = false;
    health->overload_fault_latched = false;
    health->freshness_fault_latched = false;
}

ImuHealthResult imu_health_record_queued_sample(
    ImuHealth *health,
    uint32_t sequence,
    uint32_t now_tick)
{
    /* TODO: record the sample, clear consecutive empty receives, and preserve latches. */
    (void)health;
    (void)sequence;
    (void)now_tick;
    return IMU_HEALTH_FAULT;
}

ImuHealthResult imu_health_record_queue_drop(ImuHealth *health)
{
    /* TODO: count drops and latch overload at the configured threshold. */
    (void)health;
    return IMU_HEALTH_FAULT;
}

ImuHealthResult imu_health_record_empty_receive(ImuHealth *health)
{
    /* TODO: count empty receives and latch freshness at the configured threshold. */
    (void)health;
    return IMU_HEALTH_FAULT;
}
