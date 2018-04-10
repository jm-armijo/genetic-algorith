#include "Population.hpp"
#include <iostream>

int main() {
    int num_generations {3};
    std::vector<double> expected {4.0};
    std::vector<double> args {2.0, 2.0};

    unsigned num_args  = args.size();
    unsigned num_genes = 3;
    unsigned pop_size  = 10*num_genes;

    int i {0};
    Population pop(pop_size, num_args, num_genes); // initialise
    do {
        pop.evaluate(expected);

        if (pop.getTopScore() == 0) {
            pop.printTopIndividual();
            break;
        }

        pop.select(); // dummy call for now
        pop.crossover();
        pop.mutate();
        std::cout << "----------" << std::endl;
    } while (i++ < num_generations);

    return 0;
}
