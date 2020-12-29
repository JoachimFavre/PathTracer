#include "Triangle.h"

// Constructors
Triangle::Triangle()
    : Object3D(), vertex0(1, 0, 0), vertex1(0, 1, 0), vertex2(0, 0, 1) {
    computeArea();
}

Triangle::Triangle(const DoubleVec3D& vertex0, const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, Material* material)
    : Object3D(material), vertex0(vertex0), vertex1(vertex1), vertex2(vertex2) {
    computeArea();
}

Triangle::Triangle(const Triangle& triangle)
    : Object3D(triangle), vertex0(triangle.vertex0), vertex1(triangle.vertex1), vertex2(triangle.vertex2) {
    computeArea();
}

// Getters
DoubleVec3D Triangle::getVertex0() const { return vertex0; }
DoubleVec3D Triangle::getVertex1() const { return vertex1; }
DoubleVec3D Triangle::getVertex2() const { return vertex2; }

DoubleVec3D Triangle::getCenter() const {
    return (vertex0 + vertex1 + vertex2) / 3;
}


// Setters
void Triangle::setVertex0(const DoubleVec3D& vertex) { vertex0 = vertex; computeArea(); }
void Triangle::setVertex1(const DoubleVec3D& vertex) { vertex1 = vertex; computeArea(); }
void Triangle::setVertex2(const DoubleVec3D& vertex) { vertex2 = vertex; computeArea(); }


// Virtual methods
void Triangle::computeArea() {
    DoubleVec3D edge1 = vertex1 - vertex0;
    DoubleVec3D edge2 = vertex2 - vertex0;
    area = 0.5 * length(crossProd(edge1, edge2));
}

Object3D* Triangle::deepCopy() const {
    return new Triangle(vertex0, vertex1, vertex2, getMaterial()->deepCopy());
}

double Triangle::closestIntersection(const Ray& ray) const {
    // Using Möller-Trumbore intersection algorithm (using notations from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm (accessed on 3rd July 2020)
    // Return -1 if no intersection
    DoubleVec3D edge1 = vertex1 - vertex0;
    DoubleVec3D edge2 = vertex2 - vertex0;
    DoubleVec3D h = crossProd(ray.getDirection(), edge2);
    double a = dotProd(edge1, h);
    if (a > -DBL_EPSILON && a < DBL_EPSILON)
        return -1;  // Triangle and ray are parallel
    double f = 1.0 / a;
    DoubleVec3D s = ray.getOrigin() - vertex0;
    double barycentricCoordU = f * dotProd(s, h);
    if (barycentricCoordU < 0.0 || barycentricCoordU > 1.0)  // conditions for barycentric coordinates
        return -1;
    DoubleVec3D q = crossProd(s, edge1);
    double barycentricCoordV = f * dotProd(ray.getDirection(), q);
    if (barycentricCoordV < 0.0 || barycentricCoordU + barycentricCoordV > 1.0)  // conditions for barycentric coordinates
        return -1;
    return f * dotProd(edge2, q);
}

DoubleUnitVec3D Triangle::getNormal(const DoubleVec3D& point) const {
    DoubleVec3D edge1 = vertex1 - vertex0;
    DoubleVec3D edge2 = vertex2 - vertex0;
    return crossProd(edge1, edge2);  // Casted into DoubleUnitVec3D 
    // The triangle can only be seen from one side, vertices have to be defined counterclockwise (point of view of the visible hemisphere).
}

DoubleVec3D Triangle::getRandomPoint() const {
    // Using p.814 of Robert Osada et al. "Shape distribution" (see report for a full bibliography)
    double rand1 = sqrt(randomDouble());
    double rand2 = randomDouble();
    return (1 - rand1)*vertex0 + rand1*(1 - rand2)*vertex1 + rand1*rand2*vertex2;
}


DoubleVec3D Triangle::getMinCoord() const {
    double minX = std::min(vertex0.getX(), std::min(vertex1.getX(), vertex2.getX()));
    double minY = std::min(vertex0.getY(), std::min(vertex1.getY(), vertex2.getY()));
    double minZ = std::min(vertex0.getZ(), std::min(vertex1.getZ(), vertex2.getZ()));

    return DoubleVec3D(minX, minY, minZ);
}

DoubleVec3D Triangle::getMaxCoord() const {
    double maxX = std::max(vertex0.getX(), std::max(vertex1.getX(), vertex2.getX()));
    double maxY = std::max(vertex0.getY(), std::max(vertex1.getY(), vertex2.getY()));
    double maxZ = std::max(vertex0.getZ(), std::max(vertex1.getZ(), vertex2.getZ()));

    return DoubleVec3D(maxX, maxY, maxZ);
}

std::ostream& Triangle::getDescription(std::ostream& stream) const {
    stream << "Triangle / Vertex0 = " << vertex0 << " / Vertex1 = " << vertex1 << " / Vertex2 = " << vertex2;
    return stream;
}


// Virtual methods for json
std::string Triangle::getType() const { return "Triangle"; }

json Triangle::getLocationJson() const {
    return { {"Vertex0", vertex0},
             {"Vertex1", vertex1},
             {"Vertex2", vertex2 } };
}

void Triangle::setLocationJson(const json& j) {
    vertex0 = j["Vertex0"].get<DoubleVec3D>();
    vertex1 = j["Vertex1"].get<DoubleVec3D>();
    vertex2 = j["Vertex2"].get<DoubleVec3D>();
}

