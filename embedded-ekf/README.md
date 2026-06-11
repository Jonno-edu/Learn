# Embedded ESKF Course

This workspace is a step-by-step course for building a small standalone
error-state Kalman filter in C for rocket-style navigation.

The course rule is simple:

1. Learn one math concept.
2. Implement the matching C function or module.
3. Run focused tests.
4. Review before moving to the next concept.

## Current Slice

Lesson 1 sets the course contract, frame conventions, units, and dimension
constants.

Open the lesson index:

```sh
open lessons/index.html
```

Open the lesson in a browser:

```sh
open lessons/0001-course-contract-and-frames.html
```

Run the current tests:

```sh
make test
```

The first test is intentionally red. Fill in the placeholder constants in
`include/eskf/eskf_types.h`, then rerun `make test`.

Lessons 1-10 now exist as reading and implementation guides. Only Lesson 1 has
an active red test harness so the first exercise stays focused.

## Layout

```text
include/eskf/      Public headers for the ESKF library
lessons/           Self-contained HTML lessons
reference/         Printable reference notes and glossary
tests/             Plain-C test programs
COURSE.md          Course plan and locked design decisions
MISSION.md         Why this workspace exists
RESOURCES.md       Trusted sources for lessons
NOTES.md           Teaching preferences and working notes
```
