#include "event_bridge.h"

#include <stddef.h>

void event_bridge_init(EventBridge *bridge)
{
    if (bridge == NULL)
    {
        return;
    }

    bridge->pending_event = FLIGHT_EVENT_NONE;
    bridge->has_pending_event = false;
    bridge->dropped_events = 0u;
}

bool event_bridge_post_from_isr(EventBridge *bridge, FlightEvent event)
{
    if (bridge == NULL)
    {
        return false;
    }

    if (bridge->has_pending_event)
    {
        bridge->dropped_events += 1u;
        return false;
    }

    if (event == FLIGHT_EVENT_NONE)
    {
        return false;
    }


    bridge->has_pending_event = true;
    bridge->pending_event = event;
    return true;

}

bool event_bridge_take_for_task(EventBridge *bridge, FlightEvent *out_event)
{
    
    if (bridge == NULL || out_event == NULL)
    {
        return false;
    }

    if (bridge->has_pending_event)
    {
        *out_event = bridge->pending_event;
        bridge->has_pending_event = false;
        bridge->pending_event = FLIGHT_EVENT_NONE;
        return true;
    }

    return false;
}
