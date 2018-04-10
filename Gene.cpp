#include "Gene.hpp"
#include "Random.hpp"

Gene::Gene(unsigned gene_count, unsigned num_args) :
        m_gene_id(gene_count),
        m_num_args(num_args)
{
    m_type  = _getNewType();
    m_value = _getNewValue();
}

Gene::Gene() : m_value(1)
{
}

void Gene::mutate()
{
    m_value = _getNewValue();
}

Type Gene::_getNewType()
{
    Type type;
    if (m_gene_id%2==0) {
        if (Random::Uniform(0,9) > 7) {
            type = Type::Constant;
        } else {
            type = Type::Variable;
        }
    } else {
        type = Type::Operator;
    }

    return type;
}

int Gene::_getNewValue()
{
    int value;
    if (m_type == Type::Variable) {
        value = static_cast<unsigned>(Random::Uniform(0, m_num_args-1));
    } else if (m_type == Type::Operator) {
        value = static_cast<unsigned>(Random::Uniform(0, 3));
    } else {
        value = static_cast<unsigned>(Random::Uniform(0, 9));
    }
    return value;
}

unsigned Gene::getValue() const {
    return m_value;
}

std::string Gene::toString() const
{
    if (m_type == Type::Variable) {
        return "x" + std::to_string(m_value);
    } else if (m_type == Type::Operator) {
        unsigned value = m_value;
        if (value == 2) {
            value = 5;
        }
        return std::string(1, static_cast<char>(value+42));
    } else {
        return std::string(1, static_cast<char>(m_value+48));
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
            if (genes[i].m_type == Type::Operator) {
                op = genes[i];
            } else {
                double value;
                if (genes[i].m_type == Type::Variable) {
                    value = args[genes[i].m_value];
                } else {
                    value = static_cast<double>(genes[i].m_value);
                }

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
            }
        }
    }

    if (error) {
        return std::numeric_limits<double>::max();
    } else {
        return std::abs(accumulator - expected);
    }
}
