CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

include ../../freertos/freertos_posix.mk

.PHONY: test freertos-syntax freertos-test clean

test: freertos-test

freertos-syntax: isr_queue_handoff.o imu_dma_isr.o

freertos-test: freertos_isr_queue_handoff
	./freertos_isr_queue_handoff

freertos_isr_queue_handoff: test_isr_queue_handoff_freertos.c isr_queue_handoff.c isr_queue_handoff.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(FREERTOS_CFLAGS) $(FREERTOS_INCLUDES) test_isr_queue_handoff_freertos.c isr_queue_handoff.c $(FREERTOS_KERNEL_SRCS) $(FREERTOS_LDLIBS) -o freertos_isr_queue_handoff

isr_queue_handoff.o: isr_queue_handoff.c isr_queue_handoff.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c isr_queue_handoff.c -o isr_queue_handoff.o

imu_dma_isr.o: imu_dma_isr.c isr_queue_handoff.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c imu_dma_isr.c -o imu_dma_isr.o

clean:
	rm -f *.o freertos_isr_queue_handoff
