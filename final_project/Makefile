CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
EXECUTABLE := main

# List of source files
SRCS := main.cpp board.cpp dice.cpp game.cpp player.cpp square.cpp
OBJS := $(SRCS:.cpp=.o)

# Main target
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up generated files
clean:
	rm -f $(EXECUTABLE) $(OBJS)
