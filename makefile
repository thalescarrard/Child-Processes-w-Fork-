# Compiler
CC = gcc

# Compiler flags (optional but recommended)
CFLAGS = -Wall -Werror

# Target executable names
TARGETS = prime_finder

# Source files
SRC = prime_finder.c

# Default target: compile and link
all: $(TARGETS)

# Compile targets
$(TARGETS): %: %.c
	$(CC) $(CFLAGS) -o $@ $^

# Run target
run: $(TARGETS)
	./prime_finder

# Clean target: remove the compiled programs
clean:
	rm -f $(TARGETS)

# Rebuild target: clean and then compile
rebuild: clean all
