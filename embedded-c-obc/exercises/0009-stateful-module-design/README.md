# Exercise 0009: Stateful Module Design

Implement a small flight-phase tracker with caller-owned state.

The tracker does not own a loop. The caller calls `flight_phase_update(...)` once
per new sample and passes the same `FlightPhaseTracker` each time. That repeated
call pattern is what lets `samples_in_phase` and `descent_candidate_samples`
mean something.

The point is not perfect flight logic. The point is the API pattern:

- public context type in `flight_phase.h`
- `flight_phase_init(...)` initializes every field
- `flight_phase_update(...)` mutates only the provided context
- no hidden global state
- tests replay sample sequences through the public API

The test sequence is deliberately written as repeated calls:

```c
flight_phase_update(&tracker, &boost);
flight_phase_update(&tracker, &coast);
flight_phase_update(&tracker, &descending);
flight_phase_update(&tracker, &descending);
```

That is standing in for a later scheduler or FreeRTOS task loop.

## Transition contract

Use these rules for this exercise:

- `IDLE -> BOOST` when `motor_burning == true`.
- `BOOST -> COAST` when `motor_burning == false`.
- `COAST -> DESCENT` after **two consecutive** samples where
  `vertical_velocity_mps < -10`.
- `DESCENT -> LANDED` when `altitude_m <= 5` and
  `vertical_velocity_mps >= -1`.
- Any null input, null tracker, or invalid sensor sample should produce
  `FLIGHT_PHASE_FAULT`.
- When a phase changes, reset `samples_in_phase` to `0`.
- When a phase does not change, increment `samples_in_phase`.
- `descent_candidate_samples` counts only consecutive descent-like samples in
  `COAST`; reset it when the sample is not descent-like or the phase changes.

Run:

```sh
rtk make test
```

After it passes, answer:

> Which object owns the phase memory between calls?
