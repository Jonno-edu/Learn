#ifndef FLIGHT_FSM_H
#define FLIGHT_FSM_H

#include <stdint.h>

typedef enum {
    FLIGHT_PHASE_IDLE = 0,
    FLIGHT_PHASE_BOOST,
    FLIGHT_PHASE_COAST,
    FLIGHT_PHASE_DESCENT,
    FLIGHT_PHASE_LANDED,
    FLIGHT_PHASE_FAULT
} FlightPhase;

typedef enum {
    FLIGHT_EVENT_NONE = 0,
    FLIGHT_EVENT_LAUNCH_DETECTED,
    FLIGHT_EVENT_BURNOUT_DETECTED,
    FLIGHT_EVENT_APOGEE_DETECTED,
    FLIGHT_EVENT_LANDING_DETECTED,
    FLIGHT_EVENT_SENSOR_FAULT
} FlightEvent;

typedef struct {
    FlightPhase phase;
    uint32_t transitions;
} FlightFsm;

void flight_fsm_init(FlightFsm *fsm);
FlightPhase flight_fsm_dispatch(FlightFsm *fsm, FlightEvent event);

#endif
