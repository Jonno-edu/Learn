# Exercise 0001: Volatile Registers

Implement the two functions in `exercise.c`:

- `uart_rx_ready`: return whether bit 0 of `STATUS` is set.
- `uart_read_data`: return the low byte of `DATA`.

Run:

```sh
rtk make test
```

After it passes, answer this in your own words:

> Why are `STATUS` and `DATA` declared `volatile`?
