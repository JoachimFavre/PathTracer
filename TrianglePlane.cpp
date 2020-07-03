#include "TrianglePlane.h"

// Constructors
TrianglePlane::TrianglePlane()
	: Object3D(), vertex1(1, 0, 0), vertex2(0, 1, 0), vertex3(0, 0, 1) {}

TrianglePlane::TrianglePlane(const DoubleVec3& vertex1, const DoubleVec3& vertex2, const DoubleVec3& vertex3, const Material& material)
	: Object3D(material), vertex1(vertex1), vertex2(vertex2), vertex3(vertex3) {}

TrianglePlane::TrianglePlane(const TrianglePlane& triangle)
	: Object3D(triangle), vertex1(triangle.vertex1), vertex2(triangle.vertex2), vertex3(triangle.vertex3) {}

