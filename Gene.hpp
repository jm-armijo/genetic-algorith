#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <string>
#include <vector>

enum class Type {Operator, Variable, Constant};

class Gene {
private:
    static unsigned m_num_args;
    static unsigned m_num_genes;

    unsigned m_gene_id;
    Type m_type;
    unsigned m_value;

public:
    static void init(unsigned num_args, unsigned num_genes);
    Gene() {}
    Gene(unsigned gene_count);
    void mutate();
    static double fitnessDNA(const std::vector<Gene>& genes, const std::vector<double> &args, double expected);

    unsigned getValue() const;
    std::string toString() const;

private:
    Type _getNewType() const;
    int  _getNewValue() const;
    bool _isOperator(char op) const;
    double _fitness(const std::vector<Gene>& genes, const std::vector<double> &args) const;
    double _parseValue(const std::vector<double>& args) const;
    double _doOperation(double val1, double val2) const;
};

#endif // __JM_GENETIC_ALGORITHM_GENE
