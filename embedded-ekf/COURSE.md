# Embedded ESKF Course Plan

## Locked Design Decisions

- Filter type: 15-error-state ESKF.
- Navigation frame: local NED fixed at the launch pad.
- Body frame: `x_b` forward along the nose, `y_b` right, `z_b` down.
- Attitude convention: `q_nb` rotates body-frame vectors into the navigation frame.
- Prediction sensors: gyro and accelerometer IMU samples.
- Update sensors: GPS position and GPS velocity in local NED.
- Language: C99, using a conservative aerospace-style subset.
- Numeric type: `eskf_real_t`, defaulting to `float`.
- Memory: static allocation, caller-owned structs, no heap, no VLAs.
- Matrix style: explicit fixed-size helpers, not a generic matrix library.

## Course V1 Lessons

1. Course Contract And Frames
   - Math: frame definitions, units, state dimensions, and scope.
   - C artifact: dimension constants and core typedefs.

2. Nominal State vs Error State
   - Math: why attitude is a quaternion in the nominal state but 3D in the error state.
   - C artifact: `EskfNominalState`, `EskfConfig`, and `Eskf` structs.

3. Vector And Matrix Groundwork
   - Math: 3D vectors, fixed dimensions, and cross-product matrices.
   - C artifact: `vec3_*`, `skew3()`, and basic fixed-size helpers.

4. Quaternion Basics
   - Math: unit quaternions, multiplication, inverse, and normalization.
   - C artifact: `quat_normalize()`, `quat_multiply()`, `quat_inverse()`.

5. Rotate A Vector With `q_nb`
   - Math: body-to-navigation vector rotation.
   - C artifact: `quat_rotate_vec3()`.

6. IMU Measurement Model
   - Math: gyro and accelerometer measurements, bias, units, and NED gravity sign.
   - C artifact: `ImuSample`, bias correction helpers, and input validation.

7. Nominal Attitude Prediction
   - Math: integrate gyro into a quaternion.
   - C artifact: `eskf_predict_attitude()`.

8. Nominal Velocity And Position Prediction
   - Math: rotate specific force, add gravity, integrate velocity and position.
   - C artifact: `eskf_predict_nominal()`.

9. Covariance Meaning
   - Math: what `P` represents and why prediction grows uncertainty.
   - C artifact: `mat15_identity()` and covariance init/config tests.

10. Linearized Error Dynamics
    - Math: `F`, `G`, and process-noise dimensions.
    - C artifact: `eskf_build_F()` and `eskf_build_G()`.

11. Covariance Prediction
    - Math: discrete propagation and symmetry.
    - C artifact: `eskf_predict_covariance()`.

12. GPS Position Residual
    - Math: `z_p - p` and `H_pos = [I 0 0 0 0]`.
    - C artifact: position residual and `H` builder tests.

13. GPS Velocity Residual
    - Math: `z_v - v` and `H_vel = [0 I 0 0 0]`.
    - C artifact: velocity residual and `H` builder tests.

14. Kalman Correction
    - Math: innovation covariance, Kalman gain, and correction vector.
    - C artifact: fixed-size `6x6` solve/inverse and `eskf_compute_correction()`.

15. Error Injection And Reset
    - Math: apply `dp`, `dv`, `dtheta`, `dbg`, and `dba`.
    - C artifact: `eskf_apply_error_state()`.

16. GPS Position/Velocity Update
    - Math: combined 6D measurement update.
    - C artifact: `eskf_update_gps_pos_vel()`.

17. Innovation Gating
    - Math: reject implausible GPS updates.
    - C artifact: configurable gate and status return.

18. Top-Level Estimator API
    - Math: full predict/update call sequence.
    - C artifact: `eskf_init()`, `eskf_predict()`, `eskf_update_gps_pos_vel()`.

19. Tiny Stationary Caller
    - Scenario: stationary rocket, gravity-consistent IMU, repeated GPS.
    - C artifact: `examples/stationary_main.c`.

20. Toy Vertical Launch Caller
    - Scenario: scripted local-NED trajectory, IMU prediction, GPS correction.
    - C artifact: `examples/toy_launch_main.c` plus logs.

## Lesson Mode

Default mode is learner-built:

- The lesson gives the concept and contract.
- The repo gives a small red test and a narrow stub.
- The user implements the target.
- The agent reviews, debugs, and tightens the next step.

Exception: numerically fragile estimator internals may get a reference
implementation after the equations, dimensions, and tests are agreed.

