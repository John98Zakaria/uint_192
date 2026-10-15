//
// Created by jn98zk on 26.11.23.
//
#include <catch2/catch_test_macros.hpp>

#include "catch2_uint192_generator.hpp"

TEST_CASE("Compare left shift implementation to GMP") {
    const auto num_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, 0)));
    const auto shift_by = GENERATE(take(100, random<uint64_t>(0, 192)));
    const auto num_GMP = from_uint192(num_uint192);

    REQUIRE(strip_leading_zeros(num_GMP.get_str(2)) == strip_leading_zeros(num_uint192.to_bin_string()));

    const auto num_uint192_result = num_uint192 << shift_by;

    // Bits shifted past the 192nd bit are dropped
    REQUIRE(from_uint192(num_uint192_result) == wrap_to_192_bits(mpz_class(num_GMP << shift_by)));
}
