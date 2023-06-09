CC = g++
CFLAGS = -Wall -Wextra --std=c++17
CFLAGS += -Isrc
LDFLAGS = 

CPP_SRC_FILES = $(shell find src -name '*.cpp')
CPP_OBJ_FILES = $(patsubst src/%.cpp, build/%.o, $(CPP_SRC_FILES))



#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = engine
build/%.o: src/%.cpp
	mkdir -p $(dir $@) && \
	$(CC) -Og -g $(CFLAGS) -c -o $@ $^
.PHONY: clean build_target
# This is the target that compiles our executable
build_target: $(CPP_OBJ_FILES)
	mkdir -p bin && \
	$(CC) -o bin/main $^ $(LDFLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 
# Cleanup
clean :
	rm -rf build
	rm -rf bin
