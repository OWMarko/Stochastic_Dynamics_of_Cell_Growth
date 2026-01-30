#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

// We have our toys, now we have to use them to complet the playing ground
// Our projet involve some mathematical notions (probabities, generators...) and they need to be initialized

static std::mt19937 gen; // Our seed 
static bool is_initialized = false; // test

namespace Utils{

    namespace Random
    {
        void init(unsigned int seed)
        {
            gen.seed(seed);
            is_initialized = true;
        }

        double exponential(double lambda)
        {
            if(!is_initialized) init(42); // if we forget something in the main, the seed is a default seed
            std::exponential_distribution<> P(lambda);
            return P(gen); // Expo(lambda)
        }

        double uniform()
        {
            if (!is_initialized) init(42);
            std::uniform_real_distribution<> P(0.0, 1.0);
            return P(gen); // Uniform([0,1])
        }

        int integer(int min, int max)
        {
            if (!is_initialized) init(42);
            std::uniform_int_distribution<> P(min,max);
            return P(gen); // UnfiromInt([min,max])
        }
    }


// Finally there is a classic IO implementation
// First we create a optimized save for the simulation results (double + integer)

namespace IO {

        // We cannot pass a std::vector<int> (population) to a function expecting std::vector<double>

        void save_to_csv(const TimeNumber& data, const std::string& filename)
        {
            std::ofstream file(filename);
            
            if (!file.is_open())
            {
                std::cerr << "ERROR: Failed to open file " << filename << std::endl;
                return;
            }

            file << "time,population\n";

            // test with there is a dimension problem between our time and population span    

            size_t n = data.time.size(); 
            if (data.population.size() != n) 
            {
                std::cerr << "ERROR: Dimension mismatch between Time and Population vectors.\n";
                return;
            }

            for (size_t i = 0; i < n; ++i)
            {
                file << data.time[i] << "," << data.population[i] << "\n";
            }
            
            std::cout << "[CSV] Simulation results saved to: " << filename << std::endl;
        }

        // And we write a generic function for the data (Double X + Double Y)
        // It will be used for statistical inference where values are floats

        void save_raw_data(const std::vector<double>& x, 
                           const std::vector<double>& y, 
                           const std::string& filename,
                           const std::string& header) 
        {
            std::ofstream file(filename);
            
            if (!file.is_open()) 
            {
                std::cerr << "ERROR: Failed to open file " << filename << std::endl;
                return;
            }

            file << header << "\n";

            size_t n = x.size();
            if (y.size() != n) 
            {
                std::cerr << "ERROR: Dimension mismatch between X and Y vectors.\n";
                return;
            }

            for (size_t i = 0; i < n; ++i) 
            {
                file << x[i] << "," << y[i] << "\n";
            }
            
            std::cout << "[CSV] Analysis data saved to: " << filename << std::endl;
        }

        void save_traj(const std::vector<double>& t, 
                       const std::vector<double>& y, 
                       const std::string& filename, 
                       const std::string& header) 
        {

            save_raw_data(t, y, filename, header);
        }

        void save_pop(const std::vector<double>& t, 
                      const std::vector<int>& pop, 
                      const std::string& filename) 
        {
            std::vector<double> pop_d(pop.begin(), pop.end());
            save_raw_data(t, pop_d, filename, "time,population");
        }
    }
}