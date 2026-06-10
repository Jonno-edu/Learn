# Exercise 0008: Module API Design

Design and implement a small recovery gate module.

The purpose is not to build the full flight state machine yet. The purpose is to practice a clean module boundary:

- public caller-visible types in `recovery_gate.h`
- private helpers in `recovery_gate.c`
- tests that drive behavior through the public API
- no dynamic allocation
- no hidden global state

Run:

```sh
rtk make test
```

After it passes, answer:

> Which parts of this module are public contract, and which parts are private implementation?
