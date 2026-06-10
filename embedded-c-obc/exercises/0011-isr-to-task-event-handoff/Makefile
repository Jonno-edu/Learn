CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_event_bridge.c event_bridge.c event_bridge.h
	$(CC) $(CFLAGS) test_event_bridge.c event_bridge.c -o exercise

clean:
	rm -f exercise
