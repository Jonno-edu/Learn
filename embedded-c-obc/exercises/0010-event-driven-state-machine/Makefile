CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_flight_fsm.c flight_fsm.c flight_fsm.h
	$(CC) $(CFLAGS) test_flight_fsm.c flight_fsm.c -o exercise

clean:
	rm -f exercise
