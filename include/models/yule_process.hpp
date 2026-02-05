#pragma once
#include <vector>

namespace YuleModel {

    struct PopulationResult
    {
        std::vector<double> time;
        std::vector<int> population;
    };

    PopulationResult run_population_simulation(double lambda, double t_max);

    std::vector<int> run_batch_serial(double lambda, double t_max, int M_simulations);
    std::vector<int> run_batch_parallel(double lambda, double t_max, int M_simulations);
}
