#include "Random.hpp"
#include <cassert>

std::random_device Random::m_rd;
std::mt19937 Random::m_rand_generator(Random::m_rd());

unsigned Random::UnsignedUniform(unsigned min, unsigned max) {
    std::uniform_int_distribution<> u_rand_distr(min, max);
    return static_cast<unsigned>(u_rand_distr(m_rand_generator));
}

// RightBinomial returns the right-hand side of a binomial distribution
// centered in 0
//
// Since std::binomial_distribution(n, 0.5) returns numbers in the range [0, n],
// we generate a binomial in the range [0, n*2+1]. For n = 3:
//
//           |  |
//        |  |  |  |
//  .  |  |  |  |  |  |  .
//  0  1  2  3  4  5  6  7
//
// Then we center the binomial in value 0:
//
//           |  |
//        |  |  |  |
//  .  |  |  |  |  |  |  .
// -4 -3 -2 -1  0  1  2  3
//
// And finally we invert the left-hand side:
//
//           |  |                     ||
//        |  |  |  |          ==>     ||  ||
//  .  |  |  |  |  |  |  .            ||  ||  ||  ..
//  3  2  1  0  0  1  2  3            0   1   2   3
//
unsigned Random::RightBinomial(int max) {
    // Binomial for increased range
    std::binomial_distribution<> u_bin_distr(2*max + 1, 0.5);
    int val = u_bin_distr(m_rand_generator);

    // Center binomial
    val -= (max + 1);

    // invert left hand side.
    if (val < 0) {
        val = std::abs(val+1);
    }

    return val;
}
