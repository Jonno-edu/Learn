# FreeRTOS task notifications

The user completed the host-side task notification exercise and practiced the notification-bit model: producers OR bits into a pending notification value, the task side waits and copies pending bits out, consumed bits are cleared, and notification bits are translated into flight events before FSM dispatch.

Key friction points from the lesson:

- The user initially needed the real RTOS flow made explicit: hardware or another task sets a notification bit, the flight task wakes from blocked state, reads the bits, translates them into `FlightEvent` values, then dispatches the FSM.
- Output-pointer handling came up again with `uint32_t *out_bits`. The important pattern is `*out_bits = notification->pending_bits`, not assigning to `out_bits` itself.
- A segfault came from dereferencing `notification` before checking for `NULL` in `task_notification_post_bits`. Future lessons should keep drilling: validate every pointer before the first `->` or `*pointer` use.
- The user correctly implemented bit-mask checks in priority order using `(bits & FLIGHT_NOTIFY_...) != 0u`, and learned why equality checks are wrong when multiple notification bits can be set at once.
- The queue-versus-notification distinction is emerging: notification bits are good for compact coalescing wakeups; queues are better when every event or sample must be preserved in order.

Future lessons can build from this into real FreeRTOS API names, especially `xTaskNotify...`, `xTaskNotifyFromISR...`, and then queues for non-coalescing event streams.
