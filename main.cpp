#include "Population.hpp"
#include <iostream>

double mistery_func(double x0, double x1) {
    return ((3*x0) + x1)/x0;
}

int main() {
    int num_generations {100};

    std::vector<std::vector<double>> args_list;
    std::vector<double> expected_vals;

    args_list.push_back({1.0, 1.0});
    args_list.push_back({3.0, 4.0});
    expected_vals.push_back(mistery_func(1.0, 1.0));
    expected_vals.push_back(mistery_func(3.0, 4.0));

    unsigned num_args  = args_list[0].size();
    unsigned num_genes = (3*num_args) + (1 - (3*num_args)%2);
    unsigned pop_size  = 10*num_genes;

    int i {0};
    Population pop(pop_size, num_args, num_genes); // initialise
    do {
        for (unsigned j {0}; j < expected_vals.size(); ++j) {
            pop.evaluate(args_list[j], expected_vals[j]);
        }

        pop.printTopIndividual();
        std::cout << pop.getTopScore() << std::endl;
        if (pop.getTopScore() == 0) {
            break;
        }

        pop.select(); // dummy call for now
        pop.crossover();
        pop.mutate();
        std::cout << "----------" << std::endl;
    } while (i++ < num_generations);

    return 0;
}

