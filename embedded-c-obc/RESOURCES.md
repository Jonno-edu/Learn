# Embedded C For Rocket OBC Firmware Resources

## Knowledge

- [cppreference: C volatile type qualifier](https://en.cppreference.com/c/language/volatile)
  Compact language reference for what `volatile` does and does not guarantee. Use for: qualifiers, memory-mapped I/O, and avoiding the common "volatile equals synchronization" misconception.
- [cppreference: C operator precedence](https://docs.cppreference.com/w/c/language/operator_precedence.html)
  Compact table showing why expressions such as `status & mask == mask` are parsed differently than many C programmers expect. Use for: parenthesizing bit tests and reading compiler precedence warnings.
- [cppreference: C implicit conversions](https://www.cppreference.com/w/c/language/conversion.html)
  Reference for integer promotions, boolean conversion, and narrowing conversions. Use for: explaining why returning a `uint32_t` expression from a `uint8_t` function truncates, and when explicit casts improve intent.
- [SEI CERT C INT02-C: Understand integer conversion rules](https://wiki.sei.cmu.edu/confluence/display/c/INT02-C.%2BUnderstand%2Binteger%2Bconversion%2Brules)
  Secure-coding guidance on C integer conversions. Use for: review posture around mixed signedness, narrowing, and firmware parser arithmetic.
- [SEI CERT C Coding Standard collection](https://www.sei.cmu.edu/library/sei-cert-c-and-c-coding-standards/)
  Secure C rules and recommendations from CMU SEI. Use for: undefined behavior, unsafe conversions, object lifetime, defensive APIs, and review checklists.
- [FreeRTOS task notification API reference](https://freertos.org/Documentation/02-Kernel/04-API-references/05-Direct-to-task-notifications/00-RTOS-task-notifications)
  Official FreeRTOS reference for lightweight task signaling. Use for: ISR-to-task and task-to-task communication once the C fundamentals reach RTOS boundaries.
- [NASA F Prime code and style guidelines](https://nasa.github.io/fprime/UsersGuide/dev/code-style.html)
  Flight-software-oriented guidance emphasizing readability, reviewability, bounded loops, avoiding recursion, controlled dynamic allocation, and checked return values. Use for: aerospace coding posture and review standards.
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
