//
// Created by jn98zk on 26.11.23.
//

#include "catch2_uint192_generator.hpp"

TEST_CASE("Compare left shift implementation to GMP") {
    const auto num_uint192 = GENERATE(take(120, randomUint192(UINT64_MAX, UINT64_MAX, 0)));
    const auto shift_by = GENERATE(take(100, random<uint64_t>(0, 192)));
    const auto num_GMP = from_uint192(num_uint192);

    REQUIRE(strip_leading_zeros(num_GMP.get_str(2)) == strip_leading_zeros(num_uint192.to_bin_string()));

    const auto num_uint192_result = num_uint192 << shift_by;
    const auto GMP_result_bits = strip_leading_zeros(mpz_class(num_GMP << shift_by).get_str(2));

    if (num_uint192_result == uint192_lib::uint_192{0, 0, 0}) {
        REQUIRE(true);
    }
    const auto uint192_result_bits = strip_leading_zeros(num_uint192_result.to_bin_string());
    bool isOk = GMP_result_bits.find(uint192_result_bits) != std::string::npos;

    REQUIRE(isOk);
}
