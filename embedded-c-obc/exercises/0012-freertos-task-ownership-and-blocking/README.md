# Exercise 0012: FreeRTOS Task Ownership And Blocking

Implement a host-side model of one flight-task step.

There are no FreeRTOS headers in this exercise. The point is to practice the
task ownership shape:

- one task context owns counters and timeout policy
- the task step consumes one pending event when work exists
- the task step records an idle timeout when no work exists
- the caller can dispatch the returned event through the FSM

Run:

```sh
rtk make test
```

After it passes, answer:

> Why is returning `FLIGHT_TASK_TIMEOUT` better than silently doing nothing?
