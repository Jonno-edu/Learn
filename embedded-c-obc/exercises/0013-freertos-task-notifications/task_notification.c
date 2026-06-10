#include "task_notification.h"

#include <stddef.h>

void task_notification_init(TaskNotification *notification)
{
    if (notification == NULL)
    {
        return;
    }

    notification->pending_bits = 0u;
    notification->post_count = 0u;
    notification->wait_count = 0u;
}

bool task_notification_post_bits(TaskNotification *notification, uint32_t bits)
{
    
    if (notification == NULL || bits == 0u)
    {
        return false;
    }
    notification->pending_bits |= bits;
    notification->post_count += 1u;
    return true;
}

bool task_notification_wait_bits(TaskNotification *notification, uint32_t *out_bits)
{

    if (notification == NULL || out_bits == NULL)
    {
        return false;
    }

    if (notification->pending_bits == 0u)
    {
        *out_bits = 0u;
        return false;
    }

    *out_bits = notification->pending_bits;
    notification->pending_bits = 0u;
    notification->wait_count += 1u;
    return true;
}

FlightEvent task_notification_first_event(uint32_t bits)
{
    if ((bits & FLIGHT_NOTIFY_LAUNCH) != 0u)
    {
        return FLIGHT_EVENT_LAUNCH_DETECTED;
    }

    if ((bits & FLIGHT_NOTIFY_BURNOUT) != 0u)
    {
        return FLIGHT_EVENT_BURNOUT_DETECTED;
    }

    if ((bits & FLIGHT_NOTIFY_APOGEE) != 0u)
    {
        return FLIGHT_EVENT_APOGEE_DETECTED;
    }
    
    if ((bits & FLIGHT_NOTIFY_FAULT) != 0u)
    {
        return FLIGHT_EVENT_SENSOR_FAULT;
    }
    

    return FLIGHT_EVENT_NONE;
}
