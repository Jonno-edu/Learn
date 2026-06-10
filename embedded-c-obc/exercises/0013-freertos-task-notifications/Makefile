CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: test clean

test: exercise
	./exercise

exercise: test_task_notification.c task_notification.c task_notification.h
	$(CC) $(CFLAGS) test_task_notification.c task_notification.c -o exercise

clean:
	rm -f exercise
