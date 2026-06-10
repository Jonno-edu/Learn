CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_recovery_gate.c recovery_gate.c recovery_gate.h
	$(CC) $(CFLAGS) test_recovery_gate.c recovery_gate.c -o exercise

clean:
	rm -f exercise
