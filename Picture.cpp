#include "Picture.h"

// Constructors & Destructors
Picture::Picture() : Picture(500, 500) {}

Picture::Picture(unsigned int width, unsigned int height) : width(width), height(height) {
	pixels = new DoubleVec3D*[width];
	for (int pixelX = 0; pixelX < width; pixelX++) {
		pixels[pixelX] = new DoubleVec3D[height];
		for (int pixelY = 0; pixelY < height; pixelY++)
			pixels[pixelX][pixelY] = 0.0;
	}
}

Picture::Picture(const Picture& picture) : Picture(picture.width, picture.height) {}

Picture::~Picture() {
	for (int pixelX = 0; pixelX < width; pixelX++)
		delete pixels[pixelX];
	delete pixels;
}


// Getters
unsigned int Picture::getWidth() const { return width; }
unsigned int Picture::getHeight() const { return height; }

// Modify pixels
void Picture::addValuePix(unsigned int x, unsigned int y, DoubleVec3D value) { pixels[x][y] += value; }
void Picture::setValuePix(unsigned int x, unsigned int y, DoubleVec3D value) { pixels[x][y] = value; }

// Other methods
void Picture::writeToFile(double middleGray, std::string fileName /* = "picture"*/) const {
	std::ofstream file;
	file.open(fileName + ".ppm");
	file << "P3" << std::endl << width << " " << height << std::endl << "255" << std::endl;
	for (unsigned int pixelY = 0; pixelY < height; pixelY++) {
		for (unsigned int pixelX = 0; pixelX < width; pixelX++) {
			DoubleVec3D currentColour = pixels[pixelX][pixelY];
			// Very naive tone mapping
			file << (int)(255 * currentColour.getX() / (middleGray + currentColour.getX())) << " ";
			file << (int)(255 * currentColour.getY() / (middleGray + currentColour.getY())) << " ";
			file << (int)(255 * currentColour.getZ() / (middleGray + currentColour.getZ())) << std::endl;
		}
	}
	file.close();
}