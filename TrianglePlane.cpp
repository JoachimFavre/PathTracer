#include "TrianglePlane.h"

// Constructors
TrianglePlane::TrianglePlane()
	: Object3D(), vertex1(1, 0, 0), vertex2(0, 1, 0), vertex3(0, 0, 1) {}

TrianglePlane::TrianglePlane(const DoubleVec3& vertex1, const DoubleVec3& vertex2, const DoubleVec3& vertex3, const Material& material)
	: Object3D(material), vertex1(vertex1), vertex2(vertex2), vertex3(vertex3) {}

TrianglePlane::TrianglePlane(const TrianglePlane& triangle)
	: Object3D(triangle), vertex1(triangle.vertex1), vertex2(triangle.vertex2), vertex3(triangle.vertex3) {}


// Getters
DoubleVec3 TrianglePlane::getVertex1() const { return vertex1; }
DoubleVec3 TrianglePlane::getVertex2() const { return vertex2; }
DoubleVec3 TrianglePlane::getVertex3() const { return vertex3; }


// Setters
void TrianglePlane::setVertex1(const DoubleVec3& vertex) { vertex1 = vertex; }
void TrianglePlane::setVertex2(const DoubleVec3& vertex) { vertex2 = vertex; }
void TrianglePlane::setVertex3(const DoubleVec3& vertex) { vertex3 = vertex; }


// Other methods
double TrianglePlane::closestIntersection(const Ray& ray) const {
	// Using Möller-Trumbore intersection algorithm (using notations from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm (accessed on 3rd July 2020)
	// Return -1 if no intersection
	DoubleVec3 edge1 = vertex2 - vertex1;
	DoubleVec3 edge2 = vertex3 - vertex1;
	DoubleVec3 h = crossProd(ray.getDirection(), edge2);
	double a = dotProd(edge1, h);
	if (a > -DBL_EPSILON && a < DBL_EPSILON)
		return -1;  // Triangle and ray are parallel
	double f = 1.0 / a;
	DoubleVec3 s = ray.getOrigin() - vertex1;
	double barycentricCoordU = f * dotProd(s, h);
	if (barycentricCoordU < 0.0 || barycentricCoordU > 1.0)  // conditions for barycentric coordinates
		return -1;
	DoubleVec3 q = crossProd(s, edge1);
	double barycentricCoordV = f * dotProd(ray.getDirection(), q);
	if (barycentricCoordV < 0.0 || barycentricCoordU + barycentricCoordV > 1.0)  // conditions for barycentric coordinates
		return -1;
	return f * dotProd(edge2, q);
}

DoubleVec3 TrianglePlane::getNormal(const DoubleVec3& point) const {
	DoubleVec3 edge1 = vertex2 - vertex1;
	DoubleVec3 edge2 = vertex3 - vertex1;
	return crossProd(edge1, edge2);  // Not sure with the signs
}
