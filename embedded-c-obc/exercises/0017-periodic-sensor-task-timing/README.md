# Exercise 0017: Periodic Sensor Task Timing

Implement the plain C timing policy for a fixed-rate IMU producer, then inspect the FreeRTOS task wrapper.

Complete:

- `sensor_timing_policy.c`
- review `imu_periodic_task.c`

Rules:

- `sensor_period_ms_to_ticks` returns zero only when the input period or tick rate is zero.
- For nonzero millisecond periods, round up so a small nonzero period does not become zero ticks.
- A successful send increments `total_sent_sample_count` and resets `consecutive_missed_send_count`.
- A failed send increments `total_missed_send_count` and `consecutive_missed_send_count`.
- The freshness fault latch becomes true once consecutive misses reach the configured threshold.
- A later success clears the consecutive miss counter but does not clear a latched fault.

Run the plain-C test:

```sh
rtk make test
```

Syntax-check the FreeRTOS task skeleton:

```sh
rtk make freertos-syntax
```

After it passes, answer:

> Which file owns the infinite loop, and which file owns the health counters?
