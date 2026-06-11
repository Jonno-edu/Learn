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
    if (health == NULL)
    {
        return IMU_HEALTH_FAULT;
    }
    health->queued_sample_count += 1u;
    health->last_sample_tick = now_tick;
    health->last_sequence = sequence;
    health->has_sample = true;
    health->consecutive_empty_receive_count = 0u;

    if (health->overload_fault_latched || health->freshness_fault_latched)
    {
        return IMU_HEALTH_FAULT;
    }

    return IMU_HEALTH_OK;
}

ImuHealthResult imu_health_record_queue_drop(ImuHealth *health)
{
    if (health == NULL)
    {
        return IMU_HEALTH_FAULT;
    }

    health->queue_drop_count += 1u;

    if (health->queue_drop_count >= health->drop_fault_threshold)
    {
        health->overload_fault_latched = true;
        return IMU_HEALTH_FAULT;
    }


    return IMU_HEALTH_DROP_RECORDED;
}

ImuHealthResult imu_health_record_empty_receive(ImuHealth *health)
{
    if (health == NULL)
    {
        return IMU_HEALTH_FAULT;
    }
    
    health->empty_receive_count += 1;
    health->consecutive_empty_receive_count += 1;

    if (health->consecutive_empty_receive_count >= health->empty_receive_fault_threshold)
    {
        health->freshness_fault_latched = true;
        return IMU_HEALTH_FAULT;
    }

    return IMU_HEALTH_EMPTY_RECORDED;

}
