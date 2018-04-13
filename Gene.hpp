#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <string>
#include <vector>

enum class Type {Operator, Variable, Constant};

class Gene {
private:
    unsigned m_gene_id;
    unsigned m_num_args;
    Type m_type;
    unsigned m_value;

public:
    Gene(unsigned gene_count, unsigned num_args);
    void mutate();
    static double fitness(const std::vector<Gene>& genes, const std::vector<double> &args, double expected);

    unsigned getValue() const;
    std::string toString() const;

private:
    Gene();
    Type _getNewType() const;
    int  _getNewValue() const;
    bool _isOperator(char op) const;
    double _evaluate(const std::vector<double>& args) const;
    static double _doOperation(const Gene& op, double val1, double val2);
};

#endif // __JM_GENETIC_ALGORITHM_GENE
