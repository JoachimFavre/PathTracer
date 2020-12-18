#include "Picture.h"

// Constructors & Destructors
Picture::Picture() : Picture(500, 500) {}

Picture::Picture(unsigned int width, unsigned int height, double renderTime /* = -1*/) : width(width), height(height), renderTime(renderTime) {
    pixels = new DoubleVec3D*[width];
    for (int pixelX = 0; pixelX < width; pixelX++) {
        pixels[pixelX] = new DoubleVec3D[height];
        for (int pixelY = 0; pixelY < height; pixelY++)
            pixels[pixelX][pixelY] = 0.0;
    }
}

Picture::Picture(const Picture& picture) : Picture(picture.width, picture.height, picture.renderTime) {}

Picture::~Picture() {
    for (int pixelX = 0; pixelX < width; pixelX++)
        delete pixels[pixelX];
    delete pixels;
}


// Getters
unsigned int Picture::getWidth() const { return width; }
unsigned int Picture::getHeight() const { return height; }
double Picture::getRenderTime() const { return renderTime; }

std::vector<std::vector<DoubleVec3D>> Picture::getPixels() const {
    std::vector<std::vector<DoubleVec3D>> result;
    for (int pixelX = 0; pixelX < width; pixelX++) {
        std::vector<DoubleVec3D> column;
        for (int pixelY = 0; pixelY < height; pixelY++) {
            column.push_back(pixels[pixelX][pixelY]);
        }
        result.push_back(column);
    }
    return result;
}

// Modify pixels
void Picture::addValuePix(unsigned int x, unsigned int y, DoubleVec3D value) { pixels[x][y] += value; }
void Picture::setValuePix(unsigned int x, unsigned int y, DoubleVec3D value) { pixels[x][y] = value; }
void Picture::setRenderTime(double renderTime) { this->renderTime = renderTime; }

// Other methods
void Picture::writeToFile(double middleGray, std::string fileName, unsigned int movingAverageSize /*= 0*/) const {
    double writingBeginningTime = getCurrentTimeSeconds();

    std::vector<std::vector<DoubleVec3D>> pixelValues;
    for (unsigned int pixelX = 0; pixelX < width; pixelX++) {
        std::vector<DoubleVec3D> column;
        for (unsigned int pixelY = 0; pixelY < height; pixelY++) {
            column.push_back(toneMapping(pixels[pixelX][pixelY], middleGray));
        }
        pixelValues.push_back(column);
    }


    std::ofstream file;
    file.open("temp.ppm");
    file << "P3" << std::endl << width << " " << height << " " << MAX_COLOUR_VALUE << std::endl;
    for (unsigned int pixelY = 0; pixelY < height; pixelY++) {
        for (unsigned int pixelX = 0; pixelX < width; pixelX++) {
            DoubleVec3D currentColour = getColourMovingAverage(pixelValues, pixelX, pixelY, movingAverageSize);
            file << (int)(currentColour.getX()) << " ";
            file << (int)(currentColour.getY()) << " ";
            file << (int)(currentColour.getZ()) << std::endl;
        }
    }
    file.close();

    cimg_library::CImg<unsigned char> image("temp.ppm");
    remove("temp.ppm");
    image.save(fileName.c_str());

    std::cout << "The picture was successfully written in " << fileName << " file with " << middleGray << " being the middle gray in " << getCurrentTimeSeconds() - writingBeginningTime << " seconds!" << std::endl;
    system((".\\" + fileName).c_str());
}

void Picture::printAll() const {
    clearScreenPrintHeader();

    std::cout << "Picture" << std::endl << DASH_SPLITTER << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Render time: " << renderTime << "s " << std::endl;
    std::cout << std::endl;


    availableCommandsHeader();
    std::cout << "- b: leave this page" << std::endl;
    std::cout << "- e: export this picture as a " << PICTURE_EXTENSION << " file" << std::endl;
    std::cout << "- s: save this picture as a " << PICTURE_SAVE_EXTENSION_JSON << " file" << std::endl;
}

