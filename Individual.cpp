#include <iostream>
#include <limits>
#include "Individual.hpp"

std::random_device Individual::m_rd;
std::mt19937 Individual::m_rand_generator(Individual::m_rd());

Individual::Individual(unsigned num_args, unsigned num_genes) :
        m_num_args(num_args),
        m_num_genes(num_genes)
{
    for (unsigned i {0}; i<m_num_genes; ++i) {
        m_genes.push_back(Gene(i, m_num_args));
    }
}

Individual::Individual(const Individual& ind1, const Individual& ind2)
{
    std::uniform_int_distribution<> gene_selector(0,1);
    m_num_genes = ind1.m_num_genes;

    for (unsigned i {0}; i<m_num_genes; ++i) {
        int selector = gene_selector(m_rand_generator);
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
        std::cout << "<" << c.getValue() << ">";
    }
    std::cout << std::endl;
}

void Individual::mutate()
{
    std::uniform_int_distribution<> gene_selector(0,m_num_genes-1);

    int gen_number = gene_selector(m_rand_generator);
    m_genes[gen_number].mutate();
}

bool Individual::operator < (const Individual& ind) const
{
    return (m_value < ind.m_value);
}

void Individual::evaluate(double expected)
{
    m_value = Gene::evaluate(m_genes, expected);
}

double Individual::getValue() const
{
    return m_value;
}
