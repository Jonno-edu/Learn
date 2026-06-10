# Exercise 0010: Event-Driven State Machine

Implement a small flight state machine that transitions on named events.

The purpose is to separate:

- event detection: "launch detected", "apogee detected", "sensor fault"
- transition policy: "from coast, apogee means descent"

Run:

```sh
rtk make test
```

After it passes, answer:

> Which function owns the transition from coast to descent?
