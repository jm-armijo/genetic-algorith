#ifndef __JM_GENETIC_ALGORITHM_POPULATION
#define __JM_GENETIC_ALGORITHM_POPULATION

#include <vector>
#include "Individual.hpp"

class Population {
private:
    unsigned m_size;
    unsigned m_mutation_rate;
    std::vector<Individual> m_individuals;
    
public:
    Population(unsigned size, unsigned num_args, unsigned num_genes, unsigned mutation_rate);
    void fitness(const std::vector<double> &args, double expected);
    void select();
    void crossover();
    void mutate();
    double getTopScore() const;
    void printTopIndividual() const;
};

#endif // __JM_GENETIC_ALGORITHM_POPULATION
