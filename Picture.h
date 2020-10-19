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

class Picture
{
private:
	const unsigned int width;
	const unsigned int height;
	double renderTime;
	DoubleVec3D** pixels;

public:
	static constexpr unsigned int maxColourValue = 255;  // must be in [1, 65536]

	Picture();
	Picture(unsigned int width, unsigned int height, double renderTime = -1);
	Picture(const Picture& picture);
	~Picture();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	double getRenderTime() const;
	std::vector<std::vector<DoubleVec3D>> getPixels() const;

	void addValuePix(unsigned int x, unsigned int y, DoubleVec3D value);
	void setValuePix(unsigned int x, unsigned int y, DoubleVec3D value);
	void setRenderTime(double renderTime);

	DoubleVec3D toneMapping(const DoubleVec3D& luminance, double middleGray) const;
	DoubleVec3D getColourMovingAverage(const std::vector<std::vector<DoubleVec3D>>& pixelValues, unsigned int pixelX, unsigned int pixelY, unsigned int size) const;
	void writeToFile(double middleGray, std::string fileName, unsigned int movingAverage = 0) const;
	void modify();
};

void to_json(json& j, const Picture& picture);
Picture importPictureFromJson(const json&);

#endif

