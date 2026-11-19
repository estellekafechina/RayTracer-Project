#include "geometry/sphere.h"
#include "render/trace.h"
#include "scene/scene.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <memory>

TEST_CASE("trace shades a sphere facing the light", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    Scene scene(Vector(0.0, 0.0, -1.0));
    scene.add(std::make_unique<Sphere>(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));

    requireColoursEqual(
        trace(ray, scene),
        Colour(1.0, 0.0, 0.0)
    );
}

TEST_CASE("trace shades a sphere at an angle", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    Scene scene(Vector(0.6, 0.0, -0.8));
    scene.add(std::make_unique<Sphere>(
        Vector(0.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));

    requireColoursEqual(
        trace(ray, scene),
        Colour(0.8, 0.0, 0.0)
    );
}

TEST_CASE("trace shades an off-centre sphere", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    Scene scene(Vector(0.0, 0.0, -1.0));
    scene.add(std::make_unique<Sphere>(
        Vector(3.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));

    requireColoursEqual(
        trace(ray, scene),
        Colour(0.8, 0.0, 0.0)
    );
}

TEST_CASE("trace returns black when the ray misses", "[trace]") {
    const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    Scene scene(Vector(0.0, 0.0, -1.0));
    scene.add(std::make_unique<Sphere>(
        Vector(6.0, 0.0, 9.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    ));

    requireColoursEqual(
        trace(ray, scene),
        Colour(0.0, 0.0, 0.0)
    );
}
