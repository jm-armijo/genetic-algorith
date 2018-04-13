#include <cassert>
#include "Gene.hpp"
#include "Random.hpp"

Gene::Gene(unsigned gene_count, unsigned num_args) :
        m_gene_id(gene_count),
        m_num_args(num_args)
{
    m_type  = _getNewType();
    m_value = _getNewValue();
}

Gene::Gene() :
        m_gene_id(0),
        m_num_args(0),
        m_type(Type::Operator),
        m_value(1)
{
}

void Gene::mutate()
{
    unsigned gene_id  = m_gene_id;
    unsigned num_args = m_num_args;
    Type type         = m_type;

    m_value = _getNewValue();

    assert(gene_id  == m_gene_id);
    assert(num_args == m_num_args);
    assert(type     == m_type);
}

Type Gene::_getNewType() const
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

int Gene::_getNewValue() const
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

double Gene::_evaluate(const std::vector<double>& args) const {
    double value;
    if (m_type == Type::Variable) {
        value = args[m_value];
    } else {
        value = static_cast<double>(m_value);
    }
    return value;
}

double Gene::_doOperation(const Gene& op, double val1, double val2)
{
    double response;
    if (op._isOperator('+')) {
        response = val1 + val2;
    } else if (op._isOperator('-')) {
        response = val1 - val2;
    } else if (op._isOperator('*')) {
        response = val1 * val2;
    } else if (op._isOperator('/') && val2 != 0) {
        response = val1 / val2;
    } else  {
        response = std::numeric_limits<double>::max();
    }
    return response;
}

double Gene::fitness(const std::vector<Gene>& genes, const std::vector<double> &args, double expected)
{
    unsigned num_genes = genes.size();
    bool error = false;
    double accumulator {0.0};

    Gene op;
    for (unsigned i {0}; i<num_genes && !error; ++i) {
        if (genes[i].m_type == Type::Operator) {
            op = genes[i];
        } else {
            double value = genes[i]._evaluate(args);

            accumulator = _doOperation(op, accumulator, value);
            if (accumulator == std::numeric_limits<double>::max()) {
                error = true;
            }
        }
    }

    if (error) {
        return std::numeric_limits<double>::max();
    } else {
        return std::abs(accumulator - expected);
    }
}
