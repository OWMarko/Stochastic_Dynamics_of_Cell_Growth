#include "models/cell_mass.hpp"
#include "utils.hpp"
#include <cmath>
#include <omp.h> 
#include <random> 

namespace CellMassModel {

    // We simulate the final state of N cells one after another
    // It's a simple and reliable approch but very slow for massive datasets

    MassExperimentResult run_experiment_serial(double alpha, double lambda, double m0, int n_cells)
    {

        MassExperimentResult res;
        res.mass_at_division.resize(n_cells); // we block the memory now because we know how many cells we want

        for (int i = 0; i < n_cells; ++i)
        {
            double tau = Utils::Random::exponential(lambda); // life duration, cells grow exponentially until it divides
            res.mass_at_division[i] = m0 * std::exp(alpha * tau); 
        }

        return res;
    }

    // We know every cell's life is independent of its neighbor
    // We can simulate simulatneously on different cores, we'll use parallelism 

    MassExperimentResult run_experiment_parallel(double alpha, double lambda, double m0, int n_cells)
    {
        MassExperimentResult res;
        res.mass_at_division.resize(n_cells);

        // We run our code on multiple threads to eco time

        #pragma omp parallel
        {
            // Like before we use different generators 

            int thread_id = omp_get_thread_num();
            std::mt19937 local_rng(42 + thread_id); 
            std::exponential_distribution<double> dist_exp(lambda);

            // We share the work by slipting iterations among the threads
            // To imagine the mecanism : the door 0 takes students 0 to 100, the door 1 takes students 101 to 200 and so on

            #pragma omp for
            for (int i = 0; i < n_cells; ++i)
            {
                double tau = dist_exp(local_rng);
                res.mass_at_division[i] = m0 * std::exp(alpha * tau); // same formula there
            }
        }
        return res;
    }

    // The previous function return only the mass at the division but we want to know the trajectory of the mass at each second
    // This function records the entire kife of a single cell, by this method we can  visualize the memory loss
    
    MassTrajectoryResult simulate_trajectory(double alpha, double lambda, double m0, double t_max)
    {
        MassTrajectoryResult res;
        double t = 0.0;
        double current_mass = m0;

        // we start at frame 0

        res.time.push_back(t);
        res.mass.push_back(current_mass);

        while (t < t_max)
        {
            double tau = Utils::Random::exponential(lambda); // how long until the next div

            if (t + tau > t_max) // the simulation time is over before the cell divides
            {

                // We simulate the growth for the remaining time and stop

                current_mass += alpha * (t_max - t); // linear approx for the trajectory step
                t = t_max;
                res.time.push_back(t);
                res.mass.push_back(current_mass);
                break;
            }

            // Growth phase 

            t += tau;
            current_mass += alpha * tau;

            // We catch the mass before division

            res.time.push_back(t);
            res.mass.push_back(current_mass);

            // We divide, the cell splits and the mass is divided by 2

            current_mass /= 2.0;

            // We catch also the mass after the split

            res.time.push_back(t);
            res.mass.push_back(current_mass);
        }
        return res;
    }

}