GL_TARGET = game
LIBS = -lm -D_REENTRANT -lGL -lGLEW -lSDL2 -lSDL2_image

NOGL_TARGET = game-nogl
NOGL_LIBS = -lm -D_REENTRANT -lSDL2 -lSDL2_image -lncurses

CC = gcc
CFLAGS = -g -Wall -I/usr/include/SDL2 -Icommon/ -Inogl/ -Igl/

.PHONY: default all clean

default: $(GL_TARGET)
all: default

COMMON_OBJECTS = $(patsubst common/%.c, common/%.o, $(wildcard common/*.c))
COMMON_HEADERS = $(wildcard common/*.h)
COMMON_SRCS = $(wildcard common/*.c)

NOGL_OBJECTS = $(patsubst nogl/%.c, nogl/%.o, $(wildcard nogl/*.c))
NOGL_HEADERS = $(wildcard nogl/*.h)
NOGL_SRCS = $(wildcard nogl/*.c)

GL_OBJECTS = $(patsubst gl/%.c, gl/%.o, $(wildcard gl/*.c))
GL_HEADERS = $(wildcard gl/*.h)
GL_SRCS = $(wildcard gl/*.c)

.PRECIOUS: $(TARGET) $(NOGL_TARGET) $(COMMON_OBJECTS) $(GL_OBJECTS) $(NOGL_OBJECTS)

$(GL_TARGET): $(COMMON_OBJECTS) $(GL_OBJECTS)
	$(CC) $(COMMON_OBJECTS) $(GL_OBJECTS) -Wall $(LIBS) -o $@

$(NOGL_TARGET): $(COMMON_OBJECTS) $(NOGL_OBJECTS)
	$(CC) $(COMMON_OBJECTS) $(NOGL_OBJECTS) -Wall $(NOGL_LIBS) -o $@

common/%.o: common/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

nogl/%.o: nogl/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

gl/%.o: gl/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f gl/*.o
	rm -f nogl/*.o
	rm -f common/*.o
	rm -f $(GL_TARGET)
	rm -f $(NOGL_TARGET)

output:
	@echo "==== gl ===="
	@echo "gl sources: $(GL_SRCS)"
	@echo "gl headers: $(GL_HEADERS)"
	@echo "gl objects: $(GL_OBJECTS)"
	@echo "==== nogl ===="
	@echo "nogl sources: $(NOGL_SRCS)"
	@echo "nogl headers: $(NOGL_HEADERS)"
	@echo "nogl objects: $(NOGL_OBJECTS)"
	@echo "==== common ===="
	@echo "common sources: $(COMMON_SRCS)"
	@echo "common headers: $(COMMON_HEADERS)"
	@echo "common objects: $(COMMON_OBJECTS)"
