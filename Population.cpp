#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include "Population.hpp"
#include "Random.hpp"

Population::Population(unsigned size, unsigned num_args, unsigned num_genes, unsigned mutation_rate) :
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

bool Population::stop(double delta) const
{
    if (m_individuals[0].getValue() <= delta) {
        return true;
    } else {
        return false;
    }
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

    for (unsigned i {0}; i < m_individuals.size(); i+=2) {
        Individual child1(m_individuals[i], m_individuals[i+1]);
        Individual child2(m_individuals[i], m_individuals[i+1]);
        children.push_back(child1);
        children.push_back(child2);
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
