#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "BRDF.h"

class Material {
private:
	DoubleVec3D colour;
	BRDF brdf;
	double emittance;

public:
	Material();
	Material(const DoubleVec3D& colour, BRDF brdf, double emittance = 0);
	Material(const Material& material);

	DoubleVec3D getColour() const;
	BRDF getBRDF() const;
	double getEmittance() const;

	void setColour(const DoubleVec3D& colour);
	void setBRDF(BRDF brdf);
	void setEmittance(double emittance);
};


#endif