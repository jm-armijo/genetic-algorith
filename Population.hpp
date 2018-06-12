#ifndef __JM_GENETIC_ALGORITHM_POPULATION
#define __JM_GENETIC_ALGORITHM_POPULATION

#include <vector>
#include "Individual.hpp"

class Population {
private:
    unsigned m_size;
    unsigned m_mutation_rate;
    const static double accepted_fitness;
    std::vector<Individual> m_individuals;
    
public:
    Population(unsigned size, unsigned mutation_rate);
    //    |
    //    V
    void fitness(const std::vector<double> &args, double expected); // <--+
    //    |                                                         //    |
    //    V                                                         //    |
    bool checkEndCondition() const; // --> End                      //    |
    //    | No         // Yes                                       //    |
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
