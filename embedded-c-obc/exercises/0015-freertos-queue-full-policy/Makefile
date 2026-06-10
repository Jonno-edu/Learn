CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

include ../../freertos/freertos_posix.mk

.PHONY: test freertos-syntax freertos-test clean

test: exercise
	./exercise

exercise: test_drop_policy.c drop_policy.c drop_policy.h
	$(CC) $(CFLAGS) test_drop_policy.c drop_policy.c -o exercise

freertos-syntax: imu_queue_overflow.o

freertos-test: freertos_queue_overflow
	./freertos_queue_overflow

freertos_queue_overflow: test_imu_queue_overflow_freertos.c imu_queue_overflow.c imu_queue_overflow.h drop_policy.c drop_policy.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(FREERTOS_CFLAGS) $(FREERTOS_INCLUDES) test_imu_queue_overflow_freertos.c imu_queue_overflow.c drop_policy.c $(FREERTOS_KERNEL_SRCS) $(FREERTOS_LDLIBS) -o freertos_queue_overflow

imu_queue_overflow.o: imu_queue_overflow.c imu_queue_overflow.h drop_policy.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c imu_queue_overflow.c -o imu_queue_overflow.o

clean:
	rm -f exercise *.o freertos_queue_overflow
