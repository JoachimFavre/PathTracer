#ifndef DEF_PICTURE
#define DEF_PICTURE

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "CImg/CImg.h"

#include "DoubleVec3D.h"
#include "InterfaceGestion.h"

//! Stores luminance for each pixel.
class Picture
{
private:
	const unsigned int width;
	const unsigned int height;
	double renderTime;
	DoubleVec3D** pixels;

public:
	//! The maximum value for the colour in the file.
	/*!
		\sa toneMapping()
	*/
	static constexpr unsigned int maxColourValue = 255;

	//! Default constructor.
	/*!
		By default, width and height are both set to 500.
	*/
	Picture();

	//! Main constructor
	/*!
		All pixels are set to (0, 0, 0).
		\param width The picture width.
		\param height The picture height.
		\param renderTime The time in seconds in took to compute this picture.
	*/
	Picture(unsigned int width, unsigned int height, double renderTime = -1);
	
	//! Copy constructor
	/*!
		\param picture The picture that will be copied.
	*/
	Picture(const Picture& picture);

	//! Destructor.
	~Picture();

	//! Getter for the width.
	/*!
		\return The camera width.
	*/
	unsigned int getWidth() const;

	//! Getter for the height.
	/*!
		\return The camera height.
	*/
	unsigned int getHeight() const;

	//! Getter for the render time.
	/*!
		\return The time it took to compute this picture.
	*/
	double getRenderTime() const;

	//! Getter for the pixels.
	/*!
		\return A std::vector of std::vector that contains the luminance at each pixel.
	*/
	std::vector<std::vector<DoubleVec3D>> getPixels() const;


	//! Adds a value to a pixel.
	/*!
		\param x The *x* coordinate of the pixel.
		\param y The *y* coordinate of the pixel.
		\param value The value that will be added to that pixel.
	*/
	void addValuePix(unsigned int x, unsigned int y, DoubleVec3D value);

	//! Sets a pixel value.
	/*!
		\param x The *x* coordinate of the pixel.
		\param y The *y* coordinate of the pixel.
		\param value The value to which that pixel will be set.
	*/
	void setValuePix(unsigned int x, unsigned int y, DoubleVec3D value);

	//! Setter for the render time.
	/*!
		This method can be used if the time was not set when the picture was instanciated (which is very likely to happen).
		\param renderTime The new time this picture took to be computed.
	*/
	void setRenderTime(double renderTime);


	//! Concerts a luminance to a colour value.
	/*!
		This is a very naive tone mapping. See my TM's report for more explanations.
		\param luminance The luminance we want to convert.
		\param middleGray The luminance value that corresponds to the middle-gray.
		\return The colour that has been computed. Each part of the colour (red, green or blue) range from 0 to maxColourValue.
	*/
	DoubleVec3D toneMapping(const DoubleVec3D& luminance, double middleGray) const;

	//! Computes the value of a pixel when having applied a moving average.
	/*!
		\param pixelValues The values of all pixels (can be luminance or colour).
		\param pixelX The *x* coordinate of the pixel.
		\param pixelY the *y* coordinate of the pixel.
		\param size The size of the moving average.
		\return The colour at that pixel after having applied the moving average.
	*/
	DoubleVec3D getColourMovingAverage(const std::vector<std::vector<DoubleVec3D>>& pixelValues, unsigned int pixelX, unsigned int pixelY, unsigned int size) const;
	
	//! Writes this as a picture file.
	/*!
		\param middleGray The middle-gray value that will be used for the toneMapping() function.
		\param fileName The path to the file where we want to write this picture.
		\param movingAverage The size of the moving average (see getColourMovingAverage()).
		\sa toneMapping(), getColourMovingAverage()
	*/
	void writeToFile(double middleGray, std::string fileName, unsigned int movingAverage = 0) const;

	//! Interactive modification of this picture.
	/*!
		This is a page on its own. It allows the user to write the picture under different names, different middle-gray values and different moving average size.
		\sa writeToFile(), toneMapping(), getColourMovingAverage()
	*/
	void modify();
};

//! Conversion to json.
/*!
	\param j Json output.
	\param picture The picture that will be converted to json.
	\warning This is a very inefficient way to store a picture. Only use it to make temporary backups.
*/
void to_json(json& j, const Picture& picture);

//! Imports a picture out of json.
/*!
	\param j The json input.
	\return The imported picture.
*/
Picture importPictureFromJson(const json& j);

#endif

