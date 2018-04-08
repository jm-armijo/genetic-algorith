#include <iostream>
#include <limits>
#include <cmath>
#include "Individual.hpp"

std::random_device Individual::m_rd;
std::mt19937 Individual::m_rand_generator(Individual::m_rd());

Individual::Individual(unsigned num_dimensions) :
        m_num_dimensions(num_dimensions),
        m_value(std::numeric_limits<double>::max()),
        m_num_genes(calculateNumGenes())
{
    for (unsigned i {0}; i<m_num_genes; ++i) {
        if (i%2==0) {
            m_genes.push_back(Gene(Gene::Variable, m_num_dimensions));
        } else {
            m_genes.push_back(Gene(Gene::Operator));
        }
    }
}

Individual::Individual(const Individual& a, const Individual& b) : m_value(std::numeric_limits<double>::max())
{
    std::uniform_int_distribution<> gene_selector(0,1);
    m_num_genes = a.m_num_genes;

    for (unsigned i {0}; i<m_num_genes; ++i) {
        int selector = gene_selector(m_rand_generator);
        if (selector == 0) {
            m_genes.push_back(a.m_genes[i]);
        } else {
            m_genes.push_back(b.m_genes[i]);
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
    if (gen_number%2==0) {
        m_genes[gen_number] = Gene(Gene::Variable, m_num_dimensions);
    } else {
        m_genes[gen_number] = Gene(Gene::Operator);
    }
}

bool Individual::operator < (const Individual& ind) const
{
    return (m_value < ind.m_value);
}

void Individual::evaluate(double expected)
{
    m_value = Gene::evaluate(m_genes, expected);
}

unsigned Individual::calculateNumGenes(unsigned num_args)
{
    static unsigned num_genes = 5*num_args + (1 - (5*num_args)%2);
    return num_genes;
}

double Individual::getValue() const
{
    return m_value;
}
