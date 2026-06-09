# Notes

- User has C and embedded experience but wants to rebuild fundamentals due to rustiness and over-reliance on AI.
- Teaching should start from first principles while staying tied to rocket OBC firmware.
- Keep lessons short, practical, and feedback-driven.
- Later sessions should be tailored against the user's real OBC codebase.
- Lesson 1 friction point: the user understood why hardware registers need `volatile`, but struggled with C expression mechanics: bit masks versus equality, operator precedence, named masks versus magic numbers, and explicit narrowing from register-width values to smaller fields.
- Lesson 5 friction points: the user completed the bounded packet parser, but needed explicit teaching on `size_t`, frame versus payload, `&frame[2]` as a pointer start offset, why `sizeof(frame)` is pointer size inside a function, and the validate-before-output parser habit.
- Good next lesson candidate: a compact embedded-C type toolbox covering `uint8_t`, `uint16_t`, `uint32_t`, `int16_t`, `size_t`, `bool`, pointers, arrays, and when each should be used in OBC-style firmware.
