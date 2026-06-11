#include "drop_policy.h"

#include <stddef.h>

void imu_drop_policy_init(ImuDropPolicy *policy, uint32_t drop_fault_threshold)
{
    if (policy == NULL)
    {
        return;
    }

    policy->sent_sample_count = 0u;
    policy->dropped_sample_count = 0u;
    policy->drop_fault_threshold = drop_fault_threshold;
    policy->fault_latched = false;
}

ImuDropPolicyResult imu_drop_policy_record_send_ok(ImuDropPolicy *policy)
{
    if (policy == NULL)
    {
        return IMU_DROP_POLICY_FAULT;
    }

    policy->sent_sample_count += 1u;

    if (!policy->fault_latched)
    {
        return IMU_DROP_POLICY_OK;
    }

    return IMU_DROP_POLICY_FAULT;
}

ImuDropPolicyResult imu_drop_policy_record_send_failed(ImuDropPolicy *policy)
{
    if (policy == NULL)
    {
        return IMU_DROP_POLICY_FAULT;
    }

    policy->dropped_sample_count += 1u;

    if (policy->dropped_sample_count >= policy->drop_fault_threshold)
    {
        policy->fault_latched = true;
        return IMU_DROP_POLICY_FAULT;
    }

    return IMU_DROP_POLICY_DROPPED;
}
