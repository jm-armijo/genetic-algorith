#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <cmath>
#include <random>
#include <vector>
#include "Gene.hpp"

class Individual {
    unsigned m_num_args;
    unsigned m_num_genes;
    double m_value = std::numeric_limits<double>::max();
    std::vector<Gene> m_genes;

public:
    Individual(unsigned num_args, unsigned num_genes);
    Individual(const Individual& a, const Individual& b);
    void evaluate(double);
    void mutate();
    void print() const;
    bool operator < (const Individual& ind) const;
    double getValue() const;

// Random number generation attributes
private:
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
