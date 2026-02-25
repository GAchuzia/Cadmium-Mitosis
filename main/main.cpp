#include <iostream>
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "../top_model/top.hpp"

using namespace cadmium;

int main() {
    auto model = std::make_shared<top_model>("top");

    auto rootCoordinator = RootCoordinator(model);

    rootCoordinator.setLogger<STDOUTLogger>(";");

    // Run the simulation (all atomic tests in parallel; events up to ~23s)
    rootCoordinator.start();
    rootCoordinator.simulate(100.0);
    rootCoordinator.stop();

    return 0;
}