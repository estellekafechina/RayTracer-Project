#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <memory>

using Catch::Matchers::WithinAbs;

TEST_CASE("Scene returns a plane hit before a sphere", "[scene]") {
    Scene scene(Vector(0.0, 1.0, 0.0));
    scene.add(std::make_unique<Sphere>(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));
    scene.add(std::make_unique<Plane>(
        Vector(0.0, 0.0, 2.0),
        Vector(0.0, 0.0, -1.0),
        Material(Colour(0.0, 0.0, 1.0))
    ));
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    const std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3.0, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(0.0, 0.0, 1.0));
}

TEST_CASE("Scene returns a sphere hit before a plane", "[scene]") {
    Scene scene(Vector(0.0, 1.0, 0.0));
    scene.add(std::make_unique<Sphere>(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));
    scene.add(std::make_unique<Plane>(
        Vector(0.0, 0.0, 20.0),
        Vector(0.0, 0.0, -1.0),
        Material(Colour(0.0, 0.0, 1.0))
    ));
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    const std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5.0, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(1.0, 0.0, 0.0));
}

TEST_CASE("Scene returns no hit when the ray misses every shape", "[scene]") {
    Scene scene(Vector(0.0, 1.0, 0.0));
    scene.add(std::make_unique<Sphere>(
        Vector(6.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}
