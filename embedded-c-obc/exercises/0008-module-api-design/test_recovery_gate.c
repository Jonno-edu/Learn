#include "recovery_gate.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    const RecoveryGateInput boost = {
        .altitude_m = 120,
        .vertical_velocity_mps = 80,
        .flight_state = FLIGHT_STATE_BOOST,
        .pyro_armed = true
    };

    const RecoveryGateInput descent_fast = {
        .altitude_m = 850,
        .vertical_velocity_mps = -45,
        .flight_state = FLIGHT_STATE_DESCENT,
        .pyro_armed = true
    };

    const RecoveryGateInput descent_low = {
        .altitude_m = 280,
        .vertical_velocity_mps = -18,
        .flight_state = FLIGHT_STATE_DESCENT,
        .pyro_armed = true
    };

    const RecoveryGateInput unarmed = {
        .altitude_m = 250,
        .vertical_velocity_mps = -20,
        .flight_state = FLIGHT_STATE_DESCENT,
        .pyro_armed = false
    };

    const RecoveryGateInput invalid_state = {
        .altitude_m = 500,
        .vertical_velocity_mps = -20,
        .flight_state = (FlightState)9,
        .pyro_armed = true
    };

    assert(recovery_gate_evaluate(NULL) == RECOVERY_GATE_FAULT);
    assert(recovery_gate_evaluate(&invalid_state) == RECOVERY_GATE_FAULT);
    assert(recovery_gate_evaluate(&unarmed) == RECOVERY_GATE_HOLD);
    assert(recovery_gate_evaluate(&boost) == RECOVERY_GATE_HOLD);
    assert(recovery_gate_evaluate(&descent_fast) == RECOVERY_GATE_DEPLOY_DROGUE);
    assert(recovery_gate_evaluate(&descent_low) == RECOVERY_GATE_DEPLOY_MAIN);

    puts("PASS: recovery gate module API exercise");
    return 0;
}
