# Exercise 0003: Real Sensor Registers

This exercise models a small BMP280-style pressure-sensor driver slice:

- read status bits from one register byte
- combine three data bytes into one 20-bit raw pressure sample

Implement the stubs in `exercise.c`.

Rules:

- Use named masks and shifts.
- Do not compare the whole status register to one bit value.
- Cast bytes to `uint32_t` before shifting into the wider result.

Run:

```sh
rtk make test
```

After it passes, answer:

> Why does `press_xlsb` shift right while `press_msb` and `press_lsb` shift left?
