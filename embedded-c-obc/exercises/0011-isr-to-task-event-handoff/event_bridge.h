#ifndef EVENT_BRIDGE_H
#define EVENT_BRIDGE_H

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

typedef struct {
    FlightEvent pending_event;
    bool has_pending_event;
    uint32_t dropped_events;
} EventBridge;

void event_bridge_init(EventBridge *bridge);
bool event_bridge_post_from_isr(EventBridge *bridge, FlightEvent event);
bool event_bridge_take_for_task(EventBridge *bridge, FlightEvent *out_event);

#endif
