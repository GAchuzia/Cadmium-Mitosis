# Cadmium Mitosis — Makefile
# Usage:
#   make all          # build simulation and run_tests
#   make simulation   # build ./simulation
#   make run_tests    # build ./run_tests
#   make run-simulation   # build and run ./simulation
#   make run-tests        # build and run ./run_tests
#   make clean        # remove built executables
#
# Override Cadmium include path if needed:
#   make CADMIUM_PATH=/path/to/cadmium/include

CADMIUM_PATH ?= /home/cadmium/rt_cadmium/include
CXX          = g++
CXXFLAGS     = -g -O3 -std=c++17 -I$(CADMIUM_PATH)

# Executables
SIMULATION   = simulation
RUN_TESTS    = run_tests

# Headers that trigger rebuild (wildcard evaluated once)
TOP_HEADERS  = top_model/top.hpp
MAIN_HEADERS = main/include/centrosome.hpp main/include/centrosome_pair.hpp \
	main/include/cell_structures.hpp main/include/chromosome.hpp \
	main/include/nuclear_envelope.hpp main/include/nucleolus.hpp \
	main/include/phase_control.hpp main/include/phase_controller.hpp \
	main/include/spindle.hpp main/include/status_checker.hpp

.PHONY: all clean simulation run_tests run-simulation run-tests

all: $(SIMULATION) $(RUN_TESTS)
	@echo ""
	@echo "Build complete. Run: ./$(SIMULATION)  or  ./$(RUN_TESTS)"

simulation: main/main.cpp $(TOP_HEADERS) $(MAIN_HEADERS)
	$(CXX) $(CXXFLAGS) main/main.cpp -o $(SIMULATION)
	@echo "Run: ./$(SIMULATION)"

run_tests: tests/main.cpp tests/test.hpp $(MAIN_HEADERS)
	$(CXX) $(CXXFLAGS) tests/main.cpp -o $(RUN_TESTS)
	@echo "Run: ./$(RUN_TESTS)"

run-simulation: $(SIMULATION)
	./$(SIMULATION)

run-tests: $(RUN_TESTS)
	./$(RUN_TESTS)

clean:
	rm -f $(SIMULATION) $(RUN_TESTS)
