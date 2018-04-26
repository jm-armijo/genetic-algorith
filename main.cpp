#include "Population.hpp"
#include <iostream>

double mistery_func(double x0, double x1) {
    return ((3*x0) + x1)/x0;
}

std::vector<std::vector<double>> getArgs()
{
    std::vector<std::vector<double>> args_list;

    args_list.push_back({7.0, 2.0});
    args_list.push_back({3.0, 4.0});

    return args_list;
}

int main() {
    int num_generations {10000};

    std::vector<std::vector<double>> &&args_list = getArgs();
    std::vector<double> expected_vals;

    for (unsigned i {0}; i<args_list.size(); ++i) {
        std::vector<double> args = args_list[i];
        expected_vals.push_back(mistery_func(args[0], args[1]));
    }

    unsigned num_args  = 2; //args_list[0].size();
    unsigned num_genes = 8;
    unsigned pop_size  = 15000;
    unsigned mutation_rate = 5; // 5%

    int i {0};
    Population pop(pop_size, num_args, num_genes, mutation_rate); // initialise
    do {
        for (unsigned j {0}; j < expected_vals.size(); ++j) {
            pop.fitness(args_list[j], expected_vals[j]);
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

