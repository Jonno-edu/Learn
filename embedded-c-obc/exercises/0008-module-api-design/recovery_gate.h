#ifndef RECOVERY_GATE_H
#define RECOVERY_GATE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FLIGHT_STATE_IDLE = 0,
    FLIGHT_STATE_BOOST = 1,
    FLIGHT_STATE_COAST = 2,
    FLIGHT_STATE_DESCENT = 3
} FlightState;

typedef enum {
    RECOVERY_GATE_HOLD = 0,
    RECOVERY_GATE_DEPLOY_DROGUE,
    RECOVERY_GATE_DEPLOY_MAIN,
    RECOVERY_GATE_FAULT
} RecoveryGateDecision;

typedef struct {
    int32_t altitude_m;
    int32_t vertical_velocity_mps;
    FlightState flight_state;
    bool pyro_armed;
} RecoveryGateInput;

RecoveryGateDecision recovery_gate_evaluate(const RecoveryGateInput *input);

#endif
