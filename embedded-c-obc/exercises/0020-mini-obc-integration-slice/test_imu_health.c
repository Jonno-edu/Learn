#include "imu_health.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    ImuHealth health;
    imu_health_init(&health, 2u, 3u);

    assert(health.drop_fault_threshold == 2u);
    assert(health.empty_receive_fault_threshold == 3u);
    assert(health.queued_sample_count == 0u);
    assert(health.queue_drop_count == 0u);
    assert(health.empty_receive_count == 0u);
    assert(health.consecutive_empty_receive_count == 0u);
    assert(health.has_sample == false);
    assert(health.overload_fault_latched == false);
    assert(health.freshness_fault_latched == false);

    assert(imu_health_record_queued_sample(&health, 10u, 100u) == IMU_HEALTH_OK);
    assert(health.queued_sample_count == 1u);
    assert(health.last_sequence == 10u);
    assert(health.last_sample_tick == 100u);
    assert(health.has_sample == true);
    assert(health.consecutive_empty_receive_count == 0u);

    assert(imu_health_record_empty_receive(&health) == IMU_HEALTH_EMPTY_RECORDED);
    assert(health.empty_receive_count == 1u);
    assert(health.consecutive_empty_receive_count == 1u);
    assert(health.freshness_fault_latched == false);

    assert(imu_health_record_queued_sample(&health, 11u, 110u) == IMU_HEALTH_OK);
    assert(health.queued_sample_count == 2u);
    assert(health.last_sequence == 11u);
    assert(health.consecutive_empty_receive_count == 0u);

    assert(imu_health_record_queue_drop(&health) == IMU_HEALTH_DROP_RECORDED);
    assert(health.queue_drop_count == 1u);
    assert(health.overload_fault_latched == false);

    assert(imu_health_record_queue_drop(&health) == IMU_HEALTH_FAULT);
    assert(health.queue_drop_count == 2u);
    assert(health.overload_fault_latched == true);

    assert(imu_health_record_empty_receive(&health) == IMU_HEALTH_EMPTY_RECORDED);
    assert(imu_health_record_empty_receive(&health) == IMU_HEALTH_EMPTY_RECORDED);
    assert(imu_health_record_empty_receive(&health) == IMU_HEALTH_FAULT);
    assert(health.empty_receive_count == 4u);
    assert(health.consecutive_empty_receive_count == 3u);
    assert(health.freshness_fault_latched == true);

    assert(imu_health_record_queued_sample(&health, 12u, 120u) == IMU_HEALTH_FAULT);
    assert(health.consecutive_empty_receive_count == 0u);
    assert(health.overload_fault_latched == true);
    assert(health.freshness_fault_latched == true);

    assert(imu_health_record_queued_sample(NULL, 1u, 1u) == IMU_HEALTH_FAULT);
    assert(imu_health_record_queue_drop(NULL) == IMU_HEALTH_FAULT);
    assert(imu_health_record_empty_receive(NULL) == IMU_HEALTH_FAULT);

    puts("PASS: mini OBC integration slice health module");
    return 0;
}
