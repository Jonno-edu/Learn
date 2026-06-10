# Exercise 0007: Pack IMU Telemetry

Implement a bounded OBC telemetry packet builder.

The packet carries one flight state and one IMU sample:

```text
0: 0xa5
1: 0x5a
2: msg_id = 0x42
3: payload_len = 13
4: flight_state
5..16: accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z as int16_t little-endian
17: checksum
```

Checksum is the low byte of the sum of `msg_id`, `payload_len`, and payload bytes.

Rules:

- Reject null pointers.
- Reject invalid flight states.
- Check output capacity before writing the frame.
- Pack signed 16-bit fields little-endian.
- Set `*out_len` only after a complete frame is written.

Run:

```sh
rtk make test
```

After it passes, answer:

> Which argument proves it is safe to write `out_frame[17]`?
