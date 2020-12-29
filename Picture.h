#ifndef DEF_PICTURE
#define DEF_PICTURE

#include <algorithm>
#include <iomanip>

#include "CImg/CImg.h"

#include "DoubleVec3D.h"

/*!
    \file Picture.h
    \brief Defines the Picture class and the functions around it.

    \class Picture
    \brief Stores radiance for every pixel.

    \var static constexpr unsigned int Picture::MAX_COLOUR_VALUE
    \brief The maximum value that will be used to write a colour in a file.
    \sa toneMapping()

    \fn Picture::Picture()
    \brief Default constructor.
    \details By default, width and height are both set to 500.

    \fn Picture::Picture(unsigned int width, unsigned int height, double renderTime = -1)
    \brief Main constructor
    \details All pixels are set to (0, 0, 0).
    \param width The picture width.
    \param height The picture height.
    \param renderTime The time in seconds in took to compute this picture.

    \fn Picture::Picture(const Picture& picture)
    \brief Copy constructor
    \param picture The picture that will be copied.

    \fn Picture::~Picture()
    \brief Destructor.

    \fn unsigned int Picture::getWidth()
    \brief Getter for the width.
    \return The camera width.

    \fn unsigned int Picture::getHeight()
    \brief Getter for the height.
    \return The camera height.

    \fn double Picture::getRenderTime()
    \brief Getter for the render time.
    \return The time it took to compute this picture.

    \fn std::vector<std::vector<DoubleVec3D>> Picture::getPixels()
    \brief Getter for the pixels.
    \return A std::vector of std::vector that contains the radiance at each pixel.

    \fn void Picture::addValuePix(unsigned int x, unsigned int y, DoubleVec3D value)
    \brief Adds a value to a pixel.
    \param x The *x* coordinate of the pixel.
    \param y The *y* coordinate of the pixel.
    \param value The value that will be added to that pixel.

    \fn void Picture::setValuePix(unsigned int x, unsigned int y, DoubleVec3D value)
    \brief Sets a pixel value.
    \param x The *x* coordinate of the pixel.
    \param y The *y* coordinate of the pixel.
    \param value The value to which that pixel will be set.

    \fn void Picture::setRenderTime(double renderTime)
    \brief Setter for the render time.
    \details This method can be used if the time was not set when the picture was instanciated (which is very likely to happen).
    \param renderTime The new time this picture took to be computed.

    \fn void Picture::export2File(double middleGrey, std::string fileName, unsigned int movingAverage = 0)
    \brief Writes this as a picture file.
    \details Uses the CImg library.
    \param middleGrey The middle-grey value that will be used for the toneMapping() function.
    \param fileName The path to the file where we want to write this picture. If it is "-", it will give a very nice bugged result. This could be easily fixed, but it is very fun and purely nondestructive.
    \param movingAverage The size of the moving average (see getColourMovingAverage()).
    \sa toneMapping(), getColourMovingAverage()

    \fn void Picture::printAll()
    \brief Prints the whole page.
    \details Clears the page, prints the header, information and the available commands.
    \sa clearScreenPrintHeader()

    \fn void Picture::modify()
    \brief Interactive modification of this picture.
    \details This is a page on its own. It allows the user to write the picture under different names, different middle-grey values and different moving average size.
    \sa writeToFile(), toneMapping(), getColourMovingAverage()

    \fn DoubleVec3D toneMapping(const DoubleVec3D& radiance, double middleGrey)
    \brief Converts a radiance to a colour value.
    \details This is a very naive tone mapping. See my TM's report for more explanations.
    \param radiance The radiance we want to convert.
    \param middleGrey The radiance value that corresponds to the middle-grey.
    \return The colour that has been computed. Each part of the colour (red, green or blue) range from 0 to MAX_COLOUR_VALUE.

    \fn DoubleVec3D getColourMovingAverage(const std::vector<std::vector<DoubleVec3D>>& pixelValues, unsigned int pixelX, unsigned int pixelY, unsigned int size)
    \brief Computes the value of a pixel when having applied a moving average.
    \param pixelValues The values of all pixels (can be radiance or colour value, depending whether you first use the toneMapping function or not).
    \param pixelX The *x* coordinate of the pixel.
    \param pixelY the *y* coordinate of the pixel.
    \param size The size of the moving average.
    \return The colour at that pixel after having applied the moving average.

    \fn void to_json(json& j, const Picture& picture)
    \brief Conversion to json.
    \param j Json output.
    \param picture The picture that will be converted to json.
    \warning This is a very inefficient way to store a picture. Only use it to make temporary backups.

    \fn Picture importPictureFromJson(const json& j)
    \brief Imports a picture out of json.
    \param j The json input.
    \return The imported picture.
*/

class Picture {
private:
    const unsigned int width;
    const unsigned int height;
    double renderTime;
    DoubleVec3D** pixels;

public:
    static constexpr unsigned int MAX_COLOUR_VALUE = 255;

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

    void export2File(double middleGrey, std::string fileName, unsigned int movingAverage = 0) const;
    void printAll() const;
    void modify();
};

DoubleVec3D toneMapping(const DoubleVec3D& radiance, double middleGrey);
DoubleVec3D getColourMovingAverage(const std::vector<std::vector<DoubleVec3D>>& pixelValues, unsigned int pixelX, unsigned int pixelY, unsigned int size);

void to_json(json& j, const Picture& picture);
Picture importPictureFromJson(const json& j);

#endif

