# Bounded packet parser

The user completed the bounded packet parser exercise and successfully implemented the defensive validation order: null checks, minimum frame length, start bytes, payload length bounds, exact frame length, checksum validation, then output commit. Future lessons can assume the user has seen the frame-vs-payload distinction and the idea of validating before writing output, but should reinforce C size/index types and pointer-offset thinking.

Key friction points from the lesson:

- `size_t` was unfamiliar; future lessons should explicitly distinguish byte values (`uint8_t`) from sizes and indexes (`size_t`).
- The user needed clarification on frame versus payload: the frame is the whole transmitted buffer, while the payload is only the useful data inside it.
- The checksum call `obc_checksum(&frame[2], 2u + payload_len)` required explanation because taking the address of an indexed element changes where the helper begins reading.
- `sizeof(frame)` inside a function was a useful trap: the parameter is a pointer, not the original array.
- The defensive habit to keep drilling is: prove an index exists before reading `frame[i]`, then validate the whole frame before mutating `out`.
