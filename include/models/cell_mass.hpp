#pragma once
#include <vector>

// We want to look at what happens to them physically, we call it Cell Mass Dynamics
// Here we model how a cell grows, divides, and how its mass fluctuates over time.

namespace CellMassModel {

    // Here we only care about the mass at the exact moment of division (Z_n), not the whole journey.

    struct MassExperimentResult
    {
        std::vector<double> mass_at_division; 
    };

    MassExperimentResult run_experiment_serial(double alpha, double lambda, double m0, int n_cells);

    // The optimized approach, we process the whole colony at once using multiple cores
    MassExperimentResult run_experiment_parallel(double alpha, double lambda, double m0, int n_cells);

    // There we track the mass evolution of a single cell lineage over time to visualize the "Memory Loss" phenomenon

    struct MassTrajectoryResult
    {
        std::vector<double> time;
        std::vector<double> mass;
    };

    // alpha = growth speed
    // lambda = our rate
    // m0 = initial mass
    // t_max = max time
    // n_cells = number of cells

    MassExperimentResult run_mass_experiment(double alpha, double lambda, double m0, int n_cells);
    MassTrajectoryResult simulate_trajectory(double alpha, double lambda, double m0, double t_max);
}