#include "geometry/sphere.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("A ray through a sphere is a hit", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray can hit a sphere away from its centre", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(3.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray can miss a sphere", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(6.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("A sphere behind the eye is not hit", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(0.0, 0.0, -11.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("Sphere stores its colour", "[sphere]") {
    const Sphere sphere(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.5, 0.0))
    );

    requireColoursEqual(sphere.colour(), Colour(1.0, 0.5, 0.0));
}
