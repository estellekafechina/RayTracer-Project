#include "render/trace.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("trace returns the sphere colour when the ray hits", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Colour(1.0, 0.0, 0.0)
    );

    const Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour.r(), WithinAbs(1.0, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0.0, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0.0, tolerance));
}

TEST_CASE("trace returns black when the ray misses", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    const Sphere sphere(
        Vector(6.0, 0.0, 9.0),
        5.0,
        Colour(1.0, 0.0, 0.0)
    );

    const Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour.r(), WithinAbs(0.0, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0.0, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0.0, tolerance));
}
