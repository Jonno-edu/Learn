# Exercise 0011: ISR To Task Event Handoff

Implement a one-slot event bridge between an ISR-like producer and a task-like
consumer.

This exercise intentionally does not include FreeRTOS headers. The point is to
practice the ownership shape before memorizing kernel APIs:

- ISR side posts a small `FlightEvent`
- task side takes the pending event
- task side would be the only place that dispatches the flight FSM
- overflow is counted instead of hidden

Run:

```sh
rtk make test
```

After it passes, answer:

> Which side is allowed to dispatch the flight FSM: ISR side or task side?
