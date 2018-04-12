#include <iostream>
#include <algorithm>
#include <cmath>
#include "Population.hpp"
#include "Random.hpp"

Population::Population(unsigned size, unsigned num_args, unsigned num_genes) : m_size(size)
{
    for(unsigned i {0}; i<m_size; ++i) {
        Individual ind(num_args, num_genes);
        m_individuals.push_back(ind);
    }
}

void Population::evaluate(const std::vector<double> &args, double expected)
{
    for (auto &ind : m_individuals) {
        ind.evaluate(args, expected);
    }
}

void Population::select()
{
    // should be used to select individuals for crossover (instead of picking by order)
    std::vector<Individual> selected;

    for (unsigned i {0}; i < m_size; ++i) {
        int ind = Random::Binomial(2*m_size - 1) - m_size;
        if (ind < 0) {
            ind = std::abs(ind+1);
        }

        selected.push_back(m_individuals[ind]);
    }

    m_individuals = selected;
}

void Population::crossover()
{
    std::vector<Individual> individuals;

    for (unsigned i {0}; i < m_individuals.size()/2; i+=2) {
        for (unsigned j {0}; j<4; ++j) {
            Individual ind(m_individuals[j], m_individuals[j+1]);
            individuals.push_back(ind);
        }
    }
    m_individuals = individuals;
}

void Population::mutate()
{
    int individual = Random::Uniform(0, m_size - 1);
    m_individuals[individual].mutate();
}

double Population::getTopScore() const
{
    return m_individuals[0].getValue();
}

void Population::printTopIndividual() const
{
    m_individuals[0].print();
}
