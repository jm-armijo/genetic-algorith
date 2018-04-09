#include <iostream>
#include <algorithm>
#include "Population.hpp"
#include "Random.hpp"

Population::Population() : m_num_generation(1)
{
    unsigned num_args = 2;
    unsigned num_genes = 11;

    // Population should be 10*num_genes
    m_size = 10*num_genes;

    for(unsigned i {0}; i<m_size; ++i) {
        Individual ind(num_args, num_genes);
        m_individuals.push_back(ind);
    }
}

void Population::evaluate(const std::vector<double>& expected)
{
    for (auto &val : expected) {
        for (auto &ind : m_individuals) {
            ind.evaluate(val);
        }
    }
    std::sort(m_individuals.begin(), m_individuals.end());
    std::cout << "Best score " << m_individuals[0].getValue() << " by ";
    m_individuals[0].print();
}

void Population::select()
{
    // should be used to select individuals for crossover (instead of picking by order)
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
    ++m_num_generation;
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
