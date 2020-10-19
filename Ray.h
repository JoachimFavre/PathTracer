#ifndef DEF_RAY
#define DEF_RAY

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"

//! Combination of an origin and a direction.
class Ray {
private:
	DoubleVec3D origin;
	DoubleUnitVec3D direction;

public:
	//! Default constructor.
	/*!
		By default, the origin is at (0, 0, 0) and the direction is (1, 0, 0)
	*/
	Ray();

	//! Main constructor.
	/*!
		\param origin Where the ray starts.
		\param direction The ray direction.
	*/
	Ray(const DoubleVec3D& origin, const DoubleUnitVec3D& direction);

	//! Copy constructor.
	/*!
		\param ray The ray that will be copied.
	*/
	Ray(const Ray& ray);


	//! Getter for the origin.
	/*!
		\return This ray's origin.
	*/
	DoubleVec3D getOrigin() const;

	//! Getter for the direction.
	/*!
		\return This ray's direction.
	*/
	DoubleUnitVec3D getDirection() const;


	//! Setter for the origin.
	/*!
		\param origin The new origin of this ray.
	*/
	void setOrigin(const DoubleVec3D& origin);

	//! Setter for the direction.
	/*!
		\param direction The new direction of this ray.
	*/
	void setDirection(const DoubleUnitVec3D& direction);
};

#endif
