#include <iostream>
#include <limits>
#include <cmath>
#include "Individual.hpp"

std::random_device Individual::m_rd;
std::mt19937 Individual::m_rand_generator(Individual::m_rd());

Individual::Individual() : m_num_genes(5), m_value(0) {
    for (unsigned i = 0; i<m_num_genes; ++i) {
        if (i%2==0)
            m_genes.push_back(_generate_rand_value());
        else
            m_genes.push_back(_generate_rand_operator());
    }
}

char Individual::_generate_rand_operator() const {
    std::uniform_int_distribution<> operator_distr(42,45);

    // * = 42
    // + = 43
    // - = 45
    // / = 47
    int op = operator_distr(m_rand_generator);
    if (op == 44)
        op = 47;

    return static_cast<char>(op);
}

char Individual::_generate_rand_value() const {
    std::uniform_int_distribution<> value_distr(48,57);

    return static_cast<char>(value_distr(m_rand_generator));
}

Individual::Individual(const Individual& a, const Individual& b) : m_num_genes(a.m_num_genes), m_value(0) {
    std::uniform_int_distribution<> gene_selector(0,1);

    for (unsigned i=0; i<m_num_genes; ++i) {
        int selector = gene_selector(m_rand_generator);
        if (selector == 0)
            m_genes.push_back(a.m_genes[i]);
        else
            m_genes.push_back(b.m_genes[i]);
    }
}

void Individual::print() const {
    for (auto &c : m_genes) {
        std::cout << c ;
    }
    std::cout << std::endl;
}

void Individual::mutate() {
    std::uniform_int_distribution<> gene_selector(0,m_num_genes-1);

    int gen_number = gene_selector(m_rand_generator);
    if (gen_number%2==0)
        m_genes[gen_number] = _generate_rand_value();
    else
        m_genes[gen_number] = _generate_rand_operator();
}

bool Individual::operator < (const Individual& ind) const {
    return (m_value < ind.m_value);
}

void Individual::evaluate(double expected) {
    double accumulator {0.0};
    char op = '+';

    for (unsigned i=0; i<m_num_genes; ++i) {
        if (i%2==0) {
            int value = static_cast<int>(m_genes[i]) - 48;
            if (op == '+')
                accumulator += value;
            else if (op == '-')
                accumulator -= value;
            else if (op == '*')
                accumulator *= value;
            else if (op == '/') {
                if (value == 0) {
                    m_value = std::numeric_limits<double>::max();
                    break;
                }
                accumulator /= value;
            }
        } else {
            op = m_genes[i];
        }
    }

    m_value = std::abs(accumulator - expected);
}

double Individual::getValue() const {
    return m_value;
}
