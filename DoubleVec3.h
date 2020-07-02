#ifndef DEF_DOUBLEVEC3
#define DEF_DOUBLEVEC3

class DoubleVec3 {
private:
	double x, y, z;

public:
	DoubleVec3(double val = 0);
	DoubleVec3(double x, double y, double z);

	double getX();
	double getY();
	double getZ();

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setVals(double x, double y, double z);

	void operator+=(const DoubleVec3& vec);
	void operator-=(const DoubleVec3& vec);
};

double length(const DoubleVec3& vec);
double dotProd(const DoubleVec3& vec1, const DoubleVec3& vec2);
DoubleVec3 crossProd(const DoubleVec3& vec1, const DoubleVec3& vec2);

DoubleVec3 operator+(const DoubleVec3& vec1, const DoubleVec3& vec2);
DoubleVec3 operator-(const DoubleVec3& vec1, const DoubleVec3& vec2);


#endif