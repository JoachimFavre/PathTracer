#ifndef DEF_DOUBLEVEC3
#define DEF_DOUBLEVEC3

#include <iostream>
#include <math.h>

class DoubleVec3 {
private:
	double x = 0;
	double y = 0;
	double z = 0;

public:
	DoubleVec3(double val = 0);
	DoubleVec3(double x, double y, double z);
	DoubleVec3(const DoubleVec3& vec);

	double getX() const;
	double getY() const;
	double getZ() const;

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setVals(double x, double y, double z);

	void operator+=(const DoubleVec3& vec);
	void operator-=(const DoubleVec3& vec);
	void operator*=(const double& val);
	void operator/=(const double& val);

	void normalise();
};

DoubleVec3 operator+(const DoubleVec3& vec1, const DoubleVec3& vec2);
DoubleVec3 operator-(const DoubleVec3& vec);
DoubleVec3 operator-(const DoubleVec3& vec1, const DoubleVec3& vec2);

DoubleVec3 operator*(const DoubleVec3& vec, const double& val);
DoubleVec3 operator*(const double& val, const DoubleVec3& vec);
DoubleVec3 operator/(const DoubleVec3& vec, const double& val);

std::ostream& operator<<(std::ostream& stream, const DoubleVec3& vec);

DoubleVec3 crossProd(const DoubleVec3& vec1, const DoubleVec3& vec2);
double dotProd(const DoubleVec3& vec1, const DoubleVec3& vec2);
double length(const DoubleVec3& vec);

#endif