# Exercise 0004: Signed Sensor Values

This exercise models a signed 16-bit accelerometer output split across two bytes.

Implement the stubs in `exercise.c`.

Rules:

- Combine bytes into a `uint16_t` raw pattern first.
- Convert the complete raw pattern to `int16_t`.
- Use `int32_t` arithmetic when scaling counts to milli-g.

Run:

```sh
rtk make test
```

After it passes, answer:

> Why is `0xff38` interpreted as `-200` when viewed as `int16_t`?
