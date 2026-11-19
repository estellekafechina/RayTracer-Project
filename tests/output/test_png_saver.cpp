#include "image/image.h"
#include "output/png_saver.h"

#include <catch2/catch_test_macros.hpp>
#include <lodepng.h>

#include <cstdio>
#include <string>
#include <vector>

TEST_CASE("PngSaver writes pixels in rows from the top", "[png_saver]") {
    const std::string path = "png_saver_test.png";
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1.0, 0.5, 0.0));

    PngSaver saver;
    saver.save(image, path);

    std::vector<unsigned char> pixels;
    unsigned width = 0;
    unsigned height = 0;
    const unsigned error = lodepng::decode(
        pixels,
        width,
        height,
        path,
        LCT_RGB,
        8
    );

    REQUIRE(error == 0);
    REQUIRE(width == 2);
    REQUIRE(height == 2);

    const std::vector<int> actual(pixels.begin(), pixels.end());
    const std::vector<int> expected{
        0, 0, 0,
        255, 128, 0,
        0, 0, 0,
        0, 0, 0
    };
    REQUIRE(actual == expected);

    std::remove(path.c_str());
}
