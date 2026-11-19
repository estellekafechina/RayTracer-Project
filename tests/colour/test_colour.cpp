#include "colour/colour.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("Colour stores its red, green and blue components", "[colour]") {
    const Colour colour(1.0, 0.5, 0.0);

    REQUIRE_THAT(colour.r(), WithinAbs(1.0, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0.5, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0.0, tolerance));
}

TEST_CASE("t * colour scales every component", "[colour]") {
    requireColoursEqual(
        0.5 * Colour(1.0, 0.5, 0.0),
        Colour(0.5, 0.25, 0.0)
    );
}
