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
    /* TODO: update sent_sample_count without clearing a latched fault. */
    (void)policy;
    return IMU_DROP_POLICY_FAULT;
}

ImuDropPolicyResult imu_drop_policy_record_send_failed(ImuDropPolicy *policy)
{
    /* TODO: count the drop and latch fault when the threshold is reached. */
    (void)policy;
    return IMU_DROP_POLICY_FAULT;
}
