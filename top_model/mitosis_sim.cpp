#include <cadmium/simulation/root_coordinator.hpp>
#include "mitosis_simulation.hpp" 

int main() {
    // Instantiate the Top Model
    auto model = std::make_shared<MitosisSimulation>("mitosis_sim");

    auto rootCoordinator = cadmium::RootCoordinator(model);

    rootCoordinator.start();
    rootCoordinator.simulate(100.0); 
    rootCoordinator.stop();

    return 0;
}