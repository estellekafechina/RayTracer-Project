#include "geometry/sphere.h"

#include <cmath>

Sphere::Sphere(const Vector& centre, double radius, const Material& material)
    : _centre(centre), _radius(radius), _material(material) {}

Colour Sphere::colour() const {
    return _material.colour();
}

bool Sphere::isHitBy(const Ray& ray) const {
    const Vector eyeToCentre = ray.origin() - _centre;
    const double a = ray.direction().dot(ray.direction());
    const double b = 2.0 * eyeToCentre.dot(ray.direction());
    const double c = eyeToCentre.dot(eyeToCentre) - _radius * _radius;
    const double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return false;
    }

    const double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    const double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    return t1 > 0.0 || t2 > 0.0;
}

std::optional<Hit> Sphere::hit(const Ray& ray) const {
    const Vector eyeToCentre = ray.origin() - _centre;
    const double a = ray.direction().dot(ray.direction());
    const double b = 2.0 * eyeToCentre.dot(ray.direction());
    const double c = eyeToCentre.dot(eyeToCentre) - _radius * _radius;
    const double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return std::nullopt;
    }

    const double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    const double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    double t;
    if (t1 > 0.0) {
        t = t1;
    } else if (t2 > 0.0) {
        t = t2;
    } else {
        return std::nullopt;
    }

    const Vector point = ray.at(t);
    const Vector normal = (1.0 / _radius) * (point - _centre);
    return Hit{t, point, normal, _material};
}
