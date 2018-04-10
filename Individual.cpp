#include <iostream>
#include <limits>
#include "Individual.hpp"
#include "Random.hpp"

Individual::Individual(unsigned num_args, unsigned num_genes) :
        m_num_genes(num_genes)
{
    for (unsigned i {0}; i<m_num_genes; ++i) {
        m_genes.push_back(Gene(i, num_args));
    }
}

Individual::Individual(const Individual& ind1, const Individual& ind2)
{
    m_num_genes = ind1.m_num_genes;

    for (unsigned i {0}; i<m_num_genes; ++i) {
        int selector = Random::Uniform(0,1);
        if (selector == 0) {
            m_genes.push_back(ind1.m_genes[i]);
        } else {
            m_genes.push_back(ind2.m_genes[i]);
        }
    }
}

void Individual::print() const
{
    for (const auto &c : m_genes) {
        std::cout << c.toString();
    }
    std::cout << std::endl;
}

void Individual::mutate()
{
    int gen_number = Random::Uniform(0, m_num_genes-1);
    m_genes[gen_number].mutate();
}

bool Individual::operator < (const Individual& ind) const
{
    return (m_value < ind.m_value);
}

void Individual::evaluate(const std::vector<double> &args, double expected)
{
    m_value = Gene::evaluate(m_genes, args, expected);
}

double Individual::getValue() const
{
    return m_value;
}
