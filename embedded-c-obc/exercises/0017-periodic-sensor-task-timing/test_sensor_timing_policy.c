#include "sensor_timing_policy.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    assert(sensor_period_ms_to_ticks(10u, 1000u) == 10u);
    assert(sensor_period_ms_to_ticks(1u, 100u) == 1u);
    assert(sensor_period_ms_to_ticks(3u, 1000u) == 3u);
    assert(sensor_period_ms_to_ticks(0u, 1000u) == 0u);
    assert(sensor_period_ms_to_ticks(10u, 0u) == 0u);

    SensorTimingPolicy policy;
    sensor_timing_policy_init(&policy, 10u, 3u);
    assert(policy.period_ticks == 10u);
    assert(policy.missed_send_fault_threshold == 3u);
    assert(policy.freshness_fault_latched == false);

    assert(sensor_timing_policy_record_send(&policy, true) == SENSOR_TIMING_OK);
    assert(policy.total_sent_sample_count == 1u);
    assert(policy.consecutive_missed_send_count == 0u);

    assert(sensor_timing_policy_record_send(&policy, false) == SENSOR_TIMING_MISSED_SEND);
    assert(policy.total_missed_send_count == 1u);
    assert(policy.consecutive_missed_send_count == 1u);
    assert(policy.freshness_fault_latched == false);

    assert(sensor_timing_policy_record_send(&policy, false) == SENSOR_TIMING_MISSED_SEND);
    assert(policy.consecutive_missed_send_count == 2u);
    assert(policy.freshness_fault_latched == false);

    assert(sensor_timing_policy_record_send(&policy, false) == SENSOR_TIMING_FAULT);
    assert(policy.consecutive_missed_send_count == 3u);
    assert(policy.freshness_fault_latched == true);

    assert(sensor_timing_policy_record_send(&policy, true) == SENSOR_TIMING_FAULT);
    assert(policy.total_sent_sample_count == 2u);
    assert(policy.consecutive_missed_send_count == 0u);
    assert(policy.freshness_fault_latched == true);

    assert(sensor_timing_policy_record_send(NULL, true) == SENSOR_TIMING_FAULT);

    puts("PASS: periodic sensor timing policy exercise");
    return 0;
}
