#include "flight_fsm.h"

#include <stddef.h>

void flight_fsm_init(FlightFsm *fsm)
{
    if (fsm == NULL)
    {
        return;
    }

    fsm->phase = FLIGHT_PHASE_IDLE;
    fsm->transitions = 0u;
}

FlightPhase flight_fsm_dispatch(FlightFsm *fsm, FlightEvent event)
{
    if (fsm == NULL)
    {
        return FLIGHT_PHASE_FAULT;
    }

    if (event == FLIGHT_EVENT_SENSOR_FAULT)
    {
        fsm->phase = FLIGHT_PHASE_FAULT;
        return fsm->phase;
    }

    return fsm->phase;
}
