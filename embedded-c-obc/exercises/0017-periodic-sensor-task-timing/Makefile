CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

include ../../freertos/freertos_posix.mk

.PHONY: test freertos-syntax clean

test: exercise
	./exercise

exercise: test_sensor_timing_policy.c sensor_timing_policy.c sensor_timing_policy.h
	$(CC) $(CFLAGS) test_sensor_timing_policy.c sensor_timing_policy.c -o exercise

freertos-syntax: imu_periodic_task.o

imu_periodic_task.o: imu_periodic_task.c sensor_timing_policy.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c imu_periodic_task.c -o imu_periodic_task.o

clean:
	rm -f exercise *.o
