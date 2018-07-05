#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <limits>
#include <vector>
#include "Gene.hpp"

class Individual {
    static unsigned m_num_args;
    static unsigned m_num_genes;

    unsigned m_num_evals;
    double m_value = std::numeric_limits<double>::max();
    std::vector<Gene> m_genes;

public:
    static void init(unsigned num_args, unsigned num_genes);
    Individual();
    Individual(const Individual& a, const Individual& b);
    void fitness(const std::vector<double> &args, double expected);
    void mutate();
    bool operator < (const Individual& ind) const;
    Individual operator()() const;
    double getValue() const;
    friend std::ostream& operator<<(std::ostream& o, const Individual& ind);
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
