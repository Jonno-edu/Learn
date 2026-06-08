#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum {
    STATUS_RX_READY = 1u << 0,
    STATUS_TX_EMPTY = 1u << 1,
    STATUS_OVERRUN = 1u << 2,
    PACKET_LOW_BYTE_MASK = 0xffu,
    PACKET_CHANNEL_SHIFT = 8u,
    PACKET_CHANNEL_MASK = 0x0fu
};

static bool status_has_rx_ready(uint32_t status)
{
    return (status & STATUS_RX_READY) == STATUS_RX_READY;
}

static uint8_t packet_low_byte(uint32_t packet)
{
    return (uint8_t) (packet & PACKET_LOW_BYTE_MASK);
}

static uint8_t packet_channel(uint32_t packet)
{
    return (uint8_t) (packet >> PACKET_CHANNEL_SHIFT) & PACKET_CHANNEL_MASK;
}

int main(void)
{
    assert(!status_has_rx_ready(0u));
    assert(status_has_rx_ready(STATUS_RX_READY));
    assert(!status_has_rx_ready(STATUS_TX_EMPTY));
    assert(status_has_rx_ready(STATUS_RX_READY | STATUS_OVERRUN));

    assert(packet_low_byte(0x000000a5u) == 0xa5u);
    assert(packet_low_byte(0x123456a5u) == 0xa5u);
    assert(packet_low_byte(0xffffffffu) == 0xffu);

    assert(packet_channel(0x00000300u) == 3u);
    assert(packet_channel(0x00000f42u) == 15u);
    assert(packet_channel(0x1234a700u) == 7u);

    puts("PASS: bit masks, precedence, and casts exercise");
    return 0;
}
