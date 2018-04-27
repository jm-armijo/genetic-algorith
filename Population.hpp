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
    //    |
    //    V
    void fitness(const std::vector<double> &args, double expected); // <--+
    //    |                                                         //    |
    //    V                                                         //    |
    bool stop(double delta) const; // --> End                       //    |    
    //    | No                     // Yes                           //    |
    //    V                                                         //    |
    void select();                                                  //    |
    //    |                                                         //    |
    //    V                                                         //    |
    void crossover();                                               //    | 
    //    |                                                         //    |
    //    V                                                         //    |
    void mutate();                                                  //    |
    //    |                                                         //    |
    //    +---------------------------------------------------------------+



    double getTopScore() const;
    void printTopIndividual() const;
};

#endif // __JM_GENETIC_ALGORITHM_POPULATION
