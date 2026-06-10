#include "flight_phase.h"

#include <stddef.h>

static const uint32_t DESCENT_REQ_SAMPLES  = 2u;
static const int32_t DESCENT_VEL_MPS = -10;
static const int32_t LANDED_VEL_MPS  = -1;
static const int32_t LANDED_ALT_M    = 5;


void flight_phase_init(FlightPhaseTracker *tracker)
{
    if (tracker == NULL)
    {
        return;
    }

    tracker->phase = FLIGHT_PHASE_IDLE;
    tracker->samples_in_phase = 0u;
    tracker->descent_candidate_samples = 0u;
}

FlightPhase flight_phase_update(FlightPhaseTracker *tracker, const FlightPhaseInput *input)
{
    if (tracker == NULL || input == NULL || !input->sensors_valid)
    {
        if (tracker != NULL)
        {
            tracker->phase = FLIGHT_PHASE_FAULT;
            tracker->samples_in_phase = 0u;
            return tracker->phase;


        }
        return FLIGHT_PHASE_FAULT;
    }

    tracker->samples_in_phase += 1u;

    switch (tracker->phase)
    {
    case FLIGHT_PHASE_IDLE:
        if (input->motor_burning)
        {
            tracker->phase = FLIGHT_PHASE_BOOST;
            tracker->samples_in_phase = 0u;
            return tracker->phase;

        }
        break;

    case FLIGHT_PHASE_BOOST:
        if (!input->motor_burning)
        {
            tracker->phase = FLIGHT_PHASE_COAST;
            tracker->samples_in_phase = 0u;
            return tracker->phase;
        }
        break;

    case FLIGHT_PHASE_COAST:
        if (input->vertical_velocity_mps < DESCENT_VEL_MPS)
        {
            tracker->descent_candidate_samples += 1u;
        }
        else 
        {
            tracker->descent_candidate_samples = 0u;
        }

        if (tracker->descent_candidate_samples >= DESCENT_REQ_SAMPLES)
        {
            tracker->phase = FLIGHT_PHASE_DESCENT;
            tracker->descent_candidate_samples = 0u;
            tracker->samples_in_phase = 0u;
            return tracker->phase;
        }

        break;

    case FLIGHT_PHASE_DESCENT:
    if (input->altitude_m <= LANDED_ALT_M
        && input->vertical_velocity_mps >= LANDED_VEL_MPS)
        {
            tracker->phase = FLIGHT_PHASE_LANDED;
            tracker->descent_candidate_samples = 0u;
            tracker->samples_in_phase = 0u;
            return tracker->phase;


        }
    break;
    
    default:
        tracker->phase = FLIGHT_PHASE_FAULT;
        tracker->samples_in_phase = 0u;
        tracker->descent_candidate_samples = 0u;
        return tracker->phase;
    }

    return tracker->phase;
}
