#INCLUDE specifies which headers to use.
#INCLUDE = #include<SDL2/SDL.h>


#OBJS specifies which files to cimple as part of the project
OBJS = 01_hello_SDL.cpp

#CC specified which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional comilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJS_NAME specifies the name of our executable
OBJ_NAME = 01_hello_SDL

#This is the target that compliles our executable. Command to create the target must begin with a tab or MAKE will #reject it.
all : $(OBJS)
	 $(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

