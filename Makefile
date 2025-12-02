all: main

main: tests
	gcc -Wall -Wextra -fsanitize=leak -O2 -g ./src/main.c -o ./build/aoc2025

.PHONY: tests
tests:
	gcc -Wall -Wextra -fsanitize=leak ./tests/test.c -o ./tests/build/unittests && ./tests/build/unittests

.PHONY: clean
clean:
	rm -f ./tests/build/unittests ./build/aoc2025
