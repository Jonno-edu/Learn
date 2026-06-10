# Local FreeRTOS On macOS

This directory configures a small FreeRTOS POSIX simulator layer for the
embedded-C OBC lessons.

The local kernel checkout lives at:

```sh
embedded-c-obc/vendor/FreeRTOS-Kernel
```

It is intentionally ignored by git. The repository tracks the teaching config
and Makefile shim, not the upstream kernel source.

## First Setup

```sh
rtk sh embedded-c-obc/scripts/setup_freertos_macos.sh
```

That clones the official FreeRTOS kernel into `embedded-c-obc/vendor/`.

## Check The Simulator

```sh
rtk make -C embedded-c-obc/freertos smoke
```

This starts the real FreeRTOS POSIX scheduler, runs a producer task and a
consumer task, passes IMU-shaped samples through a real FreeRTOS queue, and then
ends the scheduler.

## Lesson Commands

For lesson 0014:

```sh
rtk make -C embedded-c-obc/exercises/0014-freertos-queues-real-api freertos-syntax
rtk make -C embedded-c-obc/exercises/0014-freertos-queues-real-api freertos-test
```

For lesson 0015:

```sh
rtk make -C embedded-c-obc/exercises/0015-freertos-queue-full-policy test
rtk make -C embedded-c-obc/exercises/0015-freertos-queue-full-policy freertos-syntax
rtk make -C embedded-c-obc/exercises/0015-freertos-queue-full-policy freertos-test
```

For lesson 0016:

```sh
rtk make -C embedded-c-obc/exercises/0016-freertos-isr-queue-handoff freertos-syntax
rtk make -C embedded-c-obc/exercises/0016-freertos-isr-queue-handoff freertos-test
```

For lesson 0017:

```sh
rtk make -C embedded-c-obc/exercises/0017-periodic-sensor-task-timing test
rtk make -C embedded-c-obc/exercises/0017-periodic-sensor-task-timing freertos-syntax
```

The `freertos-test` targets are expected to fail until the lesson TODOs are
implemented.

## macOS Debugger Note

The FreeRTOS POSIX port uses pthreads and signals. The upstream `port.c` notes
that LLDB can interfere with `SIGUSR1`; if debugging these examples in LLDB,
add this to `~/.lldbinit`:

```text
process handle SIGUSR1 -n true -p false -s false
```

## Sources

- FreeRTOS queue API reference: https://www.freertos.org/Documentation/02-Kernel/04-API-references/06-Queues/00-Queues
- FreeRTOS queue feature guide: https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues-mutexes-and-semaphores/01-Queues
- FreeRTOS-Kernel POSIX port: https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/main/portable/ThirdParty/GCC/Posix
