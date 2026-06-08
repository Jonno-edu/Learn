# Embedded C OBC Glossary

This is the quick dictionary for terms learned in the lessons. Keep definitions short and practical.

## Access And Hardware

**`volatile`**
: A C qualifier that tells the compiler an object may change outside normal C code, so each volatile access matters. Use for memory-mapped hardware registers. It is not a mutex, atomic, or FreeRTOS synchronization tool.

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

**two's complement**
: The representation used by modern C targets for signed integers, where a set top bit indicates a negative value. Example: the 16-bit pattern `0xff38` represents `-200` when interpreted as `int16_t`.

**`size_t`**
: An unsigned type used for object sizes and array lengths. Use it for buffer lengths and indexes into byte arrays.

**bounds check**
: A check that proves an index or copy length stays inside the available buffer before accessing memory.

**checksum**
: A small computed value carried with a packet to catch corrupted or malformed data. Simple exercises may use byte-sum checksums; real protocols define the exact algorithm.

**payload**
: The data part of a packet after headers and length fields.

**frame**
: The complete on-wire packet bytes, including header, metadata, payload, and checksum.
