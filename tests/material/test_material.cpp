#include "material/material.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Material shades with Lambert's law", "[material]") {
    const Material material(Colour(1.0, 0.5, 0.0));
    const Vector normal(0.0, 0.0, -1.0);

    requireColoursEqual(
        material.shade(normal, Vector(0.0, 0.0, -1.0)),
        Colour(1.0, 0.5, 0.0)
    );
    requireColoursEqual(
        material.shade(normal, Vector(0.6, 0.0, -0.8)),
        Colour(0.8, 0.4, 0.0)
    );
    requireColoursEqual(
        material.shade(normal, Vector(1.0, 0.0, 0.0)),
        Colour(0.0, 0.0, 0.0)
    );
    requireColoursEqual(
        material.shade(normal, Vector(0.0, 0.0, 1.0)),
        Colour(0.0, 0.0, 0.0)
    );
}

TEST_CASE("Material exposes its colour", "[material]") {
    const Material material(Colour(1.0, 0.5, 0.0));

    requireColoursEqual(material.colour(), Colour(1.0, 0.5, 0.0));
}
