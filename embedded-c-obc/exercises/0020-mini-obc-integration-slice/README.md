# Exercise 0020: Mini OBC Integration Slice

Build the first plain C piece of a small IMU-to-flight-task integration slice.

This exercise starts red on purpose. Do not wire FreeRTOS first. Make the health module pass its host tests first.

Complete:

- `imu_health.c`

Read first:

- `integration_design.md`
- `imu_health.h`
- `test_imu_health.c`

Run:

```sh
rtk make test
```

Rules:

- Check pointer arguments before dereferencing.
- Initialize every public field.
- Record successful samples with sequence and tick.
- Count queue drops separately from empty receives.
- Latch overload and freshness faults at their thresholds.
- Later success should clear consecutive empty receives, but must not silently clear latched faults.

After it passes, answer:

> Which requirement did each test prove, and where would the FreeRTOS queue adapter call this module?
