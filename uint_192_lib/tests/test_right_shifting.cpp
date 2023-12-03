//
// Created by jn98zk on 26.11.23.
//

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

constexpr uint64_t UINT_64_LEFT_MOST_1 = 1UL << 63;

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

        THEN("Shifting it by 192 bit works") {
            auto result = a >> UINT64_MAX;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }
    }

    GIVEN("A uint_192 of value {0,0,UINT64_MAX}") {
        uint192_lib::uint_192 a{0, 0, UINT64_MAX};

        THEN("Shifting it by 64 bit works") {
            auto result = a >> 64;
            REQUIRE(result.parts[0] == 0);
            REQUIRE(result.parts[1] == UINT64_MAX);
            REQUIRE(result.parts[2] == 0);
        }

        THEN("Shifting it by 128 bits works") {
            auto result = a >> 128;
            REQUIRE(result.parts[0] == UINT64_MAX);
            REQUIRE(result.parts[1] == 0);
            REQUIRE(result.parts[2] == 0);
        }

    }
}
