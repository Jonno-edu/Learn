#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t STATUS;
    volatile uint32_t DATA;
} UartRegs;

enum {
    UART_STATUS_RX_READY = 1u << 0,
    UART_DATA_MASK = 0xffu
};

static bool uart_rx_ready(const UartRegs *uart)
{
    if ((uart->STATUS & UART_STATUS_RX_READY) == UART_STATUS_RX_READY){
        return true;
    } else return false;

}

static uint8_t uart_read_data(const UartRegs *uart)
{
    uint8_t uart_data = (uart->DATA & UART_DATA_MASK);
    return uart_data;
}

int main(void)
{
    UartRegs fake_uart = {
        .STATUS = 0u,
        .DATA = 0x000001a5u
    };

    assert(!uart_rx_ready(&fake_uart));

    fake_uart.STATUS = UART_STATUS_RX_READY;
    assert(uart_rx_ready(&fake_uart));
    assert(uart_read_data(&fake_uart) == 0xa5u);

    fake_uart.DATA = 0x00000042u;
    assert(uart_read_data(&fake_uart) == 0x42u);

    puts("PASS: volatile register exercise");
    return 0;
}
