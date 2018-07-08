#include <cassert>
#include <cmath>
#include "Gene.hpp"
#include "Random.hpp"

unsigned Gene::m_num_args = 0;
unsigned Gene::m_num_genes = 0;

Gene::Gene(unsigned gene_count) :
        m_idx(gene_count)
{
    m_type  = _getNewType();
    m_value = _getNewValue();
}

void Gene::mutate()
{
    auto gene_id  = m_idx;
    auto num_args = m_num_args;
    auto type     = m_type;

    m_value = _getNewValue();

    // Confirm that the object invariants were not modified
    assert(gene_id  == m_idx);
    assert(num_args == m_num_args);
    assert(type     == m_type);
}

void Gene::init(unsigned num_args, unsigned num_genes)
{
    m_num_args  = num_args;
    m_num_genes = num_genes;
}

Type Gene::_getNewType() const
{
    Type type;
    auto right_idx = 2*m_idx + 2;
    if (right_idx >= m_num_genes) {
        if (Random::UnsignedUniform(0,9) > 4) {
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
    auto value = 0u;
    if (m_type == Type::Variable) {
        value = Random::UnsignedUniform(0, m_num_args-1);
    } else if (m_type == Type::Operator) {
        value = Random::UnsignedUniform(0, 3);
    } else {
        value = Random::UnsignedUniform(0, 9);
    }
    return value;
}

unsigned Gene::getValue() const
{
    return m_value;
}

Type Gene::getType() const
{
    return m_type;
}

unsigned Gene::getIdx() const
{
    return m_idx;
}

std::string Gene::toString() const
{
    std::string response;
    if (m_type == Type::Variable) {
        response = "x" + std::to_string(m_value);
    } else if (m_type == Type::Operator) {
        auto value = m_value == 2 ? 5 : m_value;
        response = std::string(1, static_cast<char>(value+42));
    } else {
        response = std::to_string(m_value);
    }
    return response;
}

//   * = 42 = 0 + 42
//   + = 43 = 1 + 42
//   - = 45 = 3 + 42
//   / = 47 = 5 + 42
bool Gene::_isOperator(char op) const {
    auto op_val = static_cast<unsigned>(op) - 42;

    auto response = false;
    if (op_val == m_value) {
        response = true;
    } else if (op_val == 5 && m_value == 2) {
        response = true;
    }

    return response;
}

double Gene::getValue(const std::vector<double>& args) const {
    assert(m_type != Type::Operator);

    double value;
    if (m_type == Type::Variable) {
        value = args[m_value];
    } else {
        value = static_cast<double>(m_value);
    }
    return value;
}

double Gene::doOperation(double val1, double val2) const
{
    double response;
    if (val1 == std::numeric_limits<double>::max()) {
        response = val1;
    } else if (val2 == std::numeric_limits<double>::max()) {
        response = val2;
    } else if (_isOperator('+')) {
        response = val1 + val2;
    } else if (_isOperator('-')) {
        response = val1 - val2;
    } else if (_isOperator('*')) {
        response = val1 * val2;
    } else if (_isOperator('/') && val2 != 0) {
        response = val1 / val2;
    } else  {
        response = std::numeric_limits<double>::max();
    }
    return response;
}
