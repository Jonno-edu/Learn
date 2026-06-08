# Exercise 0005: Bounded Packet Parser

Implement a defensive parser for a tiny OBC-style binary frame.

Frame format:

```text
0: 0xa5
1: 0x5a
2: msg_id
3: payload_len
4..: payload bytes
last: checksum
```

Checksum is the low byte of the sum of `msg_id`, `payload_len`, and payload bytes.

Rules:

- Reject null pointers.
- Check lengths before indexing.
- Reject payloads larger than the output payload buffer.
- Verify checksum before writing output.

Run:

```sh
rtk make test
```

After it passes, answer:

> What check proves it is safe to read the checksum byte?
