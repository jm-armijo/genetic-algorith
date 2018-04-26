#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <string>
#include <vector>

enum class Type {Operator, Variable, Constant};

class Gene {
private:
    unsigned m_gene_id;
    unsigned m_num_args;
    unsigned m_num_genes;
    Type m_type;
    unsigned m_value;

public:
    Gene(unsigned gene_count, unsigned num_args, unsigned num_genes);
    void mutate();
    static double fitness(const std::vector<Gene>& genes, const std::vector<double> &args, double expected);

    unsigned getValue() const;
    std::string toString() const;

private:
    Type _getNewType() const;
    int  _getNewValue() const;
    bool _isOperator(char op) const;
    double _evaluate(const std::vector<Gene>& genes, const std::vector<double> &args) const;
    double _parseValue(const std::vector<double>& args) const;
    double _doOperation(double val1, double val2) const;
};

#endif // __JM_GENETIC_ALGORITHM_GENE
