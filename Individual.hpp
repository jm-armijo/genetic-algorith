#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <limits>
#include <vector>
#include "Gene.hpp"

class Individual {
public:
    static void init(unsigned num_args, unsigned num_genes);
    Individual();
    Individual(const Individual& a, const Individual& b);
    void fitness(const std::vector<double> &args, double expected);
    void mutate(unsigned mutation_rate);
    double getValue() const;

    bool operator < (const Individual& ind) const;
    Individual operator()() const;
    friend std::ostream& operator<<(std::ostream& o, const Individual& ind);

private:
    static unsigned m_num_args;
    static unsigned m_num_genes;

    unsigned m_num_evals;
    double m_value = std::numeric_limits<double>::max();
    std::vector<Gene> m_genes;

    // Converts an Individual (sub)tree into its flattened string representation.
    std::string _flatten(unsigned idx = 0) const;

    // Evaluates an Individual (sub)tree.
    double _evaluate(const std::vector<double> &args, unsigned idx = 0) const;
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
