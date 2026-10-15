//
// Created by jn98zk on 10.12.23.
//

#ifndef MY_UINT192_CATCH2_UINT192_GENERATOR_HPP
#define MY_UINT192_CATCH2_UINT192_GENERATOR_HPP

#include <catch2/generators/catch_generators_all.hpp>
#include <gmpxx.h>
#include <iostream>
#include <random>
#include <uint_192.hpp>

struct Uint192_Generator : public Catch::Generators::IGenerator<uint192_lib::uint_192> {
    std::minstd_rand m_rand{std::random_device{}()};
    std::uniform_int_distribution<uint64_t> low_dist{0, UINT64_MAX};
    std::uniform_int_distribution<uint64_t> mid_dist{0, UINT64_MAX};
    std::uniform_int_distribution<uint64_t> high_dist{0, UINT64_MAX};
    uint192_lib::uint_192 current_number{};

    Uint192_Generator(uint64_t low_max, uint64_t min_max, uint64_t high_max) {
        low_dist = std::uniform_int_distribution<uint64_t>{0, low_max};
        mid_dist = std::uniform_int_distribution<uint64_t>{0, min_max};
        high_dist = std::uniform_int_distribution<uint64_t>{0, high_max};
        current_number = uint192_lib::uint_192{low_dist(m_rand), mid_dist(m_rand), high_dist(m_rand)};
    }

    uint192_lib::uint_192 const &get() const override {
        return current_number;
    }
    bool next() override {
        current_number = uint192_lib::uint_192{low_dist(m_rand), mid_dist(m_rand), high_dist(m_rand)};
        return true;
    }
};

Catch::Generators::GeneratorWrapper<uint192_lib::uint_192> randomUint192(uint64_t low_max, uint64_t min_max,
                                                                         uint64_t high_max) {
    return {new Uint192_Generator(low_max, min_max, high_max)};
}

// Uniformly random parts almost never hit the values where carries and borrows go wrong (0, UINT64_MAX, ...),
// so this generator picks each part from a list of such edge values half of the time.
struct Edge_Biased_Uint192_Generator : public Catch::Generators::IGenerator<uint192_lib::uint_192> {
    static constexpr std::array<uint64_t, 8> EDGE_VALUES{
        0, 1, 2, UINT32_MAX, static_cast<uint64_t>(UINT32_MAX) + 1, UINT64_MAX / 2 + 1, UINT64_MAX - 1, UINT64_MAX};
    std::minstd_rand m_rand{std::random_device{}()};
    std::uniform_int_distribution<uint64_t> part_dist{0, UINT64_MAX};
    std::uniform_int_distribution<size_t> edge_index_dist{0, EDGE_VALUES.size() - 1};
    std::bernoulli_distribution use_edge_value{0.5};
    uint192_lib::uint_192 current_number{};

    Edge_Biased_Uint192_Generator() {
        next();
    }

    uint64_t next_part() {
        return use_edge_value(m_rand) ? EDGE_VALUES[edge_index_dist(m_rand)] : part_dist(m_rand);
    }

    uint192_lib::uint_192 const &get() const override {
        return current_number;
    }
    bool next() override {
        current_number = uint192_lib::uint_192{next_part(), next_part(), next_part()};
        return true;
    }
};

Catch::Generators::GeneratorWrapper<uint192_lib::uint_192> edgeBiasedUint192() {
    return {new Edge_Biased_Uint192_Generator()};
}

mpz_class from_uint192(const uint192_lib::uint_192 &item) {
    mpq_class lower(item.parts[0]);
    mpq_class middle(item.parts[1]);
    middle <<= UINT64_WIDTH;
    mpq_class upper(item.parts[2]);
    upper <<= (UINT64_WIDTH * 2);

    return mpz_class(lower + middle + upper);
}

// uint_192 arithmetic wraps around, so GMP results have to be reduced to the lower 192 bits before comparing
mpz_class wrap_to_192_bits(const mpz_class &value) {
    mpz_class result;
    mpz_fdiv_r_2exp(result.get_mpz_t(), value.get_mpz_t(), 192);
    return result;
}

std::string strip_leading_zeros(const std::string &input) {
    const auto index_of_significant_bit = input.find('1');
    if (index_of_significant_bit == std::string::npos) {
        return "";
    }
    return input.substr(index_of_significant_bit);
}

#endif // MY_UINT192_CATCH2_UINT192_GENERATOR_HPP
