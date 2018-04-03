#ifndef __JM_GENETIC_ALGORITHM_POPULATION
#define __JM_GENETIC_ALGORITHM_POPULATION

#include <vector>
#include "Individual.hpp"

class Population {
    unsigned m_num_generation;
    unsigned m_size;
    std::vector<Individual> m_individuals;
    
public:
    Population(int);
    void evaluate();
    void select();
    void reproduce();
    void mutate();
    void discardInvalid();
    void printBest();
};

#endif // __JM_GENETIC_ALGORITHM_POPULATION
