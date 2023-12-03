//
// Created by jn98zk on 26.11.23.
//

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

TEST_CASE("Shifting it by UINT64_MAX bits returns an empty result") {
    auto result = uint192_lib::uint_192{1} << UINT64_MAX;
    REQUIRE(result.parts[0] == 0);
    REQUIRE(result.parts[1] == 0);
    REQUIRE(result.parts[2] == 0);
}

SCENARIO("Shifting left works") {

    GIVEN("A uint_192 of value {1,0,0}") {
        uint192_lib::uint_192 a{1};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == 2);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == 4);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == 1 << 10);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 1);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bits works") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 1);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 2);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 4);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 1 << 10);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 1);
        }

        THEN("Shifting it by 128 bit returns an empty result") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 2);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 4);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 1 << 10);
        }

        THEN("Shifting it by 64 bits returns an empty result") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bit returns an empty result") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {1,1,0}") {
        uint192_lib::uint_192 a{1, 1, 0};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == 2);
            REQUIRE(result.parts[1] == 2);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == 4);
            REQUIRE(result.parts[1] == 4);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == 1 << 10);
            REQUIRE(result.parts[1] == 1 << 10);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bit works") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 1);
            REQUIRE(result.parts[2] == 1);
        }

        THEN("Shifting it by 128 bit overflows correctly") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 1);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, 0, 0};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == UINT64_MAX << 1);
            REQUIRE(result.parts[1] == UINT64_MAX >> 63);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == UINT64_MAX << 2);
            REQUIRE(result.parts[1] == UINT64_MAX >> 62);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == UINT64_MAX << 10);
            REQUIRE(result.parts[1] == UINT64_MAX >> 54);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bit works") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bit works correctly") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == UINT64_MAX);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};

        THEN("Shifting it by 1 bit works") {
            auto result = a << 1;
            REQUIRE(result.parts[0] == UINT64_MAX << 1);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 63);
        }

        THEN("Shifting it by 2 bits works") {
            auto result = a << 2;
            REQUIRE(result.parts[0] == UINT64_MAX << 2);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 62);
        }

        THEN("Shifting it by 10 bits works") {
            auto result = a << 10;
            REQUIRE(result.parts[0] == UINT64_MAX << 10);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 54);
        }

        THEN("Shifting it by 64 bit works") {
            auto result = a << UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX);
        }

        THEN("Shifting it by 128 bit works correctly") {
            auto result = a << UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == UINT64_MAX);
        }

        THEN("Shifting it by 192 bits returns an empty result") {
            auto result = a << UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }
}
