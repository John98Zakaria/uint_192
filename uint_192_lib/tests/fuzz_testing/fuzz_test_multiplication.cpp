//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Compare multiplication to GMP") {
    const auto lhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    const auto rhs_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    const auto lhs_GMP = from_uint192(lhs_uint192);
    const auto rhs_GMP = from_uint192(rhs_uint192);

    REQUIRE(strip_leading_zeros(lhs_GMP.get_str(2)) == strip_leading_zeros(lhs_uint192.to_bin_string()));

    const auto result_uint192 = lhs_uint192 * rhs_uint192;
    const auto result_GMP = mpz_class(lhs_GMP * rhs_GMP);

    const auto GMP_result_bits = strip_leading_zeros(result_GMP.get_str(2));
    if (GMP_result_bits.length() > 192) {
        SKIP("RESULT is too big");
    }
    const auto uint192_result_bits = strip_leading_zeros(result_uint192.to_bin_string());

    REQUIRE(GMP_result_bits == uint192_result_bits);
}
