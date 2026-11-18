#include "vector.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("a + b adds each component", "[vector]") {
    const Vector sum = Vector(3, 4, 0) + Vector(4, -3, 0);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 0);
}

TEST_CASE("a + b includes the z component", "[vector]") {
    const Vector sum = Vector(3, 4, 1) + Vector(4, -3, 2);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 3);
}

TEST_CASE("a - b subtracts each component", "[vector]") {
    const Vector first = Vector(4, 5, 0) - Vector(1, 1, 0);

    REQUIRE(first.x() == 3);
    REQUIRE(first.y() == 4);
    REQUIRE(first.z() == 0);

    const Vector second = Vector(4, 5, 6) - Vector(1, 1, 2);

    REQUIRE(second.x() == 3);
    REQUIRE(second.y() == 4);
    REQUIRE(second.z() == 4);
}

TEST_CASE("t * v scales each component", "[vector]") {
    const Vector result = 2.0 * Vector(3, -4, 1);

    REQUIRE(result.x() == 6);
    REQUIRE(result.y() == -8);
    REQUIRE(result.z() == 2);
}

TEST_CASE("O + t * D gives the point on the ray at t", "[vector]") {
    const Vector O(0, 8, 0);
    const Vector D(3, -4, 0);
    const double t = 2;

    const Vector result = O + t * D;

    REQUIRE(result.x() == 6);
    REQUIRE(result.y() == 0);
    REQUIRE(result.z() == 0);
}

TEST_CASE("dot multiplies in pairs, then adds", "[vector]") {
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, 3, 0)) == 24);
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, -3, 0)) == 0);
    REQUIRE(Vector(3, 4, 12).dot(Vector(4, 3, 1)) == 36);
}

TEST_CASE("length follows Pythagoras", "[vector]") {
    REQUIRE(Vector(3, -4, 0).length() == 5);
    REQUIRE(Vector(3, 4, 12).length() == 13);
}
