#include <fstream>
#include <iostream>;
#include <string>;

#include "DoubleVec3D.h"

#ifndef DEF_PICTURE
#define DEF_PICTURE

class Picture
{
private:
	const unsigned int width;
	const unsigned int height;
	DoubleVec3D** pixels;

public:
	Picture();
	Picture(unsigned int width, unsigned int height);
	Picture(const Picture& picture);
	~Picture();

	unsigned int getWidth();
	unsigned int getHeight();

	void addValuePix(unsigned int x, unsigned int y, DoubleVec3D value);
	void setValuePix(unsigned int x, unsigned int y, DoubleVec3D value);

	void write(double middleGray, std::string fileName = "picture");
};

#endif

