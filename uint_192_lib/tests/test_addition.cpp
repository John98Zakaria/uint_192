//
// Created by jn98zk on 26.11.23.
//

#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

TEST_CASE("Can add two numbers correctly", "[uint_192]") {

    SECTION("0+0=0") {
        uint192_lib::uint_192 a{};
        uint192_lib::uint_192 b{};
        auto result = a + b;
        REQUIRE(result.parts[0] == 0);
        REQUIRE(result.parts[1] == 0);
        REQUIRE(result.parts[2] == 0);
    }

    SECTION("0+1=1") {
        uint192_lib::uint_192 a{1};
        uint192_lib::uint_192 b{};
        auto result = a + b;
        REQUIRE(result.parts[0] == 1);
        REQUIRE(result.parts[1] == 0);
        REQUIRE(result.parts[2] == 0);
    }

    SECTION("Adding carry in the least significant digit increments the next bit") {
        uint192_lib::uint_192 a{UINT64_MAX};
        uint192_lib::uint_192 b{1};
        auto result = a + b;
        REQUIRE(result.parts[0] == 0);
        REQUIRE(result.parts[1] == 1);
        REQUIRE(result.parts[2] == 0);
    }

    SECTION("Adding carry in the middle digit increments the last bit") {
        uint192_lib::uint_192 a{0, 1};
        uint192_lib::uint_192 b{0, UINT64_MAX};
        auto result = a + b;
        REQUIRE(result.parts[0] == 0);
        REQUIRE(result.parts[1] == 0);
        REQUIRE(result.parts[2] == 1);
    }

    SECTION("A carry into a part of UINT64_MAX is propagated to the next part") {
        uint192_lib::uint_192 a{UINT64_MAX, 5};
        uint192_lib::uint_192 b{1, UINT64_MAX};
        auto result = a + b;
        REQUIRE(result == uint192_lib::uint_192{0, 5, 1});
    }

    SECTION("A carry is propagated through multiple parts of UINT64_MAX") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX};
        uint192_lib::uint_192 b{1};
        auto result = a + b;
        REQUIRE(result == uint192_lib::uint_192{0, 0, 1});
    }

    SECTION("Adding to the maximum value overflows to zero") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint192_lib::uint_192 b{1};
        auto result = a + b;
        REQUIRE(result == uint192_lib::uint_192{});
    }

    SECTION("Simple math works") {
        uint192_lib::uint_192 a{14, 42};
        uint192_lib::uint_192 b{15, 6};
        auto result = a + b;
        REQUIRE(result.parts[0] == 29);
        REQUIRE(result.parts[1] == 48);
        REQUIRE(result.parts[2] == 0);
    }
}

TEST_CASE("Can add two numbers in place correctly", "[uint_192]") {

    SECTION("0+=0 is 0") {
        uint192_lib::uint_192 a{};
        a += uint192_lib::uint_192{};
        REQUIRE(a == uint192_lib::uint_192{});
    }

    SECTION("A carry into a part of UINT64_MAX is propagated to the next part") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX};
        a += uint192_lib::uint_192{1};
        REQUIRE(a == uint192_lib::uint_192{0, 0, 1});
    }

    SECTION("A carry into a part where both summands are UINT64_MAX is propagated to the next part") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX};
        a += uint192_lib::uint_192{1, UINT64_MAX};
        REQUIRE(a == uint192_lib::uint_192{0, UINT64_MAX, 1});
    }

    SECTION("Adding to the maximum value overflows to zero") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, UINT64_MAX};
        a += uint192_lib::uint_192{1};
        REQUIRE(a == uint192_lib::uint_192{});
    }

    SECTION("Gives the same result as +") {
        const uint192_lib::uint_192 a{14, UINT64_MAX, 42};
        const uint192_lib::uint_192 b{UINT64_MAX, 6, 1};
        auto result = a;
        result += b;
        REQUIRE(result == a + b);
    }
}
