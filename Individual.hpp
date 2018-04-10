#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <cmath>
#include <vector>
#include "Gene.hpp"

class Individual {
    unsigned m_num_genes;
    double m_value = std::numeric_limits<double>::max();
    std::vector<Gene> m_genes;

public:
    Individual(unsigned num_args, unsigned num_genes);
    Individual(const Individual& a, const Individual& b);
    void evaluate(const std::vector<double> &args, double expected);
    void mutate();
    void print() const;
    bool operator < (const Individual& ind) const;
    double getValue() const;
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
