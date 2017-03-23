CC := g++ # This is the main compiler
CFLAGS := -std=c++11

SRCDIR := src
BUILDDIR := build
TARGET := bin/compilo

HEADERS := $(shell find src/ -name *.hpp)
SOURCES := $(shell find src/ -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.cpp=.o))

all : $(TARGET)

doc: $(HEADERS)
	rm -rf doc/
	doxygen Doxyfile

clean:
	rm -rf build/ bin/ doc/

$(TARGET) : $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET)

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
