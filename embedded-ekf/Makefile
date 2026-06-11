CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic -Werror -Iinclude

TEST_0001 := build/test_0001_contract

.PHONY: all test clean

all: test

build:
	mkdir -p build

$(TEST_0001): tests/test_0001_contract.c include/eskf/eskf_types.h | build
	$(CC) $(CFLAGS) tests/test_0001_contract.c -o $(TEST_0001)

test: $(TEST_0001)
	$(TEST_0001)

clean:
	rm -rf build

