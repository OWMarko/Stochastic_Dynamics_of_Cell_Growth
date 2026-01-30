#include <iostream>
#include <omp.h> 
#include "benchmark_runner.hpp"

#include "models/yule_process.hpp"
#include "models/inference.hpp"
#include "models/cell_mass.hpp"
#include "utils.hpp"

int main(void) {

    // We seed the chaos parameter, the number 42 is arbitrary but ensures reproducibility

    Utils::Random::init(42);

    // We check if OpenMP is enabled and how many cores we can use

    #ifdef _OPENMP
        std::cout << "[INFO] OpenMP active. Max Threads: " << omp_get_max_threads() << "\n";
    #else
        std::cout << "[WARN] OpenMP not found. Running in Serial mode.\n";
    #endif

    // We run the benchmark

    BenchmarkRunner::run_all_benchmarks();


    // We generate specific datasets that our Python scripts will turn into beautiful graphs

    std::cout << "--- GENERATING DATA FOR GRAPHS ---\n";
    double lambda = 2.0;

    // 1) INFERENCE DATA
    // We simulate a small batch just for the graph because saving million points from benchmark would explode the hard drive

    auto res_inf = InferenceModel::run_parallel(lambda, 1000); 
    Utils::IO::save_raw_data(res_inf.n_values, res_inf.estimated_lambda, "../data/inference_omp.csv", "n,estimated_lambda");

    // 2) CELL MASS TRAJECTORIES

    double t_max_mass = 15.0;
    double alpha = 1.0;
    
    // We launch two cells with radically different starting mass
    // The goal is to see if their trajectories eventually converge, called Memory Loss Theorem
    
    // Trajectory 1 : Starts very small (m0 = 0.1)
    Utils::Random::init(12345); 
    auto traj_small = CellMassModel::simulate_trajectory(alpha, lambda, 0.1, t_max_mass);
    Utils::IO::save_traj(traj_small.time, traj_small.mass, "../data/traj_small.csv", "time,mass");

    // Trajectory 2 : Starts huge (m0 = 10.0)
    Utils::Random::init(12345); 
    auto traj_large = CellMassModel::simulate_trajectory(alpha, lambda, 10.0, t_max_mass);
    Utils::IO::save_traj(traj_large.time, traj_large.mass, "../data/traj_large.csv", "time,mass");
    std::cout << "OK.\n";

    // 3) YULE PROCESS
    // We generate 5 parallel universes to visualize the stochastic variance

    for(int i=0; i<5; ++i)
    {
        auto res_pop = YuleModel::run_population_simulation(lambda, 4.0);
        std::string fname = "../data/pop_run_" + std::to_string(i) + ".csv";
        Utils::IO::save_pop(res_pop.time, res_pop.population, fname);
    }
    std::cout << "OK.\n";

    std::cout << "\n SIMULATION DONE \n";
    return 0;
}