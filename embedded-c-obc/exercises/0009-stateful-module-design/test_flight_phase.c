#include "flight_phase.h"

#include <assert.h>
#include <stdio.h>

static FlightPhaseInput sample(int32_t altitude_m,
                               int32_t vertical_velocity_mps,
                               bool motor_burning)
{
    const FlightPhaseInput input = {
        .altitude_m = altitude_m,
        .vertical_velocity_mps = vertical_velocity_mps,
        .motor_burning = motor_burning,
        .sensors_valid = true
    };
    return input;
}

int main(void)
{
    FlightPhaseTracker tracker;
    flight_phase_init(&tracker);

    assert(tracker.phase == FLIGHT_PHASE_IDLE);
    assert(tracker.samples_in_phase == 0u);
    assert(tracker.descent_candidate_samples == 0u);

    FlightPhaseInput boost = sample(20, 35, true);
    assert(flight_phase_update(&tracker, &boost) == FLIGHT_PHASE_BOOST);
    assert(tracker.phase == FLIGHT_PHASE_BOOST);
    assert(tracker.samples_in_phase == 0u);

    FlightPhaseInput coast = sample(600, 12, false);
    assert(flight_phase_update(&tracker, &coast) == FLIGHT_PHASE_COAST);
    assert(tracker.phase == FLIGHT_PHASE_COAST);

    FlightPhaseInput descending = sample(850, -15, false);
    assert(flight_phase_update(&tracker, &descending) == FLIGHT_PHASE_COAST);
    assert(flight_phase_update(&tracker, &descending) == FLIGHT_PHASE_DESCENT);
    assert(tracker.phase == FLIGHT_PHASE_DESCENT);

    FlightPhaseInput landed = sample(2, 0, false);
    assert(flight_phase_update(&tracker, &landed) == FLIGHT_PHASE_LANDED);

    FlightPhaseTracker invalid_tracker;
    flight_phase_init(&invalid_tracker);
    FlightPhaseInput invalid = sample(100, 10, false);
    invalid.sensors_valid = false;
    assert(flight_phase_update(&invalid_tracker, &invalid) == FLIGHT_PHASE_FAULT);
    assert(invalid_tracker.phase == FLIGHT_PHASE_FAULT);

    puts("PASS: stateful flight phase module exercise");
    return 0;
}
