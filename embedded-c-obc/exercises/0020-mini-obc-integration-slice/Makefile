CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_imu_health.c imu_health.c imu_health.h
	$(CC) $(CFLAGS) test_imu_health.c imu_health.c -o exercise

clean:
	rm -f exercise
