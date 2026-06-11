#include "sensor_timing_policy.h"

#include <stddef.h>

uint32_t sensor_period_ms_to_ticks(uint32_t period_ms, uint32_t tick_rate_hz)
{
    uint64_t ticks = ((uint64_t) period_ms  * tick_rate_hz + 999u) / 1000u;
    return (uint32_t) ticks;
}

void sensor_timing_policy_init(
    SensorTimingPolicy *policy,
    uint32_t period_ticks,
    uint32_t missed_send_fault_threshold)
{
    if (policy == NULL)
    {
        return;
    }

    policy->period_ticks = period_ticks;
    policy->missed_send_fault_threshold = missed_send_fault_threshold;
    policy->total_sent_sample_count = 0u;
    policy->total_missed_send_count = 0u;
    policy->consecutive_missed_send_count = 0u;
    policy->freshness_fault_latched = false;
}

SensorTimingResult sensor_timing_policy_record_send(SensorTimingPolicy *policy, bool sent)
{
    if (policy == NULL)
    {
        return SENSOR_TIMING_FAULT;
    }

    if (sent)
    {
        policy->total_sent_sample_count += 1u;
        policy->consecutive_missed_send_count = 0u;
    }else
    {
        policy->consecutive_missed_send_count += 1u;
        policy->total_missed_send_count += 1u;

        if (policy->consecutive_missed_send_count >= policy->missed_send_fault_threshold)
        {
            policy->freshness_fault_latched = true;
        }
    }

    if (policy->freshness_fault_latched)
    {
        return SENSOR_TIMING_FAULT;
    }
    if (!sent)
    {
        return SENSOR_TIMING_MISSED_SEND;
    }

    return SENSOR_TIMING_OK;
}
