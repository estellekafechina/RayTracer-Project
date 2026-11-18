#include "vector.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("add sums each component", "[vector]") {
    const Vector sum = Vector(3, 4, 0).add(Vector(4, -3, 0));

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 0);
}

TEST_CASE("add includes the z component", "[vector]") {
    const Vector sum = Vector(3, 4, 1).add(Vector(4, -3, 2));

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 3);
}
