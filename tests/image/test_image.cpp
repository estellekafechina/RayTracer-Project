#include "image/image.h"
#include "test_helpers.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Image starts with every pixel black", "[image]") {
    const Image image(5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
        }
    }
}

TEST_CASE("Setting a pixel changes only that pixel", "[image]") {
    Image image(5, 3);

    image.setPixel(4, 0, Colour(1, 0, 0));

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            if (column == 4 && row == 0) {
                requireColoursEqual(image.pixel(column, row), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
            }
        }
    }
}
