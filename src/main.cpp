#include <string>
#include <vector>
#include "models/yule_process.hpp"
#include "models/inference.hpp"
#include "models/cell_mass.hpp"
#include "utils.hpp"


int main(int argc, char* argv[]) {
    std::cout << "--- Stochastic Cell Growth Simulation ---\n";
    
    // Default parameters
    double lambda = 2.0;
    double time_horizon = 5.0;
    
    // Soon..
    
    std::cout << "Running simulation with Lambda=" << lambda << "...\n";
    
    // Soon...

    std::cout << "Done. Results saved to data/output.csv\n";
    return 0;
}