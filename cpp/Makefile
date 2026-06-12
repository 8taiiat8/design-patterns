# Build every pattern example into bin/<name>.
#
#   make            build all examples
#   make run        build and run all examples
#   make bin/singleton && ./bin/singleton   build and run one example
#   make clean      remove build output

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra

SOURCES  := $(wildcard creational/*.cpp structural/*.cpp behavioral/*.cpp)
BINARIES := $(patsubst %.cpp,bin/%,$(notdir $(SOURCES)))

VPATH := creational:structural:behavioral

all: $(BINARIES)

bin/%: %.cpp | bin
	$(CXX) $(CXXFLAGS) $< -o $@

bin:
	mkdir -p bin

run: all
	@for b in $(BINARIES); do echo "===== $$b ====="; ./$$b; echo; done

clean:
	rm -rf bin

.PHONY: all run clean
