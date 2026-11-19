#include "geometry/sphere.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("Sphere hit gives the nearest point and normal", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    const std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 4.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 0.0, -1.0));
    requireColoursEqual(hit->material.colour(), Colour(1.0, 0.0, 0.0));
}

TEST_CASE("Off-centre sphere hit gives its point and normal", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(3.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    const std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 5.0));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0.0, -0.8));
}

TEST_CASE("Sphere hit is empty when the ray misses", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(6.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere hit is empty behind the eye", "[sphere]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(0.0, 0.0, -11.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}
