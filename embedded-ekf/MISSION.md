# Mission: Embedded ESKF In C

## Why

Build the skill to implement and reason about a small error-state Kalman filter
core for rocket-style navigation firmware, without hiding the estimator behind a
large OBC codebase or a generic math library.

## Success looks like

- Define the estimator frames, states, units, and dimensions without ambiguity.
- Build a tested standalone C99 ESKF library one function at a time.
- Run a small caller that feeds synthetic IMU and GPS position/velocity samples.
- Explain what each prediction, update, covariance, and error-injection step is doing.

## Constraints

- Use a conservative aerospace-style C99 subset.
- Keep memory static: no heap, no hidden global estimator state, no VLAs.
- Prefer fixed-size helper functions over a generic matrix framework.
- The user should implement a fair amount of the narrow lesson targets.
- Numerically fragile sections may receive a reference implementation after the equations and tests are locked.

## Out of scope

- OBC integration, RTOS tasks, and flight-software architecture.
- Barometer, magnetometer, drag model, aero model, launch rail constraint, and geodesy.
- Formal MISRA compliance or flight certification claims.

