# Mini OBC Integration Slice Design

## Problem

The flight task needs a health-visible view of IMU delivery: samples received, queue drops, empty receives, last sequence, and last sample tick.

## Boundaries

- Plain C module: `imu_health`
  - Owns counters, thresholds, and fault latches.
  - Has no FreeRTOS includes.
  - Is tested on the host.
- FreeRTOS queue adapter:
  - Owns `xQueueSend`, `xQueueReceive`, timeouts, and task wake behavior.
  - Calls `imu_health_record_queued_sample`, `imu_health_record_queue_drop`, or `imu_health_record_empty_receive` based on API results.
- Sensor task:
  - Owns fixed-rate sampling.
  - Does not own health policy internals.
- Flight task:
  - Receives samples and calls the plain C module.

## Requirements

- REQ-001: Initialize explicit thresholds and zeroed counters.
- REQ-002: Record queued samples with latest sequence and tick.
- REQ-003: Record queue drops and latch overload fault at the threshold.
- REQ-004: Record empty receives and latch freshness fault at the threshold.
- REQ-005: Invalid pointer inputs return `IMU_HEALTH_FAULT`.

## Adapter Sketch

```c
if (xQueueReceive(queue, &sample, wait_ticks) == pdPASS)
{
    (void)imu_health_record_queued_sample(&health, sample.sequence, now_tick);
}
else
{
    (void)imu_health_record_empty_receive(&health);
}
```

For a producer-side queue send failure:

```c
if (xQueueSend(queue, &sample, (TickType_t)0) != pdPASS)
{
    (void)imu_health_record_queue_drop(&health);
}
```

## Review Checklist

- Public header exposes the contract and state shape.
- Source file owns private policy details.
- Tests use public functions only.
- No task loops, delays, queues, or globals are hidden inside the plain C module.
