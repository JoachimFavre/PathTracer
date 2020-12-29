#ifndef DEF_RAY
#define DEF_RAY

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"

/*!
    \file Ray.h
    \brief Defines the Ray class.

    \class Ray
    \brief Combination of an origin and a direction.

    \fn Ray::Ray()
    \brief Default constructor.
    \details By default, the origin is at (0, 0, 0) and the direction is (1, 0, 0)

    \fn Ray::Ray(const DoubleVec3D& origin, const DoubleUnitVec3D& direction)
    \brief Main constructor.
    \param origin Where the ray starts.
    \param direction The ray direction.

    \fn Ray::Ray(const Ray& ray)
    \brief Copy constructor.
    \param ray The ray that will be copied.

    \fn DoubleVec3D Ray::getOrigin()
    \brief Getter for the origin.
    \return This ray's origin.

    \fn DoubleVec3D Ray::getDirection()
    \brief Getter for the direction.
    \return This ray's direction.

    \fn void Ray::setOrigin(const DoubleVec3D& origin)
    \brief Setter for the origin.
    \param origin The new origin of this ray.

    \fn void Ray::setDirection(const DoubleUnitVec3D& direction)
    \brief Setter for the direction.
    \param direction The new direction of this ray.
*/

class Ray {
private:
    DoubleVec3D origin;
    DoubleUnitVec3D direction;

public:
    Ray();
    Ray(const DoubleVec3D& origin, const DoubleUnitVec3D& direction);
    Ray(const Ray& ray);

    DoubleVec3D getOrigin() const;
    DoubleUnitVec3D getDirection() const;

    void setOrigin(const DoubleVec3D& origin);
    void setDirection(const DoubleUnitVec3D& direction);
};

#endif
