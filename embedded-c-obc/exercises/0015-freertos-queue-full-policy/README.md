# Exercise 0015: FreeRTOS Queue Full Policy

Implement a visible overflow policy for a small IMU sample queue.

Part 1 is plain C and locally testable. Part 2 is the real FreeRTOS adapter.
This keeps the health policy reviewable while still forcing real API usage.

Complete:

- `drop_policy.c`
- `imu_queue_overflow.c`

Run the plain-C policy test:

```sh
rtk make test
```

Syntax-check the RTOS adapter:

```sh
rtk make freertos-syntax
```

Run the real FreeRTOS overflow adapter test after implementing the TODOs:

```sh
rtk make freertos-test
```

Rules:

- A successful send increments `sent_sample_count`.
- A failed send increments `dropped_sample_count`.
- The fault latch becomes true once drops reach `drop_fault_threshold`.
- A later success must not clear a latched fault.
- Invalid pointers or missing queue handles return `IMU_DROP_POLICY_FAULT`.
- The adapter must call `xQueueSend(runtime->sample_queue, sample, wait_ticks)`.

After it passes, answer:

> Why is a zero tick send timeout often better than `portMAX_DELAY` for a fixed-rate sensor producer?
