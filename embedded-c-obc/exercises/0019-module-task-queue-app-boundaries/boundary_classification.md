# Boundary Classification Worksheet

For each feature, write the likely boundaries.

Use this format:

```text
Feature:
Plain C module:
Task:
Queue / notification:
App / component:
Why:
```

## 1. IMU Freshness Monitoring

The system must know whether IMU samples are still arriving and latch a fault after repeated missed deliveries.

## 2. Recovery Arming

Recovery logic may arm only after a valid flight phase and disarm command state make recovery safe.

## 3. Telemetry Packing

Typed values must be converted into a fixed byte frame before downlink.

## 4. Sensor Producer

The IMU hardware should be read every 10 ms and each sample offered to flight logic.

## 5. Command Routing

Ground commands arrive, are decoded, and must be routed to the owning subsystem.

## 6. Watchdog Supervision

The system must prove that important tasks still make progress and trigger a fault if they stop checking in.

## 7. App Deployment

The mission needs a unit that is commanded, emits telemetry/events, and is wired into the larger flight-software framework.

## 8. UART Receive Path

A UART interrupt receives bytes, a parser validates frames, and a command task handles complete commands.
