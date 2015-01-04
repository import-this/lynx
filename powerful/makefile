# https://www.gnu.org/software/make/manual/make.html

# Set up compiler and options
CC = gcc
DEBUG = -g
OPT = -O3 -s -DNDEBUG
CFLAGS = -ansi -pedantic -Wall -Wextra -Wconversion -Wshadow
LDFLAGS = -flto		# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
MAIN_EXEC = ispowerful
TEST_EXEC = test
SRCS = ispowerful.c
MAIN = main.c
TEST = test.c

# Build main program command
$(MAIN_EXEC): $(SRCS) $(MAIN)
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) $? -o $@
	############################################################################
	# Example program call:
	# % ./ispowerful 1234

# Build powerful library command
powerful: $(SRCS)
	$(CC) $(CFLAGS) -c $?

# Build tests command
$(TEST_EXEC): $(SRCS) $(TEST)
	$(CC) $(CFLAGS) $? -o $@

# Remove all the compilation and debugging files
.PHONY: clean
clean:
	rm -rf $(MAIN_EXEC) $(TEST_EXEC) *.o *.exe
