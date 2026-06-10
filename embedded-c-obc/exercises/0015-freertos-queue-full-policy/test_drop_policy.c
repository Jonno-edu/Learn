#include "drop_policy.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    ImuDropPolicy policy;

    imu_drop_policy_init(&policy, 2u);
    assert(policy.sent_sample_count == 0u);
    assert(policy.dropped_sample_count == 0u);
    assert(policy.drop_fault_threshold == 2u);
    assert(policy.fault_latched == false);

    assert(imu_drop_policy_record_send_ok(&policy) == IMU_DROP_POLICY_OK);
    assert(policy.sent_sample_count == 1u);
    assert(policy.dropped_sample_count == 0u);
    assert(policy.fault_latched == false);

    assert(imu_drop_policy_record_send_failed(&policy) == IMU_DROP_POLICY_DROPPED);
    assert(policy.sent_sample_count == 1u);
    assert(policy.dropped_sample_count == 1u);
    assert(policy.fault_latched == false);

    assert(imu_drop_policy_record_send_failed(&policy) == IMU_DROP_POLICY_FAULT);
    assert(policy.dropped_sample_count == 2u);
    assert(policy.fault_latched == true);

    assert(imu_drop_policy_record_send_ok(&policy) == IMU_DROP_POLICY_FAULT);
    assert(policy.sent_sample_count == 2u);
    assert(policy.fault_latched == true);

    assert(imu_drop_policy_record_send_ok(NULL) == IMU_DROP_POLICY_FAULT);
    assert(imu_drop_policy_record_send_failed(NULL) == IMU_DROP_POLICY_FAULT);

    puts("PASS: FreeRTOS queue full policy exercise");
    return 0;
}
