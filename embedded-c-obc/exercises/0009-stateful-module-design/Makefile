CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_flight_phase.c flight_phase.c flight_phase.h
	$(CC) $(CFLAGS) test_flight_phase.c flight_phase.c -o exercise

clean:
	rm -f exercise
