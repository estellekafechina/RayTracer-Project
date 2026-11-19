#include "render/camera.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Camera creates a ray through the screen centre", "[camera]") {
    const Camera camera(
        Vector(0.0, 0.0, -1.0),
        Vector(0.0, 0.0, 0.0),
        2.0
    );

    const Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Camera ray points from the eye to the screen centre", "[camera]") {
    const Camera camera(
        Vector(1.0, 2.0, -1.0),
        Vector(4.0, 6.0, -1.0),
        2.0
    );

    const Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

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

TEST_CASE("Camera renders the sphere as a red plus", "[camera]") {
    const Camera camera(
        Vector(0.0, 0.0, -1.0),
        Vector(0.0, 0.0, 0.0),
        5.0
    );
    const Sphere sphere(
        Vector(0.0, 0.0, 6.0),
        5.0,
        Material(Colour(1.0, 0.0, 0.0))
    );

    const Image image = camera.render(
        sphere,
        Vector(0.0, 0.0, -1.0),
        5,
        3
    );

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            const bool isCentre = column == 2 && row == 1;
            const bool isNeighbour =
                (column == 2 && row == 0) ||
                (row == 1 && (column == 1 || column == 3)) ||
                (column == 2 && row == 2);
            const Colour expected = isCentre
                ? Colour(1.0, 0.0, 0.0)
                : isNeighbour
                    ? Colour(0.8, 0.0, 0.0)
                    : Colour(0.0, 0.0, 0.0);

            requireColoursEqual(image.pixel(column, row), expected);
        }
    }
}

