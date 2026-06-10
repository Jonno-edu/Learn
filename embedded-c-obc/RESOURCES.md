# Embedded C For Rocket OBC Firmware Resources

## Knowledge

- [cppreference: C volatile type qualifier](https://en.cppreference.com/c/language/volatile)
  Compact language reference for what `volatile` does and does not guarantee. Use for: qualifiers, memory-mapped I/O, and avoiding the common "volatile equals synchronization" misconception.
- [cppreference: C operator precedence](https://docs.cppreference.com/w/c/language/operator_precedence.html)
  Compact table showing why expressions such as `status & mask == mask` are parsed differently than many C programmers expect. Use for: parenthesizing bit tests and reading compiler precedence warnings.
- [cppreference: C implicit conversions](https://www.cppreference.com/w/c/language/conversion.html)
  Reference for integer promotions, boolean conversion, and narrowing conversions. Use for: explaining why returning a `uint32_t` expression from a `uint8_t` function truncates, and when explicit casts improve intent.
- [cppreference: C fixed-width integer types](https://en.cppreference.com/c/types/integer)
  Reference for `<stdint.h>` exact-width, least-width, fast-width, max-width, and pointer-capable integer typedefs. Use for: choosing `uint8_t`, `uint16_t`, `uint32_t`, `int16_t`, and related embedded data types.
- [cppreference: C size_t](https://en.cppreference.com/c/types/size_t)
  Reference for `size_t` as the unsigned result type of `sizeof` and a normal type for object sizes, array indexes, and loop counts. Use for: buffer lengths and parser indexes.
- [cppreference: C array declaration](https://en.cppreference.com/w/c/language/array)
  Reference for array objects and element access. Use for: payload buffers, fixed frame layouts, and array-to-pointer behavior in function parameters.
- [cppreference: C pointer declaration](https://en.cppreference.com/w/c/language/pointer)
  Reference for pointer declarations and pointer targets. Use for: parsing functions that receive byte buffers and output structs.
- [cppreference: C atomic types](https://en.cppreference.com/c/language/atomic)
  Reference for C11 `_Atomic` objects and `<stdatomic.h>`. Use for: distinguishing atomics from `volatile` and from RTOS synchronization primitives.
- [cppreference: C restrict qualifier](https://en.cppreference.com/c/language/restrict)
  Reference for the C99 no-alias pointer qualifier. Use for: understanding optimizer promises and why `restrict` should be used only when the aliasing contract is provable.
- [SEI CERT C INT02-C: Understand integer conversion rules](https://wiki.sei.cmu.edu/confluence/display/c/INT02-C.%2BUnderstand%2Binteger%2Bconversion%2Brules)
  Secure-coding guidance on C integer conversions. Use for: review posture around mixed signedness, narrowing, and firmware parser arithmetic.
- [SEI CERT C INT32-C: Ensure operations on signed integers do not result in overflow](https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.%2BEnsure%2Bthat%2Boperations%2Bon%2Bsigned%2Bintegers%2Bdo%2Bnot%2Bresult%2Bin%2Boverflow)
  Secure-coding rule for signed overflow. Use for: scaling raw sensor values, counters, and intermediate arithmetic in flight code.
- [SEI CERT C ARR30-C: Do not form or use out-of-bounds pointers or array subscripts](https://wiki.sei.cmu.edu/confluence/x/wtYxBQ)
  Secure-coding rule for array bounds. Use for: packet parsing, payload copies, and defensive checks before indexing buffers.
- [SEI CERT C Coding Standard collection](https://www.sei.cmu.edu/library/sei-cert-c-and-c-coding-standards/)
  Secure C rules and recommendations from CMU SEI. Use for: undefined behavior, unsafe conversions, object lifetime, defensive APIs, and review checklists.
- [FreeRTOS task notification API reference](https://freertos.org/Documentation/02-Kernel/04-API-references/05-Direct-to-task-notifications/00-RTOS-task-notifications)
  Official FreeRTOS reference for lightweight task signaling. Use for: ISR-to-task and task-to-task communication once the C fundamentals reach RTOS boundaries.
- [FreeRTOS queue API reference](https://www.freertos.org/Documentation/02-Kernel/04-API-references/06-Queues/00-Queues)
  Official FreeRTOS reference for queue-based item passing. Use for: buffering flight events or sensor samples between ISR/task and task/task boundaries.
- [NASA F Prime code and style guidelines](https://nasa.github.io/fprime/UsersGuide/dev/code-style.html)
  Flight-software-oriented guidance emphasizing readability, reviewability, bounded loops, avoiding recursion, controlled dynamic allocation, and checked return values. Use for: aerospace coding posture and review standards.
- [NASA cFS repository and documentation links](https://github.com/nasa/cFS)
  NASA Core Flight System bundle and reference links for flight software architecture, applications, platform abstraction, host builds, telemetry, commands, and mission-specific app selection. Use for: module boundaries, app/framework separation, host-side testing, and flight-software architecture vocabulary.
- [The Power of Ten: Rules for Developing Safety-Critical Code](https://spinroot.com/gerard/pdf/P10.pdf)
  Gerard Holzmann's compact safety-critical C ruleset from NASA/JPL practice. Use for: simple control flow, bounded loops, avoiding recursion, limiting scope, checking returns, and keeping code reviewable.
- [Bosch Sensortec BMP280 data sheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)
  Real sensor datasheet with status bits and packed pressure/temperature data registers. Use for: translating register-map tables into C masks, shifts, and byte-combining helpers.

## Wisdom (Communities)

- [EmbeddedRelated forums](https://www.embeddedrelated.com/forums/)
  Practitioner forum for embedded design and debugging. Use for: sanity-checking driver design, timing issues, and toolchain-specific embedded behavior.
- [Stack Overflow: embedded tag](https://stackoverflow.com/questions/tagged/embedded)
  Useful when questions are specific and reproducible. Use for: compiler diagnostics, small C examples, and toolchain behavior.

## Gaps

- Add the user's actual OBC codebase, target MCU, compiler, FreeRTOS version, and coding standard once available.
- Add the project-specific sensor/protocol datasheets later; register-level lessons should cite the exact hardware manuals when known.
