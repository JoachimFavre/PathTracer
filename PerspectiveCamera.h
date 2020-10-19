#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Ray.h"

//! Models a perspective camera.
class PerspectiveCamera {
private:
	unsigned int numberPixelsX, numberPixelsY;
	DoubleVec3D origin, focal;

	// See my TM report for an explanation of these variables.
	DoubleUnitVec3D baseX;
	DoubleUnitVec3D baseY;
	void computeBases();

public:
	//! Default constructor.
	/*!
		numberPixelsX and numberpixelsY are set to 500 by default.
	*/
	PerspectiveCamera();

	//! Main constructor.
	/*!
		\param numberPixelsX The width of the camera in pixels. It will define the width of the render.
		\param numberPixelsY The height of the camera in pixels. It will define the height of the render.
		\param origin From where the rays are casted.
		\param focal Its direction defines the camera's and its length defines the camera length.
	*/
	PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, DoubleVec3D origin = DoubleVec3D(0.0), DoubleVec3D focal = DoubleVec3D(0, 0, -0.75));
	
	//! Copy constructor.
	/*!
		\param camera The camera that will be copied.
	*/
	PerspectiveCamera(const PerspectiveCamera& camera);
	

	//! Getter for the number of pixels in *x*.
	/*!
		\return The number of pixels that compose the camera on the *x* axis.
	*/
	unsigned int getNumberPixelsX() const;

	//! Getter for the number of pixels in *y*.
	/*!
		\return The number of pixels that compose the camera on the *y* axis.
	*/
	unsigned int getNumberPixelsY() const;

	//! Getter for the camera origin.
	/*!
		\return The camera origin.
	*/
	DoubleVec3D getOrigin() const;

	//! Getter for the camera focal.
	/*!
		\return The camera focal.
	*/
	DoubleVec3D getFocal() const;

	//! Getter for the camera world width.
	/*!
		\return The width of the camera in the virtual world.
	*/
	double getWorldWidth() const;

	//! Getter for the camera world height.
	/*!
		\return The width of the camera in the virtual height.
	*/
	double getWorldHeight() const;


	//! Setter for the number of pixels in *x*.
	/*!
		\param numberPixelsX The new number of pixels that compose the camera on the *x* axis.
	*/
	void setNumberPixelsX(unsigned int numberPixelsX);

	//! Setter for the number of pixels in *y*.
	/*!
		\param numberPixelsY The new number of pixels that compose the camera on the *y* axis.
	*/
	void setNumberPixelsY(unsigned int numberPixelsY);

	//! Setter for the camera origin.
	/*!
		\param origin The new camera origin.
	*/
	void setOrigin(DoubleVec3D origin);

	//! Setter for the camera focal.
	/*!
		\param focal The new camera focal.
	*/
	void setFocal(DoubleVec3D focal);


	//! Returns a ray going through some pixels.
	/*!
		See my TM's report for explanation on how it works.
		\param pixelX The $x$ coordinate of the pixel through which we want the ray.
		\param pixelY The $y$ coordinate of the pixel through which we want the ray.
		\return A ray which origin is the camera's and which direction is such that it goes through the requested pixel.
	*/
	Ray getRayGoingThrough(double pixelX, double pixelY) const;
};

#endif
