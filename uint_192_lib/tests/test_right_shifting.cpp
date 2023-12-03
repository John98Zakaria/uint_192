//
// Created by jn98zk on 26.11.23.
//

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

constexpr uint64_t UINT_64_LEFT_MOST_1 = 1UL << 63;

TEST_CASE("Shifting right by UINT64_MAX bits returns an empty result") {
    auto result = uint192_lib::uint_192{1} >> UINT64_MAX;
    REQUIRE(result.parts[0] == 0);
    REQUIRE(result.parts[1] == 0);
    REQUIRE(result.parts[2] == 0);
}

SCENARIO("Shifting right works") {

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};
        THEN("Shifting it by 1 bit works") {
            auto result = a >> 1;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[2] == 0);
        }
        THEN("Shifting it by 2 bit works") {
            auto result = a >> 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1 >> 1);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bit works") {
            auto result = a >> 10;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1 >> 9);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a >> UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 1);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bit works") {
            auto result = a >> UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1, 0};
        THEN("Shifting it by 1 bit works") {
            auto result = a >> 1;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
        THEN("Shifting it by 2 bit works") {
            auto result = a >> 2;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 >> 1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bit works") {
            auto result = a >> 10;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 >> 9);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a >> UINT64_WIDTH;
            REQUIRE(result.parts[0] == 1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {UINT_64_LEFT_MOST_1,0,0}") {
        uint192_lib::uint_192 a{UINT_64_LEFT_MOST_1, 0, 0};
        THEN("Shifting it by 1 returns an empty value") {
            auto result = a >> 1;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 >> 1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
        THEN("Shifting it by 2 bit works") {
            auto result = a >> 2;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 >> 2);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 10 bit works") {
            auto result = a >> 10;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 >> 10);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a >> UINT64_WIDTH;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,UINT_64_LEFT_MOST_1,UINT_64_LEFT_MOST_1}") {
        uint192_lib::uint_192 a{0, UINT_64_LEFT_MOST_1, UINT_64_LEFT_MOST_1};
        THEN("Shifting it by 1 works") {
            auto result = a >> 1;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1 >> 1);
            REQUIRE(result.parts[2] == UINT_64_LEFT_MOST_1 >> 1);
        }
        THEN("Shifting it by 2 bit works") {
            auto result = a >> 2;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1 >> 2);
            REQUIRE(result.parts[2] == UINT_64_LEFT_MOST_1 >> 2);
        }

        THEN("Shifting it by 10 bit works") {
            auto result = a >> 10;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1 >> 10);
            REQUIRE(result.parts[2] == UINT_64_LEFT_MOST_1 >> 10);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a >> UINT64_WIDTH;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[1] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bits works") {
            auto result = a >> UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,UINT64_MAX,UINT64_MAX}") {
        uint192_lib::uint_192 a{0, UINT64_MAX, UINT64_MAX};
        THEN("Shifting it by 1 works") {
            auto result = a >> 1;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 1);
        }
        THEN("Shifting it by 2 bit works") {
            auto result = a >> 2;
            REQUIRE(result.parts[0] == UINT_64_LEFT_MOST_1 + (1UL << 62UL));
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 2);
        }

        THEN("Shifting it by 10 bit works") {
            auto result = a >> 10;
            // The highest 10 bits are set
            REQUIRE(result.parts[0] == 0xffc0000000000000);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == UINT64_MAX >> 10);
        }

        THEN("Shifting it by 64 bits works") {
            auto result = a >> UINT64_WIDTH;
            REQUIRE(result.parts[0] == UINT64_MAX);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bits works") {
            auto result = a >> UINT64_WIDTH * 2;
            REQUIRE(result.parts[0] == UINT64_MAX);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 192 bit returns an empty result") {
            auto result = a >> UINT64_WIDTH * 3;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }
}
