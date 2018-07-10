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
    // Calculate fitness of each individual
    auto set_fitness = [&](Individual& ind){ind.fitness(args, expected);};
    std::for_each(m_individuals.begin(), m_individuals.end(), set_fitness);

    // Sort individuals by fitness (lower to higher, more fitted to less fitted)
    sort(m_individuals.begin(), m_individuals.end());
}

bool Population::checkEndCondition() const
{
    return (getTopScore() <= accepted_fitness);
}

std::vector<unsigned> Population::select()
{
    std::vector<unsigned> selected(m_size);
    std::generate(selected.begin(), selected.end(), [&](){ return Random::RightBinomial(m_size);});
    return selected;
}

void Population::crossover(const std::vector<unsigned>& selected)
{
    std::vector<Individual> children;
    // Creates two children (index, index+1) per each pair of parents (i, i+1)
    for (auto i = 0u; i < selected.size(); i+=2) {
        // Get the indexes of the parents
        auto idx1 = selected[i];
        auto idx2 = selected[i+1];

        // Get the actual parents
        auto parent1 = m_individuals[idx1];
        auto parent2 = m_individuals[idx2];

        // Add two children from these two parents
        children.push_back(Individual(parent1, parent2));
        children.push_back(Individual(parent1, parent2));
    }

    // Check that we have as many children as parents
    assert(m_individuals.size() == children.size());

    // Replace the parents with their children
    m_individuals = std::move(children);
}

void Population::mutate()
{
    for (auto& ind : m_individuals) {
        ind.mutate(m_mutation_rate);
    }
}

// Utility functions

double Population::getTopScore() const
{
    return m_individuals[0].getValue();
}

void Population::printTopIndividual() const
{
    std::cout << m_individuals[0] << std::endl;
}
