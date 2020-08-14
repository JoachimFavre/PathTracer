#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"

class Triangle : public Object3D {
private:
	DoubleVec3D vertex1, vertex2, vertex3;

public:
	Triangle();
	Triangle(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, Material* material);
	Triangle(const Triangle& triangle);

	DoubleVec3D getVertex1() const;
	DoubleVec3D getVertex2() const;
	DoubleVec3D getVertex3() const;
	DoubleVec3D getCenter() const;  // virtual method

	void setVertex1(const DoubleVec3D& vertex);
	void setVertex2(const DoubleVec3D& vertex);
	void setVertex3(const DoubleVec3D& vertex);

	Object3D* deepCopy() const;
	double closestIntersection(const Ray& ray) const;
	DoubleUnitVec3D getNormal(const DoubleVec3D& point) const;
	DoubleVec3D getRandomPoint(double (*randomDouble)()) const;
	std::ostream& getDescription(std::ostream& stream) const;

	std::string getType() const;
	json getLocationJson() const;
};

#endif