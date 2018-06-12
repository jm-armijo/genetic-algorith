#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include "Population.hpp"
#include "Random.hpp"

const double Population::accepted_fitness = 0.00001;

Population::Population(unsigned size, unsigned mutation_rate) :
        m_size(size),
        m_mutation_rate(mutation_rate)
{
    m_individuals.resize(m_size);
    std::generate(m_individuals.begin(), m_individuals.end(), Individual());
}

void Population::fitness(const std::vector<double> &args, double expected)
{
    std::for_each(m_individuals.begin(), m_individuals.end(), [&](Individual& ind){ind.fitness(args, expected);});
    sort(m_individuals.begin(), m_individuals.end());
}

bool Population::checkEndCondition() const
{
    return (getTopScore() <= accepted_fitness);
}

void Population::select()
{
    std::vector<Individual> selected(m_size);
    std::generate(selected.begin(), selected.end(), [&](){ return m_individuals[Random::RightBinomial(m_size)];});
    m_individuals = std::move(selected);
}

void Population::crossover()
{
    std::vector<Individual> children;
    // Creates two children (index, index+1) per each pair of parents (i, i+1)
    for (unsigned i {0}; i < m_individuals.size(); ++i) {
        // i=0 -> index=0 ; i=1 -> index=0
        unsigned index {i/2*2};
        children.push_back(Individual(m_individuals[index], m_individuals[index+1]) );
    }
    assert(m_individuals.size() == children.size());
    m_individuals = std::move(children);
}

void Population::mutate()
{
    for (auto& ind : m_individuals) {
        if(Random::UnsignedUniform(1, 100) <= m_mutation_rate) {
            ind.mutate();
        }
    }
}

// Utility functions

double Population::getTopScore() const
{
    return m_individuals[0].getValue();
}

void Population::printTopIndividual() const
{
    m_individuals[0].print();
}
