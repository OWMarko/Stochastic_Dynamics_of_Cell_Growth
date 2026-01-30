#include "models/yule_process.hpp"
#include "utils.hpp"
#include <cmath>
#include <omp.h>
#include <random>

// We want to simulate hundreds and thousands of colonies to estimate the final distribution (number of cells)
// If we store the full trajectory (vector time and size) for every single colony our computer will by suffering instantly
// Our function only returns the final population size keeping memory usage minimal 

namespace YuleModel {
    int simulate_final_pop_only(double lambda, double t_max, std::mt19937& rng)
    {
        double t = 0.0;
        int n = 1;

        while (t < t_max)
        {
            // Here we use the minimum lemma thanks to the expo distribution
            // With n individual cells the global rate of the next division is n * lambda
            // It's like having n alarm clocks ticking at the same time and the first one to ring triggers the event

            double rate = n * lambda;
            std::exponential_distribution<double> dist(rate);
            double dt = dist(rng);
            
            if (t + dt > t_max) break; // If the next event happens after the experiment ends we stop.

            t += dt;
            n++;  // One new cell is born
        }
        return n;
    }

    // Like said before we want to run M experiments one after another without kill our RAM
    // We create the vector

    std::vector<int> run_batch_serial(double lambda, double t_max, int M)
    {
        std::vector<int> results(M);
        std::mt19937 rng(42); 
        
        for(int i=0; i<M; ++i)
        {
            results[i] = simulate_final_pop_only(lambda, t_max, rng);
        }
        return results;
    }

    // But we can upgrade our approach by using multi threading
    // We have to use Monte-Carlo simulations and it's expensive 
    // Yet we know that the destiny of Colony A doesn't affect Colony B (independy of our distrib)
    // we can simulate them on different cores simultaneaously without complex communication between them

    std::vector<int> run_batch_parallel(double lambda, double t_max, int M) {
        std::vector<int> results(M);

        #pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            std::mt19937 local_rng(42 + thread_id); // independant RNG like always 

            #pragma omp for
            for(int i=0; i<M; ++i)
            {
                results[i] = simulate_final_pop_only(lambda, t_max, local_rng);
            }
        }
        return results;
    }

    // We want to see everything, we record every single birth event to plot the step function noted N(t)

    PopulationResult run_population_simulation(double lambda, double t_max)
    {
        PopulationResult res;
        double t = 0.0;
        int n = 1;

        res.time.push_back(t); // rec initial state
        res.population.push_back(n); // rec initial state

        while (t < t_max)
        {
            double total_rate = n * lambda;
            double dt = Utils::Random::exponential(total_rate); // There isn't thread conflicts -> global RNG
            if (t + dt > t_max)
            {
                res.time.push_back(t_max); // rec the stat at the end of the sim
                res.population.push_back(n); // same
                break;
            }
            t += dt;
            n += 1;
            res.time.push_back(t);
            res.population.push_back(n);
        }
        return res;
    }
}