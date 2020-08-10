#ifndef DEF_DOUBLEMATRIX33
#define DEF_DOUBLEMATRIX33

#include "DoubleVec3D.h"

class DoubleMatrix33 {
private:
	DoubleVec3D column0;
	DoubleVec3D column1;
	DoubleVec3D column2;

public:
	DoubleMatrix33();
	DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2);
	DoubleMatrix33(const DoubleMatrix33& matrix);

	DoubleVec3D getColumn0();
	DoubleVec3D getColumn1();
	DoubleVec3D getColumn2();

	void setColumn0(const DoubleVec3D& column0);
	void setColumn1(const DoubleVec3D& column1);
	void setColumn2(const DoubleVec3D& column2);
};


#endif