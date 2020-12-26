#include "Sphere.h"

// Constructors
Sphere::Sphere()
    : Object3D(), center(0), radius(1) {
    computeArea();
}

Sphere::Sphere(const DoubleVec3D& center, double radius, Material* material)
    : Object3D(material), center(center), radius(radius) {
    computeArea();
}

Sphere::Sphere(const Sphere& sphere)
    : Object3D(sphere), center(sphere.center), radius(sphere.radius) {
    computeArea();
}


// Getters
DoubleVec3D Sphere::getCenter() const { return center; }
double Sphere::getRadius() const { return radius; }


// Setters
void Sphere::setCenter(const DoubleVec3D& center) { this->center = center; }
void Sphere::setRadius(double radius) { this->radius = radius; computeArea(); }


// Virtual methods
void Sphere::computeArea() { area = 4*M_PI*radius;}

Object3D* Sphere::deepCopy() const {
    return new Sphere(center, radius, getMaterial()->deepCopy());
}

double Sphere::closestIntersection(const Ray& ray) const {
    // Returns -1 if no solution
    // Using quadratic equation formula to solve (meaning of a, b, c)
    // a = dotProd(rayDir, rayDir) but = 1
    DoubleVec3D differenceOriginCenter = ray.getOrigin() - center;
    double b = 2 * dotProd(ray.getDirection(), differenceOriginCenter);
    double c = dotProd(differenceOriginCenter, differenceOriginCenter) - radius * radius;

    double discriminant = b*b - 4*c;
    if (discriminant < 0.0)
        return -1.0;
    else if (discriminant == 0.0)
        return -b/2;
    else {
        double sqrt_discriminant = sqrt(discriminant);
        double twiceSolution1 = -b - sqrt_discriminant;
        if (twiceSolution1 > 0.0)
            return twiceSolution1/2; // smallest solution and is positive
        else
            return (-b + sqrt_discriminant)/2; // biggest solution but maybe positive
    }
}    

DoubleUnitVec3D Sphere::getNormal(const DoubleVec3D& point) const {
    return DoubleUnitVec3D((point - center)/radius, true);
}


DoubleVec3D Sphere::getRandomPoint() const {
    DoubleVec3D point = randomVectorOnUnitRadiusSphere();
    return center + radius*point;
}

DoubleVec3D Sphere::getMinCoord() const {
    return center - DoubleVec3D(radius);
}

DoubleVec3D Sphere::getMaxCoord() const {
    return center + DoubleVec3D(radius);
}

std::ostream& Sphere::getDescription(std::ostream& stream) const {
    stream << "Sphere / Center = " << center << " / Radius = " << radius;
    return stream;
}


// Virtual methods for json
std::string Sphere::getType() const { return "Sphere"; }

json Sphere::getLocationJson() const {
    return { {"Center", center},
             {"Radius", radius} };
}

void Sphere::setLocationJson(const json& j) {
    center = j["Center"].get<DoubleVec3D>();
    radius = j["Radius"].get<double>();
}
