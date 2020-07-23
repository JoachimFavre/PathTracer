#include "Triangle.h"

// Constructors
Triangle::Triangle()
	: Object3D(), vertex1(1, 0, 0), vertex2(0, 1, 0), vertex3(0, 0, 1) {}

Triangle::Triangle(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, Material* material)
	: Object3D(material), vertex1(vertex1), vertex2(vertex2), vertex3(vertex3) {}

Triangle::Triangle(const Triangle& triangle)
	: Object3D(triangle), vertex1(triangle.vertex1), vertex2(triangle.vertex2), vertex3(triangle.vertex3) {}


// Getters
DoubleVec3D Triangle::getVertex1() const { return vertex1; }
DoubleVec3D Triangle::getVertex2() const { return vertex2; }
DoubleVec3D Triangle::getVertex3() const { return vertex3; }


// Setters
void Triangle::setVertex1(const DoubleVec3D& vertex) { vertex1 = vertex; }
void Triangle::setVertex2(const DoubleVec3D& vertex) { vertex2 = vertex; }
void Triangle::setVertex3(const DoubleVec3D& vertex) { vertex3 = vertex; }


// Virtual methods
double Triangle::closestIntersection(const Ray& ray) const {
	// Using Möller-Trumbore intersection algorithm (using notations from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm (accessed on 3rd July 2020)
	// Return -1 if no intersection
	DoubleVec3D edge1 = vertex2 - vertex1;
	DoubleVec3D edge2 = vertex3 - vertex1;
	DoubleVec3D h = crossProd(ray.getDirection(), edge2);
	double a = dotProd(edge1, h);
	if (a > -DBL_EPSILON && a < DBL_EPSILON)
		return -1;  // Triangle and ray are parallel
	double f = 1.0 / a;
	DoubleVec3D s = ray.getOrigin() - vertex1;
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
	DoubleVec3D edge1 = vertex2 - vertex1;
	DoubleVec3D edge2 = vertex3 - vertex1;
	DoubleUnitVec3D result = crossProd(edge1, edge2);
	return result;  // The triangle can only be seen from one side, vertices have to be defined counterclockwise (point of view of the visible hemisphere).
}

DoubleVec3D Triangle::getRandomPoint(double (*randomDouble)()) const {
	double rand1 = sqrt(randomDouble());
	double rand2 = randomDouble();
	return (1 - rand1)*vertex1 + rand1*(1 - rand2)*vertex2 + rand1*rand2*vertex3;
}
