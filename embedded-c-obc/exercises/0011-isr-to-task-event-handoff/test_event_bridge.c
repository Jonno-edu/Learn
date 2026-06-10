#include "event_bridge.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    EventBridge bridge;
    FlightEvent event = FLIGHT_EVENT_NONE;

    event_bridge_init(&bridge);
    assert(bridge.pending_event == FLIGHT_EVENT_NONE);
    assert(bridge.has_pending_event == false);
    assert(bridge.dropped_events == 0u);

    assert(event_bridge_take_for_task(&bridge, &event) == false);
    assert(event == FLIGHT_EVENT_NONE);

    assert(event_bridge_post_from_isr(&bridge, FLIGHT_EVENT_LAUNCH_DETECTED) == true);
    assert(bridge.has_pending_event == true);
    assert(bridge.pending_event == FLIGHT_EVENT_LAUNCH_DETECTED);

    assert(event_bridge_post_from_isr(&bridge, FLIGHT_EVENT_APOGEE_DETECTED) == false);
    assert(bridge.dropped_events == 1u);
    assert(bridge.pending_event == FLIGHT_EVENT_LAUNCH_DETECTED);

    assert(event_bridge_take_for_task(&bridge, &event) == true);
    assert(event == FLIGHT_EVENT_LAUNCH_DETECTED);
    assert(bridge.has_pending_event == false);
    assert(bridge.pending_event == FLIGHT_EVENT_NONE);

    assert(event_bridge_post_from_isr(&bridge, FLIGHT_EVENT_SENSOR_FAULT) == true);
    assert(event_bridge_take_for_task(&bridge, &event) == true);
    assert(event == FLIGHT_EVENT_SENSOR_FAULT);

    assert(event_bridge_post_from_isr(NULL, FLIGHT_EVENT_BURNOUT_DETECTED) == false);
    assert(event_bridge_take_for_task(&bridge, NULL) == false);
    assert(bridge.dropped_events == 1u);

    puts("PASS: ISR-to-task event bridge exercise");
    return 0;
}
