OS_NAME = $(shell uname -s)

TARGET ?= DESKTOP

RELEASE ?= DEBUG

# Folder containing the source code
SRC_DIR = ./chastybiscuit

# Build output folder
OBJDIR := objects

# Game output name
OUTPUT_NAME = ChastyBiscuit

CC := g++

C_SRCS :=
CPP_SRCS :=
OBJS :=

OUTPUT :=

LDFLAGS := 
CFLAGS := -Wall -Werror -Wextra #-fsanitize=address
INCLUDE := -I $(SRC_DIR)

# Get the source files and setup other variables depending on the OS
ifeq ($(OS_NAME), Linux)
	C_SRCS  += $(shell find $(SRC_DIR) -type f -name '*.c')
	CPP_SRCS += $(shell find $(SRC_DIR) -type f -name '*.cpp')
else ifeq ($(OS_NAME), Darwin)
	C_SRCS  += $(shell find $(SRC_DIR) -type f -name '*.c')
	CPP_SRCS += $(shell find $(SRC_DIR) -type f -name '*.cpp')
else
	C_SRCS += $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
	CPP_SRCS += $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
endif

# Setup the object files
OBJS += $(patsubst $(SRC_DIR)/%.cpp, $(OBJDIR)/%.o, $(CPP_SRCS)) $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(C_SRCS))

# Setup web and desktop configurations
ifeq ($(TARGET), WEB)
	CC = em++
	LDFLAGS += -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' -s WASM=1  --preload-file resources/* -Wno-unused-command-line-argument

	OUTPUT = index.js
else ifeq ($(OS_NAME), Linux)
	LDFLAGS += `pkg-config --libs --cflags sdl2 SDL2_image SDL2_ttf` -lm

	OUTPUT = $(OUTPUT_NAME).out
else ifeq ($(OS_NAME), Darwin)
	LDFLAGS += `pkg-config --libs --cflags sdl2 SDL2_image SDL2_ttf` -lm

	OUTPUT = $(OUTPUT_NAME).out
else
	LDFLAGS += `pkg-config --libs --cflags sdl2 SDL2_image SDL2_ttf | sed 's/-mwindows//'` -lm

	OUTPUT = $(OUTPUT_NAME).exe
endif

# Setup CFLAGS for either release or debug
ifeq ($(RELEASE), DEBUG)
	CFLAGS += -g -O0
ifeq ($(TARGET), WEB)
	CFLAGS += --emrun
endif
else
	CFLAGS += -O2
endif

.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS) $(INCLUDE)

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(INCLUDE)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(INCLUDE)

clean:
	rm -rf *.o *.exe *.out $(OBJDIR)