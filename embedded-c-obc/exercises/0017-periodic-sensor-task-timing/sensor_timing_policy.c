#include "sensor_timing_policy.h"

#include <stddef.h>

uint32_t sensor_period_ms_to_ticks(uint32_t period_ms, uint32_t tick_rate_hz)
{
    /* TODO: convert milliseconds to ticks and round nonzero periods up. */
    (void)period_ms;
    (void)tick_rate_hz;
    return 0u;
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
    /* TODO: record sends/misses and latch freshness faults after the threshold. */
    (void)policy;
    (void)sent;
    return SENSOR_TIMING_FAULT;
}
