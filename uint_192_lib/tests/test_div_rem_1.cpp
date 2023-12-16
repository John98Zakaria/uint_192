//
// Created by jn98zk on 15.12.23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <uint_192.hpp>

constexpr uint64_t DIVISION_IDENTITY{1};
constexpr uint192_lib::uint_192 ZERO = uint192_lib::uint_192{0, 0, 0};

SCENARIO("Division by uint64_t") {

    GIVEN("A uint_192 of value {1,0,0}") {
        uint192_lib::uint_192 a{1};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN("Dividing by 10 results in the reminder of 1") {
            const auto res = uint192_lib::div1_rem(a, 10);
            REQUIRE(res.reminder == 1);
            REQUIRE(res.quotient == ZERO);
        }

        THEN("Dividing by any number lower than UINT64_MAX results in the reminder of 1") {
            uint64_t divisor = GENERATE(take(100, random(2UL, UINT64_MAX)));
            const auto res = GENERATE_COPY(uint192_lib::div1_rem(a, divisor));
            CAPTURE(divisor);
            REQUIRE(res.reminder == 1);
            REQUIRE(res.quotient == ZERO);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN(
            "Dividing by any number lower than UINT64_MAX results in the reminder of UINT64_MAX % number and result of "
            "UINT64_MAX/divisor") {
            uint64_t divisor = GENERATE(take(100, random(2UL, UINT64_MAX)));
            const auto res = GENERATE_COPY(uint192_lib::div1_rem(a, divisor));
            CAPTURE(divisor);
            uint64_t reminder = (UINT64_MAX % divisor);
            REQUIRE(res.reminder == reminder);
            REQUIRE(res.quotient == uint192_lib::uint_192{UINT64_MAX / divisor});
        }

        // This test case was found by the generator above
        THEN("Dividing by 7487266968199916935Ul should work") {
            uint64_t divisor = 7487266968199916935Ul;
            const auto res = uint192_lib::div1_rem(a, divisor);
            CAPTURE(divisor);
            uint64_t reminder = UINT64_MAX % divisor;
            REQUIRE(res.reminder == reminder);
            REQUIRE(res.quotient == uint192_lib::uint_192{UINT64_MAX / divisor});
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN("Dividing by 2 results is equivalent to a right shift") {
            const auto res = uint192_lib::div1_rem(a, 2);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 63UL});
        }

        THEN("Dividing by 4 results is equivalent to a right shift of 2") {
            const auto res = uint192_lib::div1_rem(a, 4);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 62UL});
        }

        THEN("Dividing by 8 results is equivalent to a right shift of 3") {
            const auto res = uint192_lib::div1_rem(a, 8);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 61UL});
        }

        THEN("Dividing by 16 results is equivalent to a right shift of 4") {
            const auto res = uint192_lib::div1_rem(a, 16);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 60UL});
        }

        THEN("Dividing by 10 works correctly") {
            const auto res = uint192_lib::div1_rem(a, 10);
            REQUIRE(res.reminder == 6);
            REQUIRE(res.quotient == uint192_lib::uint_192{1844674407370955161UL});
        }
    }

    GIVEN("A uint_192 of value {0,UINT64_MAX,0}") {
        uint192_lib::uint_192 a{0, UINT64_MAX};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {1,1,0}") {
        uint192_lib::uint_192 a{1, 1, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, 0, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div1_rem(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }
}
