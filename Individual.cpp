#include <iostream>
#include "Individual.hpp"
#include "Random.hpp"

Individual::Individual(unsigned num_args, unsigned num_genes) :
        m_num_genes(num_genes),
        m_num_evals(0),
        m_value(0)
{
    static int id = 0;
    m_id = id++;
    for (unsigned i {0}; i<m_num_genes; ++i) {
        m_genes.push_back(Gene(i, num_args, m_num_genes));
    }
    if (m_genes.size() != m_num_genes)
        std::cout << "genes dont match!" << std::endl;
}

Individual::Individual(const Individual& ind1, const Individual& ind2) :
        m_num_evals(0),
        m_value(0)
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
    
    if (m_genes.size() != m_num_genes)
        std::cout << "genes dont match!" << std::endl;
}

void Individual::print() const
{
    for (const auto &g : m_genes) {
        std::cout << g.toString();
    }
    std::cout << std::endl;
}

void Individual::mutate()
{
    int gen_number = Random::Uniform(0, m_num_genes-1);
    m_genes[gen_number].mutate();
    if (m_genes.size() != m_num_genes)
        std::cout << "genes dont match!" << std::endl;
}

bool Individual::operator < (const Individual& ind) const
{
    return (m_value < ind.m_value);
}

void Individual::fitness(const std::vector<double> &args, double expected)
{
    double fitness = Gene::fitness(m_genes, args, expected);

    ++m_num_evals;
    m_value /= m_num_evals;
    m_value *= (m_num_evals - 1);
    double new_value = fitness / m_num_evals;
    m_value += new_value;
    return;
}

double Individual::getValue() const
{
    return m_value;
}
