#ifndef FLIGHT_TASK_H
#define FLIGHT_TASK_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FLIGHT_EVENT_NONE = 0,
    FLIGHT_EVENT_LAUNCH_DETECTED,
    FLIGHT_EVENT_BURNOUT_DETECTED,
    FLIGHT_EVENT_APOGEE_DETECTED,
    FLIGHT_EVENT_LANDING_DETECTED,
    FLIGHT_EVENT_SENSOR_FAULT
} FlightEvent;

typedef enum {
    FLIGHT_TASK_DISPATCH_EVENT = 0,
    FLIGHT_TASK_TIMEOUT,
    FLIGHT_TASK_FAULT
} FlightTaskResult;

typedef struct {
    bool has_event;
    FlightEvent event;
} FlightEventSource;

typedef struct {
    uint32_t wait_timeout_ticks;
    uint32_t dispatched_events;
    uint32_t idle_timeouts;
    bool fault_latched;
} FlightTask;

void flight_task_init(FlightTask *task, uint32_t wait_timeout_ticks);
FlightTaskResult flight_task_step(FlightTask *task,
                                  FlightEventSource *source,
                                  FlightEvent *out_event);

#endif
