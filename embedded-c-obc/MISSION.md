# Mission: Embedded C For Rocket OBC Firmware

## Why
Build back enough C fluency to confidently write, review, and debug safety-conscious embedded firmware for a rocket onboard computer without leaning on AI for fundamentals. The target context is C firmware using FreeRTOS, sensors, drivers, communication protocols, and flight-critical state handling.

## Success looks like
- Explain and correctly use core C concepts such as storage duration, linkage, qualifiers, integer types, pointers, arrays, structs, undefined behavior, and the preprocessor.
- Write small hardware-facing C modules with explicit interfaces, deterministic behavior, and testable host-side seams.
- Reason about ISR/task boundaries, memory-mapped registers, concurrency hazards, FreeRTOS primitives, and protocol parsing without cargo-culting patterns.
- Review aerospace-style firmware for failure modes, lifetime bugs, race conditions, and maintainability risks.

## Constraints
- Start from fundamentals, but keep every lesson tied to OBC firmware.
- Prefer short exercises with immediate feedback over long lectures.
- Use local files in this workspace so progress can be revisited and tailored to the real codebase later.

## Out of scope
- Full flight-software certification processes.
- Deep C++ patterns unless they affect the C firmware boundary.
- Running or modifying the user's real OBC codebase until it is provided.
