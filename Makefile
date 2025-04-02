CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS = -lm

# Example targets
EXAMPLES = minunit_example verbose_minunit_example jtn002_example

all: $(EXAMPLES)

# Build the basic example
minunit_example: examples/minunit_example.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Build the verbose example
verbose_minunit_example: examples/verbose_minunit_example.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Build the jtn002 example
jtn002_example: examples/jtn002_example.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Run examples
run: all
	@echo "\nRunning basic example:"
	@./minunit_example
	@echo "\nRunning verbose example:"
	@./verbose_minunit_example
	@echo "\nRunning jtn002 example:"
	@./jtn002_example

# Clean build files
clean:
	rm -f $(EXAMPLES)

.PHONY: all run clean 