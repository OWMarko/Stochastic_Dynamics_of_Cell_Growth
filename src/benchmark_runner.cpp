#include "benchmark_runner.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

#include "models/inference.hpp"
#include "models/cell_mass.hpp"
#include "models/yule_process.hpp"

// Since we want to compare the parallel method with the clasic one we need a stopwatch
// Instead of copu-pasting the timing with same code we create a macro for that
// This part is fully generate with IA, I'm still a beginner I'm trying to learn as best I can ! 
// But I understand this code

#define RUN_BENCHMARK(name, func_serial, func_parallel) \
    { \
        std::cout << "--- BENCHMARK: " << name << " ---\n"; \
        std::cout << "  -> Serial... " << std::flush; \
        auto t1 = std::chrono::high_resolution_clock::now(); \
        func_serial; \
        auto t2 = std::chrono::high_resolution_clock::now(); \
        double d_serial = std::chrono::duration<double>(t2 - t1).count(); \
        std::cout << "Done in " << d_serial << "s\n"; \
        std::cout << "  -> OpenMP... " << std::flush; \
        auto t3 = std::chrono::high_resolution_clock::now(); \
        func_parallel; \
        auto t4 = std::chrono::high_resolution_clock::now(); \
        double d_parallel = std::chrono::duration<double>(t4 - t3).count(); \
        std::cout << "Done in " << d_parallel << "s\n"; \
        if(d_parallel > 0) { \
            double speedup = d_serial / d_parallel; \
            std::cout << "  => SPEEDUP = x" << speedup << "\n\n"; \
        } else { \
            std::cout << "  => Too fast to measure speedup.\n\n"; \
        } \
    }

namespace BenchmarkRunner {

    void run_all_benchmarks() {
        std::cout << "\n[Performance test started]\n";
        
        double lambda = 2.0;

        // 1) INFERENCE

        int n_inf = 50000000; 
        RUN_BENCHMARK("Inference (Estimation Lambda)", 
            (InferenceModel::run_serial(lambda, n_inf)), 
            (InferenceModel::run_parallel(lambda, n_inf))
        );

        // 2) CELL MASS

        double alpha = 1.0;
        double m0 = 1.0;
        int n_cells = 50000000;
        RUN_BENCHMARK("Cell Mass (Distribution Zn)",
            (CellMassModel::run_experiment_serial(alpha, lambda, m0, n_cells)),
            (CellMassModel::run_experiment_parallel(alpha, lambda, m0, n_cells))
        );

        // 3) YULE PROCESS

        double t_max = 5.0;
        int M_sims = 100000; 
        RUN_BENCHMARK("Yule Process",
            (YuleModel::run_batch_serial(lambda, t_max, M_sims)),
            (YuleModel::run_batch_parallel(lambda, t_max, M_sims))
        );
        
        std::cout << "[Performance test ended]\n\n";
    }
}