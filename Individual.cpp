#include <algorithm>
#include <cassert>
#include <iostream>
#include "Individual.hpp"
#include "Random.hpp"

unsigned Individual::m_num_args = 0;
unsigned Individual::m_num_genes = 0;

void Individual::init(unsigned num_args, unsigned num_genes)
{
    m_num_args  = num_args;
    m_num_genes = num_genes;
}

Individual::Individual() :
        m_num_evals(0),
        m_value(0.0),
        m_genes(m_num_genes)
{
    auto i = 0u;
    std::generate(m_genes.begin(), m_genes.end(), [&](){return Gene(i++);});
}

Individual::Individual(const Individual& ind1, const Individual& ind2) :
        m_num_evals(0),
        m_value(0.0),
        m_genes(m_num_genes)
{
    auto i = 0u;
    std::generate(m_genes.begin(), m_genes.end(), [&](){
        return Random::UnsignedUniform(0,1) ? ind1.m_genes[i++] : ind2.m_genes[i++];
    });
}

std::ostream& operator<<(std::ostream& o, const Individual& ind)
{
    o << ind._flatten();
    return o;
}

std::string Individual::_flatten(unsigned idx) const
{
    std::string response;
    auto gene = m_genes[idx];
    if (gene.getType() == Type::Operator) {
        auto left_idx  = 2*gene.getIdx() + 1;
        auto right_idx = 2*gene.getIdx() + 2;

        assert(left_idx  < m_genes.size());
        assert(right_idx < m_genes.size());

        response = "(" + _flatten(left_idx) + gene.toString() + _flatten(right_idx) + ")";
    } else {
        response = gene.toString();
    }

    return response;
}

void Individual::mutate(unsigned mutation_rate)
{
    for (auto& gene : m_genes) {
        if(Random::UnsignedUniform(1, 100) <= mutation_rate) {
            gene.mutate();
        }
    }

    // Check that the individual's size remain unchanged after mutation
    assert (m_genes.size() == m_num_genes);
}

bool Individual::operator < (const Individual& ind) const
{
    return (m_value < ind.m_value);
}

Individual Individual::operator()() const
{
    return Individual();
}

void Individual::fitness(const std::vector<double> &args, double expected)
{
    auto fitness = std::abs(_evaluate(args) - expected);

    // Calculates average n values without the need of having all n values up front.
    // This prevents overflow for high values, but may lose precision.
    // Exampe for n = 3 (m_num_values = 2 when entering the function)
    //
    // x =  a + b + c   a + b   c   a + b   2   c    a + b
    //     ---------- = ----- + - = ----- * - + - =  -----
    //          3         3     3     2     3   3      2          c
    //                                              ------- * 2 + -
    //                                                 3          3

    // Increase number of values to get average
    ++m_num_evals;

    // Divide the old average by the new value of n
    m_value /= m_num_evals;

    // Then multiply the result by the old value of n
    m_value *= (m_num_evals - 1);

    // Finally add the new fitness divided by the new value of n
    auto new_value = fitness / m_num_evals;
    m_value += new_value;

    return;
}

double Individual::_evaluate(const std::vector<double> &args, unsigned idx) const
{
    double response;
    auto gene = m_genes[idx];
    if (gene.getType() == Type::Operator) {
        auto left_idx  = 2*gene.getIdx() + 1;
        auto right_idx = 2*gene.getIdx() + 2;

        assert(left_idx  < m_genes.size());
        assert(right_idx < m_genes.size());

        auto left_val  = _evaluate(args, left_idx);
        auto right_val = _evaluate(args, right_idx);
        response = gene.doOperation(left_val, right_val);
    } else {
        response = gene.getValue(args);
    }

    return response;
}

double Individual::getValue() const
{
    return m_value;
}
