#include <cassert>
#include <cmath>
#include "Gene.hpp"
#include "Random.hpp"

Gene::Gene(unsigned gene_count, unsigned num_args, unsigned num_genes) :
        m_gene_id(gene_count),
        m_num_args(num_args),
        m_num_genes(num_genes)
{
    m_type  = _getNewType();
    m_value = _getNewValue();
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
    unsigned right_idx = 2*m_gene_id + 2;
    if (right_idx >= m_num_genes) {
        if (Random::Uniform(0,9) > 4) {
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
    bool printNl = true;
    if (m_gene_id > 0) {
        unsigned prev_depth = 1 + log2(m_gene_id);
        unsigned depth      = 1 + log2(m_gene_id + 1);

        if (prev_depth == depth) {
            printNl = false;
        }
    }

    std::string response;
    if (printNl) {
        response = "\n";
    }

    if (m_type == Type::Variable) {
        response += "x" + std::to_string(m_value);
    } else if (m_type == Type::Operator) {
        unsigned value = m_value;
        if (value == 2) {
            value = 5;
        }
        response += std::string(1, static_cast<char>(value+42));
    } else {
        response += std::to_string(m_value);
    }
    return response + " ";
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

double Gene::_parseValue(const std::vector<double>& args) const {
    double value;
    if (m_type == Type::Variable) {
        value = args[m_value];
    } else {
        value = static_cast<double>(m_value);
    }
    return value;
}

double Gene::_doOperation(double val1, double val2) const
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

double Gene::_fitness(const std::vector<Gene>& genes, const std::vector<double> &args) const
{
    double response;
    if (m_type == Type::Operator) {
        unsigned left_idx  = 2*m_gene_id + 1;
        unsigned right_idx = 2*m_gene_id + 2;

        assert(left_idx < genes.size());
        assert(right_idx < genes.size());

        double left_val  = genes[left_idx]._fitness(genes, args);
        double right_val = genes[right_idx]._fitness(genes, args);
        response = _doOperation(left_val, right_val);
    } else {
        response = _parseValue(args);
    }

    return response;
}

double Gene::fitnessDNA(const std::vector<Gene>& genes, const std::vector<double> &args, double expected)
{
    assert(genes.size() > 0);
    double value = genes[0]._fitness(genes, args);
    return std::abs(value - expected);
}
