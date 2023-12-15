//
// Created by jn98zk on 13.12.23.
//
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

constexpr uint192_lib::uint_192 ZERO{0};

SCENARIO("Subtraction") {

    GIVEN("A uint_192 of value {1,0,0}") {
        uint192_lib::uint_192 a{1};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {2,0,0} should result in an underflow") {
            uint192_lib::uint_192 b{2, 0, 0};
            const auto result = a - b;
            REQUIRE(result == uint192_lib::uint_192{UINT64_MAX, UINT64_MAX, UINT64_MAX});
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {1,0,0} should result in an {UINT64_MAX, UINT64_MAX, 0}") {
            uint192_lib::uint_192 b{1, 0, 0};
            const auto result = a - b;
            REQUIRE(result == uint192_lib::uint_192{UINT64_MAX, UINT64_MAX, 0});
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {UINT64_MAX-1,0,0} should result in {1,0,0}") {
            uint192_lib::uint_192 b{UINT64_MAX - 1, 0, 0};

            const auto result = a - b;
            REQUIRE(result == uint192_lib::uint_192{1, 0, 0});
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {1,0,0} should result in {UINT64_MAX,0,0}") {
            uint192_lib::uint_192 b{1, 0, 0};

            const auto result = a - b;
            REQUIRE(result == uint192_lib::uint_192{UINT64_MAX, 0, 0});
        }
    }

    GIVEN("A uint_192 of value {1,1,0}") {
        uint192_lib::uint_192 a{1, 1, 0};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {0,1,0} should result in {1,0,0}") {
            uint192_lib::uint_192 b{0, 1, 0};

            const auto result = a - b;
            REQUIRE(result == uint192_lib::uint_192{1, 0, 0});
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, 0, 0};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {1,0,0} should reduce the result by 1") {
            const auto result = a - uint192_lib::uint_192{1};
            REQUIRE(result.parts[0] == UINT64_MAX -1Ul);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};

        THEN("Subtracting Zero should result in the original number") {
            const auto result = a - ZERO;
            REQUIRE(result == a);
        }

        THEN("Subtracting it from itself should result in zero") {
            const auto result = a - a;
            REQUIRE(result == ZERO);
        }

        THEN("Subtracting it from {1,0,0} should reduce the result by 1 in the correct position") {
            const auto result = a - uint192_lib::uint_192{1};
            REQUIRE(result.parts[0] == UINT64_MAX -1Ul);
            REQUIRE(result.parts[1] == UINT64_MAX);
        }

        THEN("Subtracting it from {1,1,0} should reduce the result by 1 in the correct positions") {
            const auto result = a - uint192_lib::uint_192{1,1};
            REQUIRE(result.parts[0] == UINT64_MAX -1Ul);
            REQUIRE(result.parts[1] == UINT64_MAX -1Ul);
        }
        THEN("Subtracting it from {1,UINT64_MAX,0} should be correct") {
            const auto result = a - uint192_lib::uint_192{1,UINT64_MAX};
            REQUIRE(result.parts[0] == UINT64_MAX -1Ul);
            REQUIRE(result.parts[1] == 0);
        }

    }
}
