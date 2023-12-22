//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Compare to_base_10 to GMP") {
    auto number_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, UINT64_MAX)));
    auto number_GMP = GENERATE_COPY(from_uint192(number_uint192));

    CAPTURE(number_uint192.parts);

    const auto GMP_decimal = GENERATE_COPY(strip_leading_zeros(number_GMP.get_str(10)));

    const auto uint192_decimal = GENERATE_COPY(strip_leading_zeros(uint192_lib::to_base10_string(number_uint192)));

    REQUIRE(GMP_decimal == uint192_decimal);
}
