# Event-driven state machines

The user completed the event-driven flight FSM exercise and practiced separating event detection from transition policy. Future lessons can assume the user has seen the pattern: convert observations into named events, dispatch one event at a time, switch by current phase first, keep transition helpers private, and test unexpected events deliberately.

This is the direct bridge into FreeRTOS: the FSM should remain ordinary host-testable C, while the RTOS task, queue, notification, or ISR adapter handles event delivery around it.
