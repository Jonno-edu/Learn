# Exercise 0014: FreeRTOS Queues Real API

Implement a real FreeRTOS queue boundary for IMU samples.

This exercise is deliberately not a host-side fake. The files include real
FreeRTOS headers and use real API names. The local repository does not vendor a
FreeRTOS kernel, so syntax checking requires a kernel/port checkout.

Complete:

- `imu_queue_create`
- `imu_queue_app_init`
- `imu_sensor_send_sample`
- `imu_flight_receive_sample`

Rules:

- Use `xQueueCreate((UBaseType_t)3, sizeof(ImuSample))`.
- Use `xQueueSend(app->sample_queue, sample, (TickType_t)0)` from task context.
- Use `xQueueReceive(app->sample_queue, out_sample, portMAX_DELAY)` in the flight task path.
- Update counters only after checking for `pdPASS`.
- Treat invalid pointers or missing queue handles as `pdFAIL`.

Syntax-check the RTOS-facing files:

```sh
rtk make freertos-syntax
```

Run the real FreeRTOS queue test after implementing the TODOs:

```sh
rtk make test
```

Equivalent explicit target:

```sh
rtk make freertos-test
```

After implementing it, answer:

> What exactly do `&sample` and `&received` point at in the send and receive calls?
