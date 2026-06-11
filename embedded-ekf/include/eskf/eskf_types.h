#ifndef ESKF_TYPES_H
#define ESKF_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef float eskf_real_t;

enum {
    /* TODO(lesson 0001): replace each placeholder with the agreed dimension. */
    ESKF_VEC3_DIM = 1,
    ESKF_QUAT_DIM = 1,
    ESKF_NOMINAL_STATE_DIM = 1,
    ESKF_ERROR_STATE_DIM = 1,
    ESKF_IMU_NOISE_DIM = 1,
    ESKF_GPS_POS_VEL_DIM = 1
};

typedef enum {
    ESKF_STATUS_OK = 0,
    ESKF_STATUS_NULL_ARGUMENT,
    ESKF_STATUS_INVALID_DT,
    ESKF_STATUS_INVALID_CONFIG
} EskfStatus;

typedef enum {
    ESKF_FRAME_LOCAL_NED = 0,
    ESKF_FRAME_BODY_FORWARD_RIGHT_DOWN
} EskfFrameId;

#endif

