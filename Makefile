# Compiler and flags
CC = clang
CFLAGS = -O3 -Isrc/lib/ -Isrc/string

# Source files
SRCS = $(wildcard src/*.c) $(wildcard src/string/*.c)

OUTPUT = /usr/bin/zelemi
all: $(OUTPUT)

# Color codes
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

$(OUTPUT): $(SRCS)
	@echo -e "$(YELLOW)Building...$(RESET)"
	@$(CC) $(CFLAGS) $(SRCS) -o $(OUTPUT)
	@echo -e "$(GREEN)Build completed successfully!$(RESET)"

# Clean target
clean:
	@echo -e "$(RED)Cleaning up...$(RESET)"
	@rm -f $(OUTPUT)
	@echo -e "$(GREEN)Clean completed!$(RESET)"

.PHONY: all clean
