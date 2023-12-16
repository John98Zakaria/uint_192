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
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN("Dividing by 10 results in the reminder of 1") {
            const auto res = uint192_lib::div_mod(a, 10);
            REQUIRE(res.reminder == 1);
            REQUIRE(res.quotient == ZERO);
        }

        THEN("Dividing by any number lower than UINT64_MAX results in the reminder of 1") {
            uint32_t divisor = GENERATE(take(100, random(static_cast<uint32_t>(2), UINT32_MAX)));
            const auto res = GENERATE_COPY(uint192_lib::div_mod(a, divisor));
            CAPTURE(divisor);
            REQUIRE(res.reminder == 1);
            REQUIRE(res.quotient == ZERO);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN(
            "Dividing by any number lower than UINT32_MAX results in the reminder of UINT64_MAX % number and result of "
            "UINT64_MAX/divisor") {
            uint32_t divisor = GENERATE(take(100, random(static_cast<uint32_t>(2), UINT32_MAX)));
            const auto res = GENERATE_COPY(uint192_lib::div_mod(a, divisor));
            CAPTURE(divisor);
            uint64_t reminder = (UINT64_MAX % divisor);
            REQUIRE(res.reminder == reminder);
            REQUIRE(res.quotient == uint192_lib::uint_192{UINT64_MAX / divisor});
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN("Dividing by 2 results is equivalent to a right shift") {
            const auto res = uint192_lib::div_mod(a, 2);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 63UL});
        }

        THEN("Dividing by 4 results is equivalent to a right shift of 2") {
            const auto res = uint192_lib::div_mod(a, 4);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 62UL});
        }

        THEN("Dividing by 8 results is equivalent to a right shift of 3") {
            const auto res = uint192_lib::div_mod(a, 8);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 61UL});
        }

        THEN("Dividing by 16 results is equivalent to a right shift of 4") {
            const auto res = uint192_lib::div_mod(a, 16);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1UL << 60UL});
        }

        THEN("Dividing by 10 works correctly") {
            const auto res = uint192_lib::div_mod(a, 10);
            REQUIRE(res.reminder == 6);
            REQUIRE(res.quotient == uint192_lib::uint_192{1844674407370955161UL});
        }
    }

    GIVEN("A uint_192 of value {0,UINT64_MAX,0}") {
        uint192_lib::uint_192 a{0, UINT64_MAX};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {10,10,0}") {
        uint192_lib::uint_192 a{10, 10, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }

        THEN("Dividing by 10 works correctly") {
            const auto res = uint192_lib::div_mod(a, 10UL);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == uint192_lib::uint_192{1, 1});
        }

        THEN("Dividing by 100 works correctly") {
            const auto res = uint192_lib::div_mod(a, 100UL);
            REQUIRE(res.reminder == 70);
            REQUIRE(res.quotient == uint192_lib::uint_192{1844674407370955161});
        }

        THEN("Dividing by 1000 works correctly") {
            const auto res = uint192_lib::div_mod(a, 1000UL);
            REQUIRE(res.reminder == 170);
            REQUIRE(res.quotient == uint192_lib::uint_192{184467440737095516});
        }

        THEN("Dividing by 10000 works correctly") {
            const auto res = uint192_lib::div_mod(a, 10000UL);
            REQUIRE(res.reminder == 6170);
            REQUIRE(res.quotient == uint192_lib::uint_192{18446744073709551});
        }

        THEN("Dividing by 100000 works correctly") {
            const auto res = uint192_lib::div_mod(a, 100000UL);
            REQUIRE(res.reminder == 16170);
            REQUIRE(res.quotient == uint192_lib::uint_192{1844674407370955});
        }

        THEN("Dividing by 100000000 works correctly") {
            const auto res = uint192_lib::div_mod(a, 100000000UL);
            REQUIRE(res.reminder == 95516170);
            REQUIRE(res.quotient == uint192_lib::uint_192{1844674407370});
        }

        THEN("Dividing by 100000000000 works correctly") {
            const auto res = uint192_lib::div_mod(a, 1000000000UL);
            REQUIRE(res.reminder == 95516170);
            REQUIRE(res.quotient == uint192_lib::uint_192{184467440737});
        }

        THEN("Dividing by UINT32_MAX works correctly") {
            const auto res = uint192_lib::div_mod(a, UINT32_MAX);
            REQUIRE(res.reminder == 20);
            REQUIRE(res.quotient == uint192_lib::uint_192{42949672970});
        }
    }

    GIVEN("A uint_192 of value {1,1,0}") {
        uint192_lib::uint_192 a{1, 1, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, 0, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};
        THEN("Dividing by 1 results in the identity") {
            const auto res = uint192_lib::div_mod(a, DIVISION_IDENTITY);
            REQUIRE(res.reminder == 0);
            REQUIRE(res.quotient == a);
        }
    }
}
