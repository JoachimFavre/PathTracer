#ifndef DEF_PICTURE
#define DEF_PICTURE

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "CImg/CImg.h"

#include "DoubleVec3D.h"

static double getCurrentTimeSeconds() {
	return (double)std::chrono::system_clock::now().time_since_epoch().count() / std::chrono::system_clock::period::den;
}

class Picture
{
private:
	const unsigned int width;
	const unsigned int height;
	DoubleVec3D** pixels;

public:
	static constexpr unsigned int maxColourValue = 255;  // must be in [1, 65536]

	Picture();
	Picture(unsigned int width, unsigned int height);
	Picture(const Picture& picture);
	~Picture();

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void addValuePix(unsigned int x, unsigned int y, DoubleVec3D value);
	void setValuePix(unsigned int x, unsigned int y, DoubleVec3D value);

	void writeToFile(double middleGray, std::string fileName = "_picture") const;
};

#endif

