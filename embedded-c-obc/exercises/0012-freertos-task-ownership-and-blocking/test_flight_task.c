#include "flight_task.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    FlightTask task;
    FlightEventSource source = {
        .has_event = false,
        .event = FLIGHT_EVENT_NONE,
    };
    FlightEvent event = FLIGHT_EVENT_NONE;

    flight_task_init(&task, 25u);
    assert(task.wait_timeout_ticks == 25u);
    assert(task.dispatched_events == 0u);
    assert(task.idle_timeouts == 0u);
    assert(task.fault_latched == false);

    assert(flight_task_step(&task, &source, &event) == FLIGHT_TASK_TIMEOUT);
    assert(task.idle_timeouts == 1u);
    assert(task.dispatched_events == 0u);
    assert(event == FLIGHT_EVENT_NONE);

    source.has_event = true;
    source.event = FLIGHT_EVENT_APOGEE_DETECTED;
    assert(flight_task_step(&task, &source, &event) == FLIGHT_TASK_DISPATCH_EVENT);
    assert(event == FLIGHT_EVENT_APOGEE_DETECTED);
    assert(source.has_event == false);
    assert(source.event == FLIGHT_EVENT_NONE);
    assert(task.dispatched_events == 1u);
    assert(task.idle_timeouts == 1u);

    assert(flight_task_step(NULL, &source, &event) == FLIGHT_TASK_FAULT);
    assert(flight_task_step(&task, NULL, &event) == FLIGHT_TASK_FAULT);
    assert(flight_task_step(&task, &source, NULL) == FLIGHT_TASK_FAULT);
    assert(task.fault_latched == true);

    puts("PASS: FreeRTOS task ownership and blocking exercise");
    return 0;
}
