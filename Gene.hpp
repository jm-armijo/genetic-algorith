#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <random>

class Gene {
public:
    Gene() {}
    Gene(unsigned gene_count, unsigned num_args);

    unsigned getValue() const;
    void mutate();
    static double evaluate(const std::vector<Gene>& genes, double expected);

private:
    int _generateValue();
    bool _isOperator(char op) const;
    unsigned m_gene_id;
    unsigned m_value;
    unsigned m_num_args;

private: // Random number generation attributes
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_GENE
