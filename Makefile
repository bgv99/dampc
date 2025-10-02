# Project Information
PROJECT_NAME := dampc
PROJECT_VERSION := 0.0.1

# Standard
CSTD := c99

# Release Optimization
COPT := 2

# Compiler
CC := gcc

# Archiver (For Library Creation)
AR := ar

# Compiler Flags
CFLAGS_ADD_DEBUG := -g3
CFLAGS_ADD_RELEASE := -O$(COPT) -DNDEBUG
CFLAGS_RELAXED := -Wall -Werror -Wextra -pipe
CFLAGS := $(CFLAGS_RELAXED) -pedantic -std=$(CSTD)

# Archiver Flags
ARFLAGS := rcs

# Include Directories
CINC :=

# Link Libraries
CLNK :=

# Compiler Defines (Regardless of Build Mode)
CDEF := \
	DAMPC_VERSION=\"$(PROJECT_VERSION)\"

# Target Binary Name
TARGET := $(PROJECT_NAME)

# Automatically Scan Source Files And Create Object File List
CSRC := $(wildcard src/*.c)
COBJ := $(patsubst src/%.c, build/%.o, $(CSRC))

# Stuff To Append To Compiler Flags
CFLAGS_ADD :=

# Add Include Directories To Compiler Flags
CFLAGS_ADD += $(addprefix -I, $(CINC))

# Add Link Libraries To Compiler Flags
CFLAGS_ADD += $(addprefix -l, $(CLNK))

# Add Compiler Definitions To Compiler Flags
CFLAGS_ADD += $(addprefix -D, $(CDEF))

# Build Mode
MODE ?= debug

# Address Sanitizer
ASAN ?= true

# Add Build Mode Flags
ifeq ($(MODE),release)
	CFLAGS_ADD += $(CFLAGS_ADD_RELEASE)
else
	CFLAGS_ADD += $(CFLAGS_ADD_DEBUG)

	# Add ASan Flags
	ifeq ($(ASAN),true)
		CFLAGS_ADD += -fsanitize=address
	endif
endif

# Compiler Flags Append
CFLAGS += $(CFLAGS_ADD)
CFLAGS_RELAXED += $(CFLAGS_ADD)

# Create .PHONY List
PHONY_LIST :=

PHONY_LIST += all
all: build/$(TARGET) | build

# Create Build Directory
build:
	mkdir build

# Link Target
build/$(TARGET): $(COBJ) | build
	$(CC) $(CFLAGS) -o $@ $^

# Compile Object Files From Source Files
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Delete Build Artifacts
PHONY_LIST += clean
clean:
	rm -rf build
	rm -rf .cache

# Delete Build Artifacts And More
PHONY_LIST += fresh
fresh: clean
	rm -rf compile_commands.json

# Define Makefile .PHONY
.PHONY: $(PHONY_LIST)
