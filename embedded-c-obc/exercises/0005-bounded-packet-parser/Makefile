CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: exercise.c
	$(CC) $(CFLAGS) exercise.c -o exercise

clean:
	rm -f exercise
