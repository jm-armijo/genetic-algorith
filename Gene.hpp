#ifndef __JM_GENETIC_ALGORITHM_GENE
#define __JM_GENETIC_ALGORITHM_GENE

#include <random>

class Gene {
public:
    enum Type {Variable, Operator};

    Gene() {}
    Gene(Type type, unsigned num_args = 0);

    unsigned getValue() const;
    bool isOperator(char op) const;
    static double evaluate(const std::vector<Gene>& genes, double expected);

private:
    unsigned m_value;

private: // Random number generation attributes
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_GENE