void Picture::modify() {
    bool commandWasInvalid = false;
    while (true) {
        printAll();
        std::cout << std::endl;
        if (commandWasInvalid) {
            std::cout << INVALID_COMMAND << std::endl;
        }

        char command = getLowerCaseCharFromUser();

        if (commandWasInvalid) {
            // Reprint everything to remove the "invalid command"
            printAll();
            std::cout << std::endl << PROMPT << command << std::endl;
            commandWasInvalid = false;
        }

        std::cout << std::endl;

        switch (command) {
        case 'b': return;
        case 'e': {
            std::string fileName = getStringFromUser("What is the name of the " + PICTURE_EXTENSION + " file in which the picture will be exported?");
            fileName = formatFileName(fileName, PICTURE_EXTENSION);
            std::cout << std::endl;

            if (fileExists(fileName)) {
                bool continue_ = getBoolFromUser("The file " + fileName + " already exists, do you want to continue? (True=T=true=t / False=F=false=f)");
                if (!continue_)
                    break;
                std::cout << std::endl;
            }

            double middleGray = getPositiveDoubleFromUser("What radiance will be the middle-gray? (try 10 if you have no idea) (positive number)");
            std::cout << std::endl;
            unsigned int movingAverageSize = getUnsignedIntFromUser("What is the size of the moving average you want to use? (0 for no moving average) (positive integer)");

            writeToFile(middleGray, fileName, movingAverageSize);

            std::cout << std::endl;
            getStringFromUser("Press enter to continue.");
            break;
        }
        case 's': {
            std::string fileName = getStringFromUser("What is the name of the " + PICTURE_SAVE_EXTENSION_JSON + " file in which the picture will be saved?");
            fileName = formatFileName(fileName, PICTURE_SAVE_EXTENSION_JSON);
            std::cout << std::endl;
            double beginningTime = getCurrentTimeSeconds();

            json jsonOutput = *this;

            std::ofstream file;
            file.open(fileName);
            file << std::setw(4) << jsonOutput << std::endl;
            file.close();

            std::cout << "Successfully saved picture to " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
            break;
        }
        default: commandWasInvalid = true;
        }
    }
}


// Other functions
DoubleVec3D toneMapping(const DoubleVec3D& radiance, double middleGray) {
    // Very naive tone mapping
    double x = Picture::MAX_COLOUR_VALUE*radiance.getX() / (middleGray + radiance.getX());
    double y = Picture::MAX_COLOUR_VALUE*radiance.getY() / (middleGray + radiance.getY());
    double z = Picture::MAX_COLOUR_VALUE*radiance.getZ() / (middleGray + radiance.getZ());

    return DoubleVec3D(x, y, z);
}

DoubleVec3D getColourMovingAverage(const std::vector<std::vector<DoubleVec3D>>& pixelValues, unsigned int pixelX, unsigned int pixelY, unsigned int size) {
    if (size == 0)
        return pixelValues[pixelX][pixelY];

    int pixelXInt = (int)pixelX;
    int pixelYInt = (int)pixelY;
    int sizeInt = (int)size;

    int width = pixelValues.size();
    int height = pixelValues[0].size();

    // Decide not to change the picture size
    int minPixX = std::max(0, pixelXInt - sizeInt);
    int minPixY = std::max(0, pixelYInt - sizeInt);
    int maxPixX = std::min((int)width - 1, pixelXInt + sizeInt);
    int maxPixY = std::min((int)height - 1, pixelYInt + sizeInt);

    DoubleVec3D result(0.0);
    unsigned int numberPixels = (maxPixX - minPixX + 1)*(maxPixY - minPixY + 1);  // not (2*size + 1)^2 because smaller if near an edge

    for (unsigned int y = minPixY; y <= maxPixY; y++) {
        for (unsigned int x = minPixX; x <= maxPixX; x++) {
            result += pixelValues[x][y] / numberPixels;
        }
    }

    return result;
}


// json
void to_json(json& j, const Picture& picture) {
    j = { {"Width", picture.getWidth()}, {"Height", picture.getHeight()}, {"RenderTime", picture.getRenderTime()}, {"Pixels", picture.getPixels()} };
}


Picture importPictureFromJson(const json& j) {
    unsigned int width = j["Width"].get<unsigned int>();
    unsigned int height = j["Height"].get<unsigned int>();
    double renderTime = j["RenderTime"].get<double>();
    std::vector<std::vector<DoubleVec3D>> pixels = j["Pixels"].get<std::vector<std::vector<DoubleVec3D>>>();
    Picture result(width, height, renderTime);
    
    for (int pixelX = 0; pixelX < width; pixelX++) {
        std::vector<DoubleVec3D> column = pixels[pixelX];
        for (int pixelY = 0; pixelY < height; pixelY++) {
            result.setValuePix(pixelX, pixelY, column[pixelY]);
        }
    }

    return result;
}