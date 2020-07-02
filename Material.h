#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "DoubleVec3.h"
#include "BRDF.h"

class Material {
private:
	DoubleVec3 colour;
	BRDF brdf;
	double emittance;

private:
	Material();
	Material(const DoubleVec3& colour, BRDF brdf, double emittance = 0);
	Material(const Material& obj);

	DoubleVec3 getColour() const;
	BRDF getBRDF() const;
	double getEmittance() const;

	void setColour(const DoubleVec3& colour);
	void setBRDF(BRDF brdf);
	void setEmittance(double emittance);
};


#endif