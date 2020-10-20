#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Ray.h"

/*!
	\file PerspectiveCamera.h
	\brief Defines the PerspectiveCamera class.

	\class PerspectiveCamera
	\brief Models a perspective camera.

	\fn PerspectiveCamera::PerspectiveCamera()
	\brief Default constructor.
	\details numberPixelsX and numberpixelsY are set to 500 by default.

	\fn PerspectiveCamera::PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, DoubleVec3D origin = DoubleVec3D(0.0), DoubleVec3D focal = DoubleVec3D(0, 0, -0.75))
	\brief Main constructor.
	\param numberPixelsX The width of the camera in pixels. It will define the width of the render.
	\param numberPixelsY The height of the camera in pixels. It will define the height of the render.
	\param origin From where the rays are casted.
	\param focal Its direction defines the camera's and its length defines the camera length.

	\fn PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
	\brief Copy constructor.
	\param camera The camera that will be copied.

	\fn PerspectiveCamera::getNumberPixelsX()
	\brief Getter for the number of pixels in *x*.
	\return The number of pixels that compose the camera on the *x* axis.

	\fn PerspectiveCamera::getNumberPixelsY()
	\brief Getter for the number of pixels in *y*.
	\return The number of pixels that compose the camera on the *y* axis.

	\fn PerspectiveCamera::getOrigin()
	\brief Getter for the camera origin.
	\return The camera origin.

	\fn PerspectiveCamera::getFocal()
	\brief Getter for the camera focal.
	\return The camera focal.

	\fn PerspectiveCamera::getWorldWidth()
	\brief Getter for the camera world width.
	\return The width of the camera in the virtual world.

	\fn PerspectiveCamera::getWorldHeight()
	\brief Getter for the camera world height.
	\return The width of the camera in the virtual height.

	\fn PerspectiveCamera::setNumberPixelsX(unsigned int numberPixelsX)
	\brief Setter for the number of pixels in *x*.
	\param numberPixelsX The new number of pixels that compose the camera on the *x* axis.

	\fn PerspectiveCamera::setNumberPixelsY(unsigned int numberPixelsY)
	\brief Setter for the number of pixels in *y*.
	\param numberPixelsY The new number of pixels that compose the camera on the *y* axis.

	\fn PerspectiveCamera::setOrigin(DoubleVec3D origin)
	\brief Setter for the camera origin.
	\param origin The new camera origin.

	\fn PerspectiveCamera::setFocal(DoubleVec3D focal)
	\brief Setter for the camera focal.
	\param focal The new camera focal.

	\fn PerspectiveCamera::getRayGoingThrough(double pixelX, double pixelY)
	\brief Returns a ray going through some pixels.
	\details See my TM's report for an explanation on how it works.
	\param pixelX The $x$ coordinate of the pixel through which we want the ray.
	\param pixelY The $y$ coordinate of the pixel through which we want the ray.
	\return A ray which origin is the camera's and which direction is such that it goes through the requested pixel.
*/

class PerspectiveCamera {
private:
	unsigned int numberPixelsX, numberPixelsY;
	DoubleVec3D origin, focal;

	// See my TM report for an explanation of these variables.
	DoubleUnitVec3D baseX;
	DoubleUnitVec3D baseY;
	void computeBases();

public:
	PerspectiveCamera();
	PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, DoubleVec3D origin = DoubleVec3D(0.0), DoubleVec3D focal = DoubleVec3D(0, 0, -0.75));
	PerspectiveCamera(const PerspectiveCamera& camera);
	
	unsigned int getNumberPixelsX() const;
	unsigned int getNumberPixelsY() const;
	DoubleVec3D getOrigin() const;
	DoubleVec3D getFocal() const;
	double getWorldWidth() const;
	double getWorldHeight() const;

	void setNumberPixelsX(unsigned int numberPixelsX);
	void setNumberPixelsY(unsigned int numberPixelsY);
	void setOrigin(DoubleVec3D origin);
	void setFocal(DoubleVec3D focal);

	Ray getRayGoingThrough(double pixelX, double pixelY) const;
};

#endif
