#include "Random.hpp"

std::random_device Random::m_rd;
std::mt19937 Random::m_rand_generator(Random::m_rd());

int Random::Uniform(int min, int max) {
    std::uniform_int_distribution<> u_rand_distr(min, max);
    return u_rand_distr(m_rand_generator);
}

