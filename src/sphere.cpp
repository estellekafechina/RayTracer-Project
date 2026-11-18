#include "sphere.h"

Sphere::Sphere(const Vector& centre, double radius, const Colour& colour)
    : _centre(centre), _radius(radius), _colour(colour) {}

Colour Sphere::colour() const {
    return _colour;
}

bool Sphere::isHitBy(const Ray& ray) const {
    const Vector eyeToCentre = ray.origin() - _centre;
    const double a = ray.direction().dot(ray.direction());
    const double b = 2.0 * eyeToCentre.dot(ray.direction());
    const double c = eyeToCentre.dot(eyeToCentre) - _radius * _radius;
    const double discriminant = b * b - 4.0 * a * c;

    return discriminant >= 0.0;
}
