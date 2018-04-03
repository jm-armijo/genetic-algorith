#include <iostream>
#include <algorithm>
#include "Population.hpp"

Population::Population(int size) : m_num_generation(1), m_size(size) {
    for(unsigned i=0; i<m_size; ++i) {
        Individual ind;
        m_individuals.push_back(ind);
    }
}

void Population::evaluate() {
    for (auto &ind : m_individuals) {
        ind.evaluate(4);
    }
    std::sort(m_individuals.begin(), m_individuals.end());
    std::cout << "Best score " << m_individuals[0].get_value() << " by ";
    m_individuals[0].print();
}

void Population::select() {
    // should be used to select individuals for crossover (instead of picking by order)
}

void Population::reproduce() {
    std::vector<Individual> individuals;

    for (unsigned i = 0; i < m_individuals.size()/2; i+=2) {
        for (unsigned i=0; i<4; ++i) {
            Individual ind(m_individuals[i], m_individuals[i+1]);
            individuals.push_back(ind);
        }
    }
    m_individuals = individuals;
    ++m_num_generation;
}

void Population::mutate() {

    std::random_device rd;
    std::mt19937 rand_generator(rd());
    std::uniform_int_distribution<> individual_distr(0, m_size - 1);

    int individual = individual_distr(rand_generator);
    m_individuals[individual].mutate();
}
