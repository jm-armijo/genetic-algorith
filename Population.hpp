#ifndef __JM_GENETIC_ALGORITHM_POPULATION
#define __JM_GENETIC_ALGORITHM_POPULATION

#include <vector>
#include "Individual.hpp"

class Population {
    unsigned m_size;
    std::vector<Individual> m_individuals;
    
public:
    Population(unsigned size, unsigned num_args, unsigned num_genes);
    void evaluate(const std::vector<double>& expected);
    void select();
    void crossover();
    void mutate();
    double getTopScore() const;
    void printTopIndividual() const;
};

#endif // __JM_GENETIC_ALGORITHM_POPULATION
