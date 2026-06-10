#ifndef FLIGHT_PHASE_H
#define FLIGHT_PHASE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FLIGHT_PHASE_IDLE = 0,
    FLIGHT_PHASE_BOOST,
    FLIGHT_PHASE_COAST,
    FLIGHT_PHASE_DESCENT,
    FLIGHT_PHASE_LANDED,
    FLIGHT_PHASE_FAULT
} FlightPhase;

typedef struct {
    int32_t altitude_m;
    int32_t vertical_velocity_mps;
    bool motor_burning;
    bool sensors_valid;
} FlightPhaseInput;

typedef struct {
    FlightPhase phase;
    uint32_t samples_in_phase;
    uint32_t descent_candidate_samples;
} FlightPhaseTracker;

void flight_phase_init(FlightPhaseTracker *tracker);
FlightPhase flight_phase_update(FlightPhaseTracker *tracker, const FlightPhaseInput *input);

#endif
