//
// Created by jn98zk on 04.12.23.
//

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <uint_192.hpp>

SCENARIO("Test == and != operator", "[uint_192]") {
    GIVEN("A uint_192 of value {1,0,0}") {
        uint192_lib::uint_192 a{1};
        THEN("It is equal to another uint_192 of value {1,0,0}") {
            uint192_lib::uint_192 b{1};
            REQUIRE(a == b);
            REQUIRE_FALSE(a != b);
        }

        THEN("It is not equal to another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a == b);
            REQUIRE(a != b);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};
        THEN("It is equal to another uint_192 of value {0,1,0}") {
            uint192_lib::uint_192 b{0, 1};
            REQUIRE(a == b);
            REQUIRE_FALSE(a != b);
        }

        THEN("It is not equal to another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a == b);
            REQUIRE(a != b);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};
        THEN("It is equal to another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE(a == b);
            REQUIRE_FALSE(a != b);
        }

        THEN("It is not equal to another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a == b);
            REQUIRE(a != b);
        }
    }
}

SCENARIO("Test < operator", "[uint_192]") {
    GIVEN("A uint_192 of value {5,0,0}") {
        uint192_lib::uint_192 a{5};

        THEN("It is not larger than another uint_192 of value {6,0,0}") {
            uint192_lib::uint_192 b{6};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,1,0}") {
            uint192_lib::uint_192 b{0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a < b);
        }

        THEN("It is not larger than another uint_192 of value {5,0,0}") {
            uint192_lib::uint_192 b{5};
            REQUIRE_FALSE(a > b);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("It is not larger than another uint_192 of value {0,2,0}") {
            uint192_lib::uint_192 b{0, 2};
            REQUIRE_FALSE(a > b);
        }
        THEN("It is not larger than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,1,0}") {
            uint192_lib::uint_192 b{0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is larger than another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE(a >= b);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};

        THEN("It is not larger than another uint_192 of value {0,0,2}") {
            uint192_lib::uint_192 b{0, 0, 2};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,0,3}") {
            uint192_lib::uint_192 b{0, 0, 3};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,0,UINT64_MAX}") {
            uint192_lib::uint_192 b{0, 0, UINT64_MAX};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not larger than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It larger than another uint_192 of value {UINT64_MAX,0,0}") {
            uint192_lib::uint_192 b{UINT64_MAX, 0, 0};
            REQUIRE(a > b);
        }

        THEN("It larger than another uint_192 of value {UINT64_MAX,UINT64_MAX,0}") {
            uint192_lib::uint_192 b{UINT64_MAX, UINT64_MAX, 0};
            REQUIRE(a > b);
        }

        THEN("It is larger than another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE(a > b);
        }
    }
}

SCENARIO("Test > operator", "[uint_192]") {
    GIVEN("A uint_192 of value {5,0,0}") {
        uint192_lib::uint_192 a{5};

        THEN("It is smaller than another uint_192 of value {6,0,0}") {
            uint192_lib::uint_192 b{6};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is smaller than another uint_192 of value {0,1,0}") {
            uint192_lib::uint_192 b{0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is smaller than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is smaller than another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a < b);
        }

        THEN("It is not smaller than another uint_192 of value {5,0,0}") {
            uint192_lib::uint_192 b{5};
            REQUIRE_FALSE(a < b);
        }
    }

    GIVEN("A uint_192 of value {0,1,0}") {
        uint192_lib::uint_192 a{0, 1};

        THEN("It is smaller than another uint_192 of value {0,2,0}") {
            uint192_lib::uint_192 b{0, 2};
            REQUIRE_FALSE(a > b);
        }
        THEN("It is smaller than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not smaller than another uint_192 of value {0,1,0}") {
            uint192_lib::uint_192 b{0, 1};
            REQUIRE_FALSE(a > b);
        }
    }

    GIVEN("A uint_192 of value {0,0,1}") {
        uint192_lib::uint_192 a{0, 0, 1};

        THEN("It is smaller than another uint_192 of value {0,0,2}") {
            uint192_lib::uint_192 b{0, 0, 2};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is smaller than another uint_192 of value {0,0,3}") {
            uint192_lib::uint_192 b{0, 0, 3};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is smaller than another uint_192 of value {0,0,UINT64_MAX}") {
            uint192_lib::uint_192 b{0, 0, UINT64_MAX};
            REQUIRE_FALSE(a > b);
        }

        THEN("It is not smaller than another uint_192 of value {0,0,1}") {
            uint192_lib::uint_192 b{0, 0, 1};
            REQUIRE_FALSE(a < b);
        }

        THEN("It is not smaller than another uint_192 of value {UINT64_MAX,0,0}") {
            uint192_lib::uint_192 b{UINT64_MAX, 0, 0};
            REQUIRE_FALSE(a < b);
        }

        THEN("It is not smaller than another uint_192 of value {UINT64_MAX,UINT64_MAX,0}") {
            uint192_lib::uint_192 b{UINT64_MAX, UINT64_MAX, 0};
            REQUIRE_FALSE(a < b);
        }

        THEN("It is not smaller than another uint_192 of value {0,0,0}") {
            uint192_lib::uint_192 b{0};
            REQUIRE_FALSE(a < b);
        }
    }
}
