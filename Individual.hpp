#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <random>
#include <vector>

class Individual {
    double m_value;
    unsigned m_num_genes;
    std::vector<char> m_genes;

public:
    Individual();
    Individual(const Individual& a, const Individual& b);
    void evaluate(double);
    void mutate();
    void print() const;
    bool operator < (const Individual& ind) const;
    double getValue() const;
    static unsigned calculateNumGenes(unsigned num_args = 0);

// Some utility methods
private:
    char _generate_rand_value() const;
    char _generate_rand_operator() const;

// Random number generation attributes
private:
    static std::random_device m_rd;
    static std::mt19937       m_rand_generator;
};

#endif // __JM_GENETIC_ALGORITHM_INDIVIDUAL
