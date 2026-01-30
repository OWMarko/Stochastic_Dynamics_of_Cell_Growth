#include "models/inference.hpp"
#include <omp.h>
#include <random>   
#include <numeric>
#include "utils.hpp"

// Let's approach lambda, we'll use 2 different methods here, a intuitive (serial) and parallel

namespace InferenceModel {

    // We observe divisions one by one

    ConvergenceResult run_serial(double true_lambda, int n_max)
    {
        // Since we know exactly how many data we have, we reserve memory to avoid resizing the vector and everytime we push a new value

        ConvergenceResult res;
        res.n_values.reserve(n_max);
        res.estimated_lambda.reserve(n_max);

        double current_sum_Tn = 0.0;

        // At each step n we get a new time interval and we update the total time

        for(int n = 1; n <= n_max; ++n)
        {
            double time_interval = Utils::Random::exponential(true_lambda);

            current_sum_Tn += time_interval;

            double lambda_esti = static_cast<double>(n) / current_sum_Tn; // we force n to become a double before the opperation happen

            // Finally we add our value to the end of our reserved memory

            res.n_values.push_back(static_cast<double>(n)); 
            res.estimated_lambda.push_back(lambda_esti);

        }
        
        return res;

    }

    // Here we use parallel strategy and we cannot use push back due to the multiple thread, we'll use resize

    ConvergenceResult run_parallel(double true_lambda, int n_max)
    {
        ConvergenceResult res;
        
        std::vector<double> time_intervals(n_max);

        // Resize creates empty places in memory, it allows each thread to access to the step n without further permissions
        // It's like assigning a specific seat to every guest before the party starts

        res.n_values.resize(n_max);
        res.estimated_lambda.resize(n_max);

        #pragma omp parallel
        {
            int thread_id = omp_get_thread_num();

            // Due to the multi thread we need to use local rng, each thread has his random number gen
            // To code this we use the seed 42 and we add the id of the thread, it change the seed
            // Sharing one global generator would create a bottleneck

            std::mt19937 local_rng(42 + thread_id); 
            std::exponential_distribution<double> dist(true_lambda);

            #pragma omp for
            for(int i = 0; i < n_max; ++i)
            {
                time_intervals[i] = dist(local_rng); // we can use the index i because we used resize
                res.n_values[i] = static_cast<double>(i + 1);
            }
        }

        // Here we use the lib numeric to compute the sum of time spend since t = 0
        // and & avoid us to copy the entier vector each time

        std::vector<double>& cumulative_sums = time_intervals;

        for(size_t i = 1; i < cumulative_sums.size(); ++i)
        {
            cumulative_sums[i] += cumulative_sums[i-1]; // time(i) depend on i-1
        }

        // Now that the sums are ready the division is independent for every point
        // We can fully utilize all cores again and apply our formula

        #pragma omp parallel for
        for(int i = 0; i < n_max; ++i)
        {
            res.estimated_lambda[i] = res.n_values[i] / cumulative_sums[i];
        }

        return res;
    }

}