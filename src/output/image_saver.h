#pragma once

#include <string>

class Image;

class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(const Image& image, const std::string& path) const = 0;
};
