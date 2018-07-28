#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <string>
#include <vector>

enum class Type {Operator, Variable, Constant};

class Gene {
public:
    static void init(unsigned num_args, unsigned num_genes);
    Gene() {}
    Gene(unsigned gene_count);
    void mutate();

    unsigned getValue() const;
    Type getType() const;
    unsigned getIdx() const;
    std::string toString() const;
    double getValue(const std::vector<double>& args) const;
    double doOperation(double val1, double val2) const;

private:
    static unsigned m_num_args;
    static unsigned m_num_genes;

    unsigned m_idx;
    Type m_type;
    unsigned m_value;

    Type _getNewType() const;
    int  _getNewValue() const;
    bool _isOperator(char op) const;
};


#endif // __JM_GENETIC_ALGORITHM_GENE
