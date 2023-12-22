//
// Created by jn98zk on 13.12.23.
//
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

// constexpr uint192_lib::uint_192 ZERO{0};

SCENARIO("To base 10 string") {

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "340282366920938463463374607431768211455");
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,UINT64_MAX}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, UINT64_MAX};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "6277101735386680763835789423207666416102355444464034512895");
        }
    }
    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "340282366920938463463374607431768211456");
        }
    }

    GIVEN("A uint_192 of value {0,10,10}") {
        uint192_lib::uint_192 a{0, 10, 10};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "3402823669209384634818213515054777630720");
        }
    }

    GIVEN("A uint_192 of value {10,10,10}") {
        uint192_lib::uint_192 a{10, 10, 10};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "3402823669209384634818213515054777630730");
        }
    }

    GIVEN("A uint_192 of value {1,1,1}") {
        uint192_lib::uint_192 a{1, 1, 1};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "340282366920938463481821351505477763073");
        }
    }

    GIVEN("A uint_192 of value {10000000000,0,0}") {
        uint192_lib::uint_192 a{10000000000U, 0, 0};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == std::to_string(a[0]));
        }
    }

    GIVEN("A uint_192 of value {16429334492609741786ul, 13028418312897329085ul,14696764418113333527ul}") {
        uint192_lib::uint_192 a{16429334492609741786ul, 13028418312897329085ul, 14696764418113333527ul};

        THEN("its base 10 representation is correct") {
            REQUIRE(a.to_base10_string() == "5001049782275034030055506961225442092573047367050745578458");
        }
    }
}
