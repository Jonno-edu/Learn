#include "flight_fsm.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    FlightFsm fsm;
    flight_fsm_init(&fsm);

    assert(fsm.phase == FLIGHT_PHASE_IDLE);
    assert(fsm.transitions == 0u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_NONE) == FLIGHT_PHASE_IDLE);
    assert(fsm.transitions == 0u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_APOGEE_DETECTED) == FLIGHT_PHASE_IDLE);
    assert(fsm.transitions == 0u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_LAUNCH_DETECTED) == FLIGHT_PHASE_BOOST);
    assert(fsm.transitions == 1u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_LANDING_DETECTED) == FLIGHT_PHASE_BOOST);
    assert(fsm.transitions == 1u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_BURNOUT_DETECTED) == FLIGHT_PHASE_COAST);
    assert(fsm.transitions == 2u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_APOGEE_DETECTED) == FLIGHT_PHASE_DESCENT);
    assert(fsm.transitions == 3u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_LANDING_DETECTED) == FLIGHT_PHASE_LANDED);
    assert(fsm.transitions == 4u);

    assert(flight_fsm_dispatch(&fsm, FLIGHT_EVENT_SENSOR_FAULT) == FLIGHT_PHASE_FAULT);
    assert(fsm.transitions == 5u);

    puts("PASS: event-driven flight FSM exercise");
    return 0;
}
