#pragma once
#include <vector>

namespace YuleModel {

    struct PopulationResult
    {
        std::vector<double> time;
        std::vector<int> population;
    };

    /**
     * @brief Simule un processus de Yule (Explosion démographique)
     * Utilise le Lemme du Minimum (Gillespie)
     */
    PopulationResult run_population_simulation(double lambda, double t_max);

    // --- POUR LE BENCHMARK ---
    // On veut la population finale de M expériences différentes
    std::vector<int> run_batch_serial(double lambda, double t_max, int M_simulations);
    std::vector<int> run_batch_parallel(double lambda, double t_max, int M_simulations);
}