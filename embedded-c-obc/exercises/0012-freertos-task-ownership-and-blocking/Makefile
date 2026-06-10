CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_flight_task.c flight_task.c flight_task.h
	$(CC) $(CFLAGS) test_flight_task.c flight_task.c -o exercise

clean:
	rm -f exercise
