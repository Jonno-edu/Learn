# Exercise 0016: FreeRTOS ISR Queue Handoff

Implement a real FreeRTOS `FromISR` queue adapter for IMU samples.

This is deliberately focused on the interrupt boundary:

- the ISR hands a compact sample to a queue,
- the ISR records only simple send/drop counters,
- the flight task receives and owns the longer decision logic.

Complete:

- `isr_queue_handoff.c`
- review `imu_dma_isr.c` after the adapter compiles

Rules:

- Validate every pointer before the first `->` or `*pointer` use.
- Set `*out_higher_priority_task_woken = pdFALSE` before calling the queue API.
- Use `xQueueSendFromISR(handoff->sample_queue, sample, out_higher_priority_task_woken)`.
- Increment `isr_send_count` only when the send returns `pdPASS`.
- Increment `isr_drop_count` when the send does not return `pdPASS`.
- Do not call normal blocking queue APIs from ISR-facing code.

Syntax-check the RTOS-facing files:

```sh
rtk make freertos-syntax
```

Run the real FreeRTOS queue test after implementing the TODO:

```sh
rtk make freertos-test
```

After it passes, answer:

> Why does the ISR pass `&higher_priority_task_woken` to FreeRTOS and then call `portYIELD_FROM_ISR`?
