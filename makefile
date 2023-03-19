# Specifies which files to compile as part of the project
CPP_FILES := $(wildcard lib/*.cpp)
HPP_FILES := $(wildcard lib/*.hpp)

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = engine

# This is the target that compiles our executable
all : $(CPP_FILES) $(HPP_FILES)
	$(CC) $(CPP_FILES) $(HPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Cleanup
clean :
	rm -f $(OBJ_NAME)
