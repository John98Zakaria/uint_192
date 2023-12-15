//
// Created by jn98zk on 26.11.23.
//

#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

#include <iostream>
constexpr uint192_lib::uint_192 MULTIPLICATION_IDENTITY{1};
constexpr uint192_lib::uint_192 ZERO{0};

SCENARIO("Multiplication") {

    GIVEN("A uint_192 of value {1,0,0}") {
        uint192_lib::uint_192 a{1};

        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == MULTIPLICATION_IDENTITY);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX};

        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 2 is equivalent to shifting it once") {
            uint192_lib::uint_192 b{2};
            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == (a << 1));
        }

        THEN("Multiplying by 4 is equivalent to shifting it twice") {
            uint192_lib::uint_192 b{4};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == (a << 2));
        }

        THEN("Multiplying by 8 is equivalent to shifting it trice") {
            uint192_lib::uint_192 b{8};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == (a << 3));
        }

        THEN("Multiplying by UINT_MAX should be correct") {
            uint192_lib::uint_192 b{UINT64_MAX};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == uint192_lib::uint_192{1, 18446744073709551614UL});
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {0,UINT64_MAX,0}") {
        uint192_lib::uint_192 a{0, UINT64_MAX};

        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 2 is equivalent to shifting it once") {
            uint192_lib::uint_192 b{2};
            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res.parts[0] == 0);
            REQUIRE(res.parts[1] == (UINT64_MAX - 1));
            REQUIRE(res.parts[2] == 1);
        }

        THEN("Multiplying by 4 is equivalent to shifting it twice") {
            uint192_lib::uint_192 b{4};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == (a << 2));
        }

        THEN("Multiplying by 8 is equivalent to shifting it trice") {
            uint192_lib::uint_192 b{8};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == (a << 3));
        }

        THEN("Multiplying by UINT_MAX should be correct") {
            uint192_lib::uint_192 b{UINT64_MAX};

            const uint192_lib::uint_192 res = a * b;
            REQUIRE(res == uint192_lib::uint_192{0, 1, 18446744073709551614UL});
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {1,1,0}") {
        uint192_lib::uint_192 a{1, 1, 0};
        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX,0,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, 0, 0};
        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }

    GIVEN("A uint_192 of value {UINT64_MAX, UINT64_MAX,0}") {
        uint192_lib::uint_192 a{UINT64_MAX, UINT64_MAX, 0};
        THEN("Multiplying by 1 results in the identity") {
            const uint192_lib::uint_192 res = a * MULTIPLICATION_IDENTITY;
            REQUIRE(res == a);
        }

        THEN("Multiplying by 0 results in 0") {
            const uint192_lib::uint_192 res = a * ZERO;
            REQUIRE(res == ZERO);
        }
    }
}

TEST_CASE("GMP value regression test") {
    uint192_lib::uint_192 a{642836, 2223009};
    uint192_lib::uint_192 b{8557021, 6585754};

    auto c = a * b;

    REQUIRE(c.parts[0] == 5500761151556UL);
    REQUIRE(c.parts[1] == 23255894454533UL);
    REQUIRE(c.parts[2] == 14640190413786Ul);
}
