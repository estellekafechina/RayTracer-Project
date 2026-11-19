#include "geometry/ray.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Ray stores its origin and direction", "[ray]") {
    const Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));

    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 3.0));
    requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
}

TEST_CASE("Ray gives its point at t", "[ray]") {
    const Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, -4.0, 0.0));

    requireVectorsEqual(ray.at(0.0), Vector(0.0, 8.0, 0.0));
    requireVectorsEqual(ray.at(2.0), Vector(6.0, 0.0, 0.0));
}
