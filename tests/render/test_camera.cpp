#include "render/camera.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Camera creates a ray through the screen centre", "[camera]") {
    const Camera camera(
        Vector(0.0, 0.0, -1.0),
        Vector(0.0, 0.0, 0.0),
        2.0
    );

    const Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Camera ray points from the eye to the screen centre", "[camera]") {
    const Camera camera(
        Vector(1.0, 2.0, -1.0),
        Vector(4.0, 6.0, -1.0),
        2.0
    );

    const Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, -1.0));
    requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
}

TEST_CASE("Camera creates rays through individual pixels", "[camera]") {
    const Camera camera(
        Vector(0.0, 0.0, -1.0),
        Vector(0.0, 0.0, 0.0),
        5.0
    );

    requireVectorsEqual(
        camera.rayThroughPixel(2, 1, 5, 3).direction(),
        Vector(0.0, 0.0, 1.0)
    );
    requireVectorsEqual(
        camera.rayThroughPixel(4, 0, 5, 3).direction(),
        Vector(2.0, 1.0, 1.0)
    );
    requireVectorsEqual(
        camera.rayThroughPixel(0, 2, 5, 3).direction(),
        Vector(-2.0, -1.0, 1.0)
    );
}

TEST_CASE("Camera supports a different pixel size", "[camera]") {
    const Camera camera(
        Vector(0.0, 0.0, -1.0),
        Vector(0.0, 0.0, 0.0),
        2.0
    );

    requireVectorsEqual(
        camera.rayThroughPixel(256, 128, 512, 256).direction(),
        Vector(1.0 / 512.0, -1.0 / 512.0, 1.0)
    );
}

