# FreeRTOS Toolbox Scenario Drill

For each scenario, write:

- Primitive:
- Reason:
- Failure mode / review question:

## 1. Barometer Data-Ready Pin

A GPIO interrupt says the barometer has fresh data. One sensor task should wake and read the device. Multiple interrupts before the task runs do not need to be counted individually.

## 2. IMU Sample Stream

The IMU producer task generates a sample every 10 ms. The flight task should process samples in order and missed samples must be visible.

## 3. Flight Event Flags

An estimator task wants to tell the flight task that one or more conditions are pending: boost detected, apogee detected, or sensor fault. Repeated identical flags may coalesce.

## 4. Shared Health Struct

Two tasks currently write fields in the same health struct.

## 5. Telemetry Downlink Frames

Several producers create telemetry frames that must be sent in order by one downlink task.

## 6. Fixed-Rate GPS Poll

A GPS task should poll a receiver every 200 ms without drifting later every time parsing takes a few milliseconds.

## 7. ISR Packet Byte Stream

A UART ISR receives bytes from a radio link. The parser runs in task context and must preserve byte order.

## 8. Command Acknowledgement

A command task needs to wait until a flash-write task reports done or failed for one specific command.

## 9. System Mode Bits

Several tasks need to observe independent mode bits such as armed, logging enabled, and inhibit recovery.

## 10. Critical Register Update

Two adjacent hardware registers must be written as one short uninterruptible sequence.
