#ifndef __JM_GENETIC_ALGORITHM_INDIVIDUAL
#define __JM_GENETIC_ALGORITHM_INDIVIDUAL

#include <random>
#include <vector>

class Individual {
    unsigned m_num_genes;
    std::vector<char> m_genes;
    double m_value;

public:
    Individual();
    Individual(const Individual& a, const Individual& b);
    void mutate();
    void evaluate(double);
    double get_value() const;
    void print() const;
    bool operator < (const Individual& ind) const;

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
