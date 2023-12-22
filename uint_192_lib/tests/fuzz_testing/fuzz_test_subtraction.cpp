//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Compare subtraction to GMP") {
    auto lhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    auto rhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    auto lhs_GMP = from_uint192(lhs_uint192);
    auto rhs_GMP = from_uint192(rhs_uint192);
    // We implemented only unsigned arithmatic, so instead of skipping the test case we swap the two values
    if (rhs_GMP > lhs_GMP) {
        std::swap(lhs_uint192, rhs_uint192);
        lhs_GMP = from_uint192(lhs_uint192);
        rhs_GMP = from_uint192(rhs_uint192);
    }
    CAPTURE(lhs_uint192);
    CAPTURE(rhs_uint192);

    const auto result_uint192 = lhs_uint192 - rhs_uint192;
    const auto result_GMP = mpz_class(lhs_GMP - rhs_GMP);

    const auto GMP_result_bits = strip_leading_zeros(result_GMP.get_str(2));

    const auto uint192_result_bits = strip_leading_zeros(result_uint192.to_bin_string());
    CAPTURE(result_uint192);

    REQUIRE(GMP_result_bits == uint192_result_bits);
}
