#ifndef DEF_DOUBLEUNITVEC3D
#define DEF_DOUBLEUNITVEC3D

#include "DoubleVec3D.h"

class DoubleUnitVec3D : public DoubleVec3D
{
public:
	DoubleUnitVec3D();
	DoubleUnitVec3D(double x, double y, double z, bool alreadyNormalised = false);
	DoubleUnitVec3D(const DoubleVec3D& vec, bool alreadyNormalised = false);
	DoubleUnitVec3D(const DoubleUnitVec3D& vec);

	virtual void setVals(double x, double y, double z);

	void operator=(const DoubleVec3D& vec);
};

DoubleUnitVec3D randomVectorOnUnitRadiusSphere(double (*randomDouble)());

#endif
