# Embedded C OBC Glossary

This is the quick dictionary for terms learned in the lessons. Keep definitions short and practical.

## Access And Hardware

**`volatile`**
: A C qualifier that tells the compiler an object may change outside normal C code, so each volatile access matters. Use for memory-mapped hardware registers. It is not a mutex, atomic, or FreeRTOS synchronization tool.

**`const`**
: A qualifier that prevents modification through that name. Use for read-only input buffers, tables, and protocol constants. It does not mean the underlying object can never change through any other path.

**`static`**
: At file scope, makes a function or object private to that C file. Inside a function, gives an object static lifetime so it keeps its value between calls.

**`_Atomic`**
: A C11 type specifier/qualifier for atomic objects. Use only when the toolchain, target, and concurrency model are understood; it is different from `volatile`.

**`restrict`**
: A pointer qualifier that promises the object modified through that pointer is not accessed through another pointer path in the same block. Breaking that promise can cause undefined behavior.

**memory-mapped register**
: A hardware register exposed at an address that C code can read or write as if it were memory. Reads and writes may trigger hardware behavior.

**register field**
: A subset of bits inside a register with a specific meaning, such as bit 3 meaning "sensor measuring".

**raw value**
: The direct decoded value from hardware or a packet before calibration, scaling, filtering, or physical-unit conversion.

## Bit Operations

**bit**
: One binary digit, either 0 or 1.

**nibble**
: Four bits. One hexadecimal digit represents one nibble.

**byte**
: Eight bits. Usually represented by two hexadecimal digits.

**mask**
: A value used to isolate, set, clear, or test specific bits.

**bitwise AND (`&`)**
: Keeps only bits that are 1 in both operands. Used to test or extract fields.

**bitwise OR (`|`)**
: Combines bits. Used to assemble non-overlapping fields or set bits.

**left shift (`<<`)**
: Moves bits toward more significant positions. In register decoding, often places a byte into a wider field.

**right shift (`>>`)**
: Moves bits toward less significant positions. In register decoding, often drops unused low bits or moves a field down to bit 0.

**whole-register equality**
: Comparing an entire register to one expected bit pattern. Usually wrong for status registers because unrelated bits may also be set.

## C Expression Mechanics

**operator precedence**
: The rules that decide how C groups an expression before evaluating it. Example: `==` binds before `&`, so write `(status & mask) == mask`.

**cast**
: An explicit conversion written by the programmer, such as `(uint8_t)value`. In firmware, casts should communicate intent, not hide warnings.

**narrowing**
: Converting from a wider type to a smaller type, such as `uint32_t` to `uint8_t`. Mask first, then cast when only a small field is intended.

**integer promotion**
: C's rule that small integer types such as `uint8_t` are often promoted to `int` or `unsigned int` before arithmetic.

**fixed-width integer**
: A type from `<stdint.h>` with an explicit size, such as `uint8_t`, `uint16_t`, `uint32_t`, or `int16_t`.

**`uint8_t`**
: An unsigned 8-bit integer. Use for one byte of protocol, register, payload, or checksum data.

**`uint16_t`**
: An unsigned 16-bit integer. Use for two-byte raw fields, counters with known range, or packed unsigned values.

**`uint32_t`**
: An unsigned 32-bit integer. Use for 32-bit registers, masks, counters, and wider unsigned intermediate values.

**`int16_t`**
: A signed 16-bit integer. Use for raw signed sensor values when the protocol or datasheet says the field is signed 16-bit.

**`int32_t`**
: A signed 32-bit integer. Use for wider signed arithmetic, especially before scaling or combining smaller signed values.

**two's complement**
: The representation used by modern C targets for signed integers, where a set top bit indicates a negative value. Example: the 16-bit pattern `0xff38` represents `-200` when interpreted as `int16_t`.

**`size_t`**
: An unsigned type used for object sizes and array lengths. Use it for buffer lengths and indexes into byte arrays.

**pointer**
: A C value that holds the address of an object or the start of a buffer. Example: `const uint8_t *frame` points to the first byte the parser may read.

**array**
: Actual contiguous storage for a fixed number of elements. Example: `uint8_t payload[8]` stores eight payload bytes inside a packet struct.

**struct**
: A C type that groups related fields into one object, such as an OBC packet with message ID, payload length, and payload bytes.

**enum**
: A C construct for named integer constants. Useful for protocol constants, states, and fixed limits.

**bounds check**
: A check that proves an index or copy length stays inside the available buffer before accessing memory.

**checksum**
: A small computed value carried with a packet to catch corrupted or malformed data. Simple exercises may use byte-sum checksums; real protocols define the exact algorithm.

**payload**
: The data part of a packet after headers and length fields.

**frame**
: The complete on-wire packet bytes, including header, metadata, payload, and checksum.

**telemetry**
: Data sent from the vehicle to another system for monitoring, logging, or analysis. Example: an OBC packet containing IMU values and flight state.

**packing**
: Turning typed C values such as structs, enums, and integers into a defined sequence of bytes for storage or transmission.

**little-endian**
: Byte order where the least significant byte is stored or transmitted first. In this workspace, a 16-bit value `0x03d5` packs as `0xd5 0x03`.

## Module Design

**module**
: A small group of C files that owns one capability, such as packet packing, recovery gating, or state-machine updates.

**API**
: The public contract a caller uses to interact with a module: visible types, constants, and function prototypes.

**header file (`.h`)**
: The public face of a C module. It should contain the declarations callers need, not private implementation details.

**source file (`.c`)**
: The implementation of a C module. It should contain private helpers, internal thresholds, and function bodies.

**internal linkage**
: File-private visibility for a function or object, usually created with file-scope `static`.

**context struct**
: Caller-provided storage that a module uses to remember state between calls, such as the current state-machine phase.

**state machine**
: Logic that stores a current state and changes state only through defined transitions.

**event**
: A named occurrence consumed by a state machine, such as launch detected, apogee detected, landing detected, or sensor fault.

**dispatch**
: To feed one event into a state machine so it can apply the transition policy for its current state.

**transition**
: A deliberate change from one state to another in response to an event or condition.

## RTOS Boundary

**ISR**
: Interrupt service routine. Code that runs in interrupt context in response to hardware or timing events. Keep it short and avoid blocking work.

**task**
: A schedulable FreeRTOS thread of execution. In this workspace, a task should usually own long-running module state such as the flight FSM context.

**task notification**
: A lightweight FreeRTOS mechanism for signaling a specific task. Useful when a compact event or wakeup is enough.

**queue**
: A FreeRTOS object for passing items between tasks or from an ISR to a task. Use when event values or samples must be buffered in order.

**FromISR API**
: A FreeRTOS API variant intended for interrupt context, such as queue send or task notification functions with `FromISR` in the name.

**overflow policy**
: The documented behavior when an event bridge, queue, or buffer is full, such as reject newest, overwrite oldest, or count drops.
