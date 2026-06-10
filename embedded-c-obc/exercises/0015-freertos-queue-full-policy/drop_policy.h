#ifndef DROP_POLICY_H
#define DROP_POLICY_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    IMU_DROP_POLICY_OK,
    IMU_DROP_POLICY_DROPPED,
    IMU_DROP_POLICY_FAULT
} ImuDropPolicyResult;

typedef struct
{
    uint32_t sent_sample_count;
    uint32_t dropped_sample_count;
    uint32_t drop_fault_threshold;
    bool fault_latched;
} ImuDropPolicy;

void imu_drop_policy_init(ImuDropPolicy *policy, uint32_t drop_fault_threshold);
ImuDropPolicyResult imu_drop_policy_record_send_ok(ImuDropPolicy *policy);
ImuDropPolicyResult imu_drop_policy_record_send_failed(ImuDropPolicy *policy);

#endif
