ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif
# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_mixer -lm

# add header files here
HDRS := 

# add source files here
SRCS := src/main.c src/screen_rendering.c src/SDL_initialisation.c src/user_input.c src/stage.c src/sound.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC1 := game

# default recipe
all: $(EXEC1)

# recipe for building the final executable
$(EXEC1): $(OBJS) $(HDRS) Makefile
	$(CC) -o $(EXEC1).$(EXEC) $(OBJS) $(CFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
run:
	./$(EXEC1).$(EXEC)

# recipe to clean the workspace
clean:
	$(RM) -f $(EXEC) $(OBJS)

.PHONY: all clean
