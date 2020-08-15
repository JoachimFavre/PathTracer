#ifndef DEF_DOUBLEVEC3D
#define DEF_DOUBLEVEC3D

#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

// Need to be included before fbxsdk, else creates conflict.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <fbxsdk.h>

class DoubleVec3D {
private:
	double x;
	double y;
	double z;

protected:
	bool normalised;

public:
	DoubleVec3D(double val = 0);
	DoubleVec3D(double x, double y, double z);
	DoubleVec3D(const DoubleVec3D& vec);
	DoubleVec3D(const FbxDouble3& vec);
	DoubleVec3D(const FbxDouble4& vec);

	double getX() const;
	double getY() const;
	double getZ() const;

	// void setX(double x);
	// void setY(double y);
	// void setZ(double z);
	virtual void setVals(double x, double y, double z);

	void operator+=(const DoubleVec3D& vec);
	void operator-=(const DoubleVec3D& vec);
	void operator*=(const double& val);
	void operator/=(const double& val);

	void normalise();
	bool isNormalised() const;
	bool isZero() const;
};

DoubleVec3D operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
DoubleVec3D operator-(const DoubleVec3D& vec);
DoubleVec3D operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2);

DoubleVec3D operator*(const DoubleVec3D& vec, const double& val);
DoubleVec3D operator*(const double& val, const DoubleVec3D& vec);
DoubleVec3D operator/(const DoubleVec3D& vec, const double& val);

std::ostream& operator<<(std::ostream& stream, const DoubleVec3D& vec);

DoubleVec3D crossProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
double dotProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
double length(const DoubleVec3D& vec);

void to_json(json& j, const DoubleVec3D& vec);
void from_json(const json& j, DoubleVec3D& vec);

#endif