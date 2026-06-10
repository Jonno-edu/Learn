#include "recovery_gate.h"

#include <stddef.h>

static const int32_t drogue_alt    = 500;
static const int32_t drogue_vel    = -40;
static const int32_t main_alt      = 20;
static const int32_t main_vel      = -10;

static bool is_valid_flight_state(FlightState state)
{
    return state >= FLIGHT_STATE_IDLE && state <= FLIGHT_STATE_DESCENT;
}

static bool should_deploy_drogue(const RecoveryGateInput *input);
static bool should_deploy_main(const RecoveryGateInput *input);

RecoveryGateDecision recovery_gate_evaluate(const RecoveryGateInput *input)
{
    if (input == NULL || !is_valid_flight_state(input->flight_state))
    {
        return RECOVERY_GATE_FAULT;
    }

    if (!input->pyro_armed)
    {
        return RECOVERY_GATE_HOLD;
    }

    if (input->flight_state != FLIGHT_STATE_DESCENT)
    {
        return RECOVERY_GATE_HOLD;
    }

    if (should_deploy_drogue(input))
    {
        return RECOVERY_GATE_DEPLOY_DROGUE;
    }

    if (should_deploy_main(input))
    {
        return RECOVERY_GATE_DEPLOY_MAIN;
    }



    return RECOVERY_GATE_HOLD;
}



static bool should_deploy_drogue(const RecoveryGateInput *input)
{
    return input->altitude_m > drogue_alt && input->vertical_velocity_mps < drogue_vel;
}


static bool should_deploy_main(const RecoveryGateInput *input)
{
    return input->altitude_m > main_alt && input->vertical_velocity_mps < main_vel;
}
