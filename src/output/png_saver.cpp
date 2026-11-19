#include "output/png_saver.h"

#include "image/image.h"

#include <lodepng.h>

#include <cmath>
#include <stdexcept>
#include <vector>

static unsigned char toByte(double value) {
    return static_cast<unsigned char>(std::lround(value * 255.0));
}

void PngSaver::save(const Image& image, const std::string& path) const {
    std::vector<unsigned char> pixels;
    pixels.reserve(image.width() * image.height() * 3);

    for (int row = 0; row < image.height(); ++row) {
        for (int column = 0; column < image.width(); ++column) {
            const Colour colour = image.pixel(column, row);
            pixels.push_back(toByte(colour.r()));
            pixels.push_back(toByte(colour.g()));
            pixels.push_back(toByte(colour.b()));
        }
    }

    const unsigned error = lodepng::encode(
        path,
        pixels,
        image.width(),
        image.height(),
        LCT_RGB
    );

    if (error != 0) {
        throw std::runtime_error(lodepng_error_text(error));
    }
}
