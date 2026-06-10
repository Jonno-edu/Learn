#include "task_notification.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    TaskNotification notification;
    uint32_t bits = 0u;

    task_notification_init(&notification);
    assert(notification.pending_bits == 0u);
    assert(notification.post_count == 0u);
    assert(notification.wait_count == 0u);

    assert(task_notification_wait_bits(&notification, &bits) == false);
    assert(bits == 0u);
    assert(notification.wait_count == 0u);

    assert(task_notification_post_bits(&notification, FLIGHT_NOTIFY_APOGEE) == true);
    assert(notification.pending_bits == FLIGHT_NOTIFY_APOGEE);
    assert(notification.post_count == 1u);

    assert(task_notification_post_bits(&notification, FLIGHT_NOTIFY_APOGEE) == true);
    assert(notification.pending_bits == FLIGHT_NOTIFY_APOGEE);
    assert(notification.post_count == 2u);

    assert(task_notification_post_bits(&notification, FLIGHT_NOTIFY_FAULT) == true);
    assert(notification.pending_bits == (FLIGHT_NOTIFY_APOGEE | FLIGHT_NOTIFY_FAULT));
    assert(notification.post_count == 3u);

    assert(task_notification_wait_bits(&notification, &bits) == true);
    assert(bits == (FLIGHT_NOTIFY_APOGEE | FLIGHT_NOTIFY_FAULT));
    assert(notification.pending_bits == 0u);
    assert(notification.wait_count == 1u);

    assert(task_notification_first_event(FLIGHT_NOTIFY_LAUNCH) == FLIGHT_EVENT_LAUNCH_DETECTED);
    assert(task_notification_first_event(FLIGHT_NOTIFY_BURNOUT) == FLIGHT_EVENT_BURNOUT_DETECTED);
    assert(task_notification_first_event(FLIGHT_NOTIFY_APOGEE | FLIGHT_NOTIFY_FAULT) == FLIGHT_EVENT_APOGEE_DETECTED);
    assert(task_notification_first_event(FLIGHT_NOTIFY_FAULT) == FLIGHT_EVENT_SENSOR_FAULT);
    assert(task_notification_first_event(0u) == FLIGHT_EVENT_NONE);

    assert(task_notification_post_bits(NULL, FLIGHT_NOTIFY_LAUNCH) == false);
    assert(task_notification_post_bits(&notification, 0u) == false);
    assert(task_notification_wait_bits(&notification, NULL) == false);

    puts("PASS: FreeRTOS task notification exercise");
    return 0;
}
