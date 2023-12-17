//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Compare div_mod to GMP") {
    auto num_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    auto divisor = GENERATE(take(120, random(static_cast<uint32_t>(0), UINT32_MAX)));
    auto num_GMP = from_uint192(num_uint192);

    CAPTURE(num_uint192);
    CAPTURE(divisor);

    const auto result_uint192 = uint192_lib::div_mod(num_uint192, divisor);
    const auto quotient_gmp = mpz_class(num_GMP / divisor);
    const auto reminder_gmp = mpz_class(num_GMP % divisor).get_ui();

    const auto GMP_result_bits = strip_leading_zeros(quotient_gmp.get_str(2));

    const auto uint192_result_bits = strip_leading_zeros(result_uint192.quotient.to_bin_string());
    CAPTURE(result_uint192);

    REQUIRE(GMP_result_bits == uint192_result_bits);

    REQUIRE(reminder_gmp == result_uint192.reminder);
}
