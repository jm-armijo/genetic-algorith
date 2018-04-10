#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <random>

enum class Type {Operator, Variable, Constant};

class Gene {
public:
    Gene(unsigned gene_count, unsigned num_args);

    unsigned getValue() const;
    std::string toString() const;
    void mutate();
    static double evaluate(const std::vector<Gene>& genes, const std::vector<double> &args, double expected);

private:
    Gene();
    Type _getNewType();
    int  _getNewValue();
    bool _isOperator(char op) const;
    unsigned m_gene_id;
    unsigned m_value;
    unsigned m_num_args;
    Type m_type;
};

#endif // __JM_GENETIC_ALGORITHM_GENE
