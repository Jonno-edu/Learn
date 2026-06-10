#ifndef SENSOR_TIMING_POLICY_H
#define SENSOR_TIMING_POLICY_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    SENSOR_TIMING_OK,
    SENSOR_TIMING_MISSED_SEND,
    SENSOR_TIMING_FAULT
} SensorTimingResult;

typedef struct
{
    uint32_t period_ticks;
    uint32_t missed_send_fault_threshold;
    uint32_t total_sent_sample_count;
    uint32_t total_missed_send_count;
    uint32_t consecutive_missed_send_count;
    bool freshness_fault_latched;
} SensorTimingPolicy;

uint32_t sensor_period_ms_to_ticks(uint32_t period_ms, uint32_t tick_rate_hz);
void sensor_timing_policy_init(
    SensorTimingPolicy *policy,
    uint32_t period_ticks,
    uint32_t missed_send_fault_threshold);
SensorTimingResult sensor_timing_policy_record_send(SensorTimingPolicy *policy, bool sent);

#endif
