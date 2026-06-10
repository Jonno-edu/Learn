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
        if (fsm->phase != FLIGHT_PHASE_FAULT)
        {
            fsm->phase = FLIGHT_PHASE_FAULT;
            fsm->transitions += 1u;
        }
        return fsm->phase;
    }

    switch (fsm->phase)
    {
    case FLIGHT_PHASE_IDLE:
        if (event == FLIGHT_EVENT_LAUNCH_DETECTED)
        {
            fsm->phase = FLIGHT_PHASE_BOOST;
            fsm->transitions += 1u;
            return fsm->phase;
        }
        break;

    case FLIGHT_PHASE_BOOST:
        if (event == FLIGHT_EVENT_BURNOUT_DETECTED)
        {
            fsm->phase = FLIGHT_PHASE_COAST;
            fsm->transitions += 1u;
            return fsm->phase;
        }
        break;

    case FLIGHT_PHASE_COAST:
        if (event == FLIGHT_EVENT_APOGEE_DETECTED)
        {
            fsm->phase = FLIGHT_PHASE_DESCENT;
            fsm->transitions += 1u;
            return fsm->phase;
        }
        break;

    case FLIGHT_PHASE_DESCENT:
        if (event == FLIGHT_EVENT_LANDING_DETECTED)
        {
            fsm->phase = FLIGHT_PHASE_LANDED;
            fsm->transitions += 1u;
            return fsm->phase;
        }
        break;

    case FLIGHT_PHASE_LANDED:
        return fsm->phase;

                    
    
    default:
        fsm->phase = FLIGHT_PHASE_FAULT;
        fsm->transitions += 1u;
        return fsm->phase;
    }

    return fsm->phase;
}
