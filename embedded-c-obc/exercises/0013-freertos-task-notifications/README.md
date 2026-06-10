# Exercise 0013: FreeRTOS Task Notifications

Implement a host-side model of task notification bits.

There are no FreeRTOS headers in this exercise. The point is to practice the
notification-bit mental model before using the real API:

- posting bits ORs them into the pending notification value
- waiting copies pending bits to the task side
- consumed bits are cleared
- repeated identical bits coalesce into one set bit
- notification bits can be translated into flight events

Run:

```sh
rtk make test
```

After it passes, answer:

> Why would a queue be better than notification bits for repeated telemetry samples?
