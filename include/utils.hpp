#pragma once // to counter the redefinition error, we tell to the compiler "if this file already been read one time during the compilation, don't read it a second time"
#include <vector>
#include <string>
#include <random>

// We have to set our toys for the playing field by defining our utils (Probability distribution, Output vector...)
// Knowing that some librairies have probably same variable names, we use namespace to counter that

namespace Utils {

    namespace Random
    {
        void init(unsigned int seed); // our random seed
        double exponential(double lambda); // exponential distribution
        double uniform(); // uniform ditribution
        int integer(int min, int max); // pick a random discret integer
    }

    namespace IO
    {

        // Our output vector
        struct TimeNumber
        {
            std::vector<double> time;
            std::vector<int> population;
        };
    
    // We avoid using a simple copy of our vector, it uses alot of memory, we prefer use pass by ref
    // with a const type to not modify our vector unintentionnaly, same for our file output

    // Moreover we'll need different saves because we'il encounter different type data, vectors, double, int and so on

        void save_raw_data(const std::vector<double>& x, 
                           const std::vector<double>& y, 
                           const std::string& filename,
                           const std::string& header);

        void save_traj(const std::vector<double>& t, 
                       const std::vector<double>& y, 
                       const std::string& filename, 
                       const std::string& header);

        void save_pop(const std::vector<double>& t, 
                      const std::vector<int>& pop, 
                      const std::string& filename);

    }
}
