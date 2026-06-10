#ifndef TASK_NOTIFICATION_H
#define TASK_NOTIFICATION_H

#include <stdbool.h>
#include <stdint.h>

#define FLIGHT_NOTIFY_LAUNCH  (1u << 0)
#define FLIGHT_NOTIFY_BURNOUT (1u << 1)
#define FLIGHT_NOTIFY_APOGEE  (1u << 2)
#define FLIGHT_NOTIFY_FAULT   (1u << 3)

typedef enum {
    FLIGHT_EVENT_NONE = 0,
    FLIGHT_EVENT_LAUNCH_DETECTED,
    FLIGHT_EVENT_BURNOUT_DETECTED,
    FLIGHT_EVENT_APOGEE_DETECTED,
    FLIGHT_EVENT_SENSOR_FAULT
} FlightEvent;

typedef struct {
    uint32_t pending_bits;
    uint32_t post_count;
    uint32_t wait_count;
} TaskNotification;

void task_notification_init(TaskNotification *notification);
bool task_notification_post_bits(TaskNotification *notification, uint32_t bits);
bool task_notification_wait_bits(TaskNotification *notification, uint32_t *out_bits);
FlightEvent task_notification_first_event(uint32_t bits);

#endif
