#pragma once
# include <vector>

// The goal here is to estimate the division rate lambda
// And we'll test the raw power of our code by comparing a classic approach vs a parallel one

// Since we don't want juste a final answer, we want to see the evolution of the approximation,
// so we create a vector with the steps n and the estimation

namespace InferenceModel {

    struct ConvergenceResult
    {
        std::vector<double> n_values;
        std::vector<double> estimated_lambda;
    };

    ConvergenceResult run_serial(double true_lambda, int n_max);

    // We'll use OpenMP here, we split the workload across all available threads to minimize runtime
    
    ConvergenceResult run_parallel(double true_lambda, int n_max);
}