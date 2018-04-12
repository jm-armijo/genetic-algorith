#include "Random.hpp"

std::random_device Random::m_rd;
std::mt19937 Random::m_rand_generator(Random::m_rd());

int Random::Uniform(int min, int max) {
    std::uniform_int_distribution<> u_rand_distr(min, max);
    return u_rand_distr(m_rand_generator);
}

int Random::Binomial(int max) {
    std::binomial_distribution<> u_bin_distr(max, 0.5);
    return u_bin_distr(m_rand_generator);
}

