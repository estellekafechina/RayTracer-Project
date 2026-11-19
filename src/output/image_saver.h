#pragma once

#include <string>

class Image;

class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    // Saves the whole image to path, or throws std::runtime_error.
    virtual void save(const Image& image, const std::string& path) const = 0;
};
