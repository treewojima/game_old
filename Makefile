CC       := clang++
CFLAGS   := -c -ggdb3 -std=c++11 $(shell sdl2-config --cflags) $(WARNINGS) -Iinclude
WARNINGS := -Wall -Wnon-virtual-dtor -Wctor-dtor-privacy
LFLAGS   := $(shell sdl2-config --libs) -lSDL2_image -lGLEW -lGL -lGLU
PROJDIRS := include src
SOURCES  := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HEADERS  := $(shell find $(PROJDIRS) -type f -name "*.hpp")
OBJECTS  := $(patsubst %.cpp, %.o, $(SOURCES))
DEPFILES := $(patsubst %.cpp, %.dep, $(SOURCES))
TARGET   := game

.PHONY: all clean dumpvars

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LFLAGS) $^

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPFILES)
	find . -type f -iname "*~" -exec rm -f {} \;

-include $(DEPFILES)

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $<
	@#$(CC) -o $@ $(CFLAGS) -MMD -MP -MF $(patsubst %.c, %.dep, $<) $<

