CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

include ../../freertos/freertos_posix.mk

.PHONY: test freertos-syntax freertos-test clean

test: freertos-test

freertos-syntax: imu_queue_app.o imu_tasks.o

freertos-test: freertos_imu_queue_app
	./freertos_imu_queue_app

freertos_imu_queue_app: test_imu_queue_app_freertos.c imu_queue_app.c imu_queue_app.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(FREERTOS_CFLAGS) $(FREERTOS_INCLUDES) test_imu_queue_app_freertos.c imu_queue_app.c $(FREERTOS_KERNEL_SRCS) $(FREERTOS_LDLIBS) -o freertos_imu_queue_app

imu_queue_app.o: imu_queue_app.c imu_queue_app.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c imu_queue_app.c -o imu_queue_app.o

imu_tasks.o: imu_tasks.c imu_queue_app.h
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(CFLAGS) $(FREERTOS_INCLUDES) -c imu_tasks.c -o imu_tasks.o

clean:
	rm -f *.o freertos_imu_queue_app
