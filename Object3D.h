#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include <string>

#include "DiffuseMaterial.h"

/*!
    \file Object3D.h
    \brief Defines the Object3D class and some functions around it.

    \class Object3D
    \brief Abstract class for a three-dimentional object.

    \var double Object3D::area
    \brief Stores the area of this object.
    \details It is computed every time the object coordinates are modified.
    \sa Object3D::getArea(), Object3D::computeArea()

    \fn Object3D::Object3D()
    \brief Default constructor.
    \details The default material is a diffuse one.

    \fn Object3D::Object3D(Material* material)
    \brief Main constructor.
    \param material The material of this object.

    \fn Object3D::Object3D(const Object3D& obj)
    \brief Copy constructor.
    \details Calls Object3D::operator=().
    \param obj The object that will be copied.
    \sa Object3D::operator=().

    \fn Object3D::~Object3D()
    \brief Destructor.

    \fn Material* Object3D::getMaterial()
    \brief Getter for the Material.
    \return A pointer to this object's material.

    \fn double Object3D::getArea()
    \brief Getter for this object's area.
    \return This object's area.
    \sa Object3D::area, Object3D::computeArea()

    \fn void Object3D::setMaterial(Material* material)
    \brief Setter for the Material.
    \param material The new material of this object.

    \fn virtual void Object3D::computeArea() = 0
    \brief Computes this object area.
    \details Modifies Object3D::area.
    \sa Object3D::area, Object3D::getArea()

    \fn virtual Object3D* Object3D::deepCopy() = 0
    \brief Makes a deep copy of this object.
    \return A pointer to a deeply copied version of this object.

    \fn virtual double Object3D::smallestPositiveIntersection(const Ray& ray) = 0
    \brief Computes the smallest positive intersection between the ray and this object.
    \param ray The ray with wich we want to compute the intersection.
    \return The distance between the ray origin and the intersection (the smallest one if there is more than one intersection). Returns -1 if the ray does not intersect with this object.

    \fn virtual DoubleUnitVec3D Object3D::getNormal(const DoubleVec3D& point) = 0
    \brief Computes the normal at a point on the object.
    \param point The point on the object at which we want to compute the normal.
    \return The normal at this point.

    \fn virtual DoubleVec3D Object3D::getRandomPoint() = 0
    \brief Computes a random point on the object.
    \details Every point has the same probability to show up.
    \return A random point on this object.

    \fn virtual std::ostream& Object3D::getDescription(std::ostream& stream) = 0
    \brief Returns this object's description.
    \param stream The current stream.
    \return The stream with the description.
    \sa operator<<(std::ostream& stream, const Object3D& object)

    \fn virtual DoubleVec3D Object3D::getCenter() = 0
    \brief Returns this object's center.
    \return The center of this object.

    \fn virtual DoubleVec3D Object3D::getMinCoord() = 0
    \brief Returns the minimum coordinate of a cuboid containing this object.
    \return The minimum coordinate of a cuboid containing this object.
    \sa getMinPoint(std::vector<Object3D*> objects)

    \fn virtual DoubleVec3D Object3D::getMaxCoord() = 0
    \brief Returns the maximum coordinate of a cuboid containing this object.
    \return The maximum coordinate of a cuboid containing this object.
    \sa getMaxPoint(std::vector<Object3D*> objects)

    \fn virtual std::string Object3D::getType() = 0
    \brief Returns this object type.
    \return Returns "Sphere" or "Triangle", depending on the object instance.

    \fn virtual json Object3D::getLocationJson() = 0
    \brief Converts this objects's location to json.
    \return This object's location converted to json.

    \fn virtual void Object3D::setLocationJson(const json& j) = 0
    \brief Sets this object's location according to json.
    \param j The json input.

    \fn Object3D& Object3D::operator=(const Object3D& otherObject)
    \brief Assignment operator.
    \details Makes a deepcopy of the material before copying it.
    \param otherObject The object to which this will be equal.
    \sa Object3D::Object3D(const Object3D& obj)

    \fn std::ostream& operator<<(std::ostream& stream, const Object3D& object)
    \brief Ostream operator.
    \details Calls the Object3D::getDescription() method.
    \param stream The ostream before.
    \param object The object that will be added to the stream.
    \return The stream with the object added.
    \sa Object3D::getDescription()
*/

class Object3D {
private:
    Material* material;

protected:
    double area;

public:
    Object3D();
    Object3D(Material* material);
    Object3D(const Object3D& obj);
    ~Object3D();

    Material* getMaterial() const;
    double getArea() const;
    void setMaterial(Material* material);

    virtual void computeArea() = 0;
    virtual Object3D* deepCopy() const = 0;

    virtual double smallestPositiveIntersection(const Ray& ray) const = 0;
    virtual DoubleUnitVec3D getNormal(const DoubleVec3D& point) const = 0;
    virtual DoubleVec3D getRandomPoint() const = 0;
    virtual std::ostream& getDescription(std::ostream& stream) const = 0;
    virtual DoubleVec3D getCenter() const = 0;
    virtual DoubleVec3D getMinCoord() const = 0;
    virtual DoubleVec3D getMaxCoord() const = 0;

    virtual std::string getType() const = 0;
    virtual json getLocationJson() const = 0;
    virtual void setLocationJson(const json& j) = 0;

    Object3D& operator=(const Object3D& otherObject);
};

std::ostream& operator<<(std::ostream& stream, const Object3D& object);

#endif
