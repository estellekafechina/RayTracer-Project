#include "geometry/plane.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("A ray hits the floor", "[plane]") {
    const Plane plane(
        Vector(0.0, 0.0, 0.0),
        Vector(0.0, 1.0, 0.0),
        Material(Colour(0.0, 1.0, 0.0))
    );
    const Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, -4.0, 0.0));

    const std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(6.0, 0.0, 0.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 1.0, 0.0));
    requireColoursEqual(hit->material.colour(), Colour(0.0, 1.0, 0.0));
}

TEST_CASE("Plane normal is normalised", "[plane]") {
    const Plane plane(
        Vector(8.0, 0.0, 0.0),
        Vector(3.0, 4.0, 0.0),
        Material(Colour(0.0, 1.0, 0.0))
    );
    const Ray ray(Vector(-8.0, 0.0, 0.0), Vector(4.0, 3.0, 0.0));

    const std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 6.0, 0.0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0.0));
}

TEST_CASE("A ray parallel to a plane does not hit", "[plane]") {
    const Plane plane(
        Vector(0.0, 0.0, 0.0),
        Vector(0.0, 1.0, 0.0),
        Material(Colour(0.0, 1.0, 0.0))
    );
    const Ray ray(Vector(0.0, 8.0, 0.0), Vector(5.0, 0.0, 0.0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}

TEST_CASE("A plane behind a ray does not hit", "[plane]") {
    const Plane plane(
        Vector(0.0, 0.0, 0.0),
        Vector(0.0, 1.0, 0.0),
        Material(Colour(0.0, 1.0, 0.0))
    );
    const Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, 4.0, 0.0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}
