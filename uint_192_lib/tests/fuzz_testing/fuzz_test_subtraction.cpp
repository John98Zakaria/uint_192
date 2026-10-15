//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"
#include <catch2/catch_test_macros.hpp>

// Results below zero wrap around, exactly like the built-in unsigned types
void compare_subtraction_to_GMP(const uint192_lib::uint_192 &lhs_uint192, const uint192_lib::uint_192 &rhs_uint192) {
    CAPTURE(lhs_uint192);
    CAPTURE(rhs_uint192);
    const auto result_uint192 = lhs_uint192 - rhs_uint192;
    CAPTURE(result_uint192);

    REQUIRE(from_uint192(result_uint192) == wrap_to_192_bits(from_uint192(lhs_uint192) - from_uint192(rhs_uint192)));
}

TEST_CASE("Compare subtraction to GMP") {
    const auto lhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    const auto rhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    compare_subtraction_to_GMP(lhs_uint192, rhs_uint192);
}

TEST_CASE("Compare subtraction to GMP with edge values") {
    const auto lhs_uint192 = GENERATE(take(120, edgeBiasedUint192()));
    const auto rhs_uint192 = GENERATE(take(120, edgeBiasedUint192()));
    compare_subtraction_to_GMP(lhs_uint192, rhs_uint192);
}
