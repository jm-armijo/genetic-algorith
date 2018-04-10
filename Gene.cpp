#include "Gene.hpp"
#include "Random.hpp"

Gene::Gene(unsigned gene_count, unsigned num_args) :
        m_gene_id(gene_count),
        m_num_args(num_args)
{
    m_value = _generateValue();
}

Gene::Gene() : m_value(1)
{
}

void Gene::mutate()
{
    m_value = _generateValue();
}

int Gene::_generateValue()
{
    int value;
    if (m_gene_id%2==0) {
        value = static_cast<unsigned>(Random::Uniform(0, m_num_args-1));
    } else {
        value = static_cast<unsigned>(Random::Uniform(0, 3));
    }
    return value;
}

unsigned Gene::getValue() const {
    return m_value;
}

std::string Gene::toString() const
{
    if (m_gene_id % 2 == 0) {
        return "x" + std::to_string(m_value);
    } else {
        unsigned value = m_value;
        if (value == 2) {
            value = 5;
        }
        return std::string(1, static_cast<char>(value+42));
    }
}

//   * = 42 = 0 + 42
//   + = 43 = 1 + 42
//   - = 45 = 3 + 42
//   / = 47 = 5 + 42
bool Gene::_isOperator(char op) const {
    unsigned op_val = static_cast<unsigned>(op) - 42;

    bool response = false;
    if (op_val == m_value) {
        response = true;
    } else if (op_val == 5 && m_value == 2) {
        response = true;
    }

    return response;
}

double Gene::evaluate(const std::vector<Gene>& genes, const std::vector<double> &args, double expected)
{
    unsigned num_genes = genes.size();
    bool error = false;
    double accumulator {0.0};

    if (num_genes <= 1) {
        error = true;
    } else {
        Gene op;
        for (unsigned i=0; i<genes.size() && !error; ++i) {
            if (i%2==0) {
                double value = args[genes[i].m_value];
                if (op._isOperator('+')) {
                    accumulator += value;
                } else if (op._isOperator('-')) {
                    accumulator -= value;
                } else if (op._isOperator('*')) {
                    accumulator *= value;
                } else if (op._isOperator('/') && value != 0) {
                    accumulator /= value;
                } else  {
                    error = true;
                }
            } else {
                op = genes[i];
            }
        }
    }

    if (error) {
        return std::numeric_limits<double>::max();
    } else {
        return std::abs(accumulator - expected);
    }
}
