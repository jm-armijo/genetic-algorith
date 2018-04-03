#include "Population.hpp"
#include <iostream>

int main() {
    int num_generations = 3;

    int i = 0;
    Population pop(8);
    do {
        pop.evaluate();
        pop.reproduce();
        pop.mutate();
        std::cout << "----------" << std::endl;
    } while (i++ < num_generations);

    return 0;
}
