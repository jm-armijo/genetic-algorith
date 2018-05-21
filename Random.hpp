#ifndef __JM_GENETIC_ALGORITHM_RANDOM
#define __JM_GENETIC_ALGORITHM_RANDOM

#include <random>

class Random {
public:
    static int Uniform(int min, int max);
    static unsigned RightBinomial(int max);

private:
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_RANDOM
