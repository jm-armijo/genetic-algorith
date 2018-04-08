#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <random>
#include <vector>
#include "Gene.hpp"

class Individual {
    unsigned m_num_dimensions;
    double m_value;
    unsigned m_num_genes;
    std::vector<Gene> m_genes;

public:
    Individual(unsigned num_dimensions);
    Individual(const Individual& a, const Individual& b);
    void evaluate(double);
    void mutate();
    void print() const;
    bool operator < (const Individual& ind) const;
    double getValue() const;
    static unsigned calculateNumGenes(unsigned num_args = 0);

// Random number generation attributes
private:
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
