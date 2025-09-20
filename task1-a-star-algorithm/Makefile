# Makefile for Chess A* Solver

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
TARGET = chess_solver

# Source files
SOURCES = main.cpp types.cpp priority_queue.cpp chess_state.cpp heuristic.cpp astar_solver.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = types.h priority_queue.h chess_state.h heuristic.h astar_solver.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Force rebuild
rebuild: clean all

# Install (copy to /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Release build (optimized)
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# Check for memory leaks (requires valgrind)
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Format code (requires clang-format)
format:
	clang-format -i *.cpp *.h

# Generate documentation (requires doxygen)
docs:
	doxygen Doxyfile

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and build"
	@echo "  install   - Install to /usr/local/bin"
	@echo "  uninstall - Remove from /usr/local/bin"
	@echo "  run       - Build and run the program"
	@echo "  debug     - Build with debug symbols"
	@echo "  release   - Build optimized version"
	@echo "  memcheck  - Run with valgrind memory checker"
	@echo "  format    - Format source code"
	@echo "  docs      - Generate documentation"
	@echo "  help      - Show this help message"

# Declare phony targets
.PHONY: all clean rebuild install uninstall run debug release memcheck format docs help

# Dependencies (automatically generated)
main.o: main.cpp astar_solver.h priority_queue.h chess_state.h types.h heuristic.h
types.o: types.cpp types.h
priority_queue.o: priority_queue.cpp priority_queue.h chess_state.h types.h
chess_state.o: chess_state.cpp chess_state.h types.h
heuristic.o: heuristic.cpp heuristic.h chess_state.h types.h
astar_solver.o: astar_solver.cpp astar_solver.h priority_queue.h chess_state.h types.h heuristic.h