#include "flight_task.h"

#include <stddef.h>

void flight_task_init(FlightTask *task, uint32_t wait_timeout_ticks)
{
    if (task == NULL)
    {
        return;
    }

    task->wait_timeout_ticks = wait_timeout_ticks;
    task->dispatched_events = 0u;
    task->idle_timeouts = 0u;
    task->fault_latched = false;
}

FlightTaskResult flight_task_step(FlightTask *task,
                                  FlightEventSource *source,
                                  FlightEvent *out_event)
{

    if (task == NULL || source == NULL || out_event == NULL)
    {
        if (task != NULL)
        {
            task->fault_latched = true;
        }
        return FLIGHT_TASK_FAULT;
    }

    if (source->has_event == false)
    {
        task->idle_timeouts += 1u;
        return FLIGHT_TASK_TIMEOUT;
    }

    *out_event = source->event;
    source->has_event = false;
    source->event = FLIGHT_EVENT_NONE;
    task->dispatched_events += 1u;

    return FLIGHT_TASK_DISPATCH_EVENT;

}
