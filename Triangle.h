#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "Object3D.h"

/*!
    \file Triangle.h
    \brief Defines the Triangle class.

    \class Triangle
    \brief A triangle defined by its three vertices.
    \details The order of its vertices is important. See the main constructor for more information.

    \fn Triangle::Triangle()
    \brief Default constructor.
    \details Defines vertex0 = (1, 0, 0), vertex1 = (0, 1, 0) and vertex2 = (0, 0, 1)

    \fn Triangle::Triangle(const DoubleVec3D& vertex0, const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, Material* material)
    \brief Main constructor
    \details The order of the vertices is important, because the normal is only on one side of the triangle (meaning that the triangle can only be seen from one side). Give the vertices counterclockwise from where you want the triangle to be visible.
    \param vertex0 The first vertex of this triangle.
    \param vertex1 The second vertex of this triangle.
    \param vertex2 The third vertex of this triangle.
    \param material A pointer to the material of this triangle.

    \fn Triangle::Triangle(const Triangle& triangle)
    \brief Copy constructor.
    \param triangle The triangle that will be copied.

    \fn DoubleVec3D Triangle::getVertex0()
    \brief Getter for the first vertex.
    \return This triangle's first vertex.

    \fn DoubleVec3D Triangle::getVertex1()
    \brief Getter for the second vertex.
    \return This triangle's second vertex.

    \fn DoubleVec3D Triangle::getVertex2()
    \brief Getter for the third vertex.
    \return This triangle's third vertex.

    \fn DoubleVec3D Triangle::getCenter()
    \brief Getter for the center.
    \return The average of the three vertices.

    \fn void Triangle::setVertex0(const DoubleVec3D& vertex)
    \brief Setter for the first vertex.
    \param vertex The new first vertex of this triangle.

    \fn void Triangle::setVertex1(const DoubleVec3D& vertex)
    \brief Setter for the second vertex.
    \param vertex The new second vertex of this triangle.

    \fn void Triangle::setVertex2(const DoubleVec3D& vertex)
    \brief Setter for the third vertex.
    \param vertex The new third vertex of this triangle.

    \fn void Triangle::computeArea()
    \brief Computes this triangle's area.
    \details Modifies Object3D::area. It uses the formula A = 0.5 * ||edge1 x edge2||.

    \fn Object3D* Triangle::deepCopy()
    \brief Makes a deep copy of this object.
    \return A pointer to a deeply copied version of this object.

    \fn double Triangle::closestIntersection(const Ray& ray)
    \brief Computes the closest intersection between the ray and this object.
    \param ray The ray with wich we want to compute the intersection.
    \return The distance between the ray origin and the intersection. Returns -1 if the ray does not intersect with the object.

    \fn DoubleUnitVec3D Triangle::getNormal(const DoubleVec3D& point)
    \brief Computes the normal at a point on the object.
    \param point The point on the object at which we want to compute the normal.
    \return The cross product between (vertex1 - vertex0) and (vertex2 - vertex0)

    \fn DoubleVec3D Triangle::getRandomPoint()
    \brief Computes a random point on the object.
    \return A random point on this object.

    \fn DoubleVec3D Triangle::getMinCoord()
    \brief Returns the minimum coordinate of a cuboid containing this object.
    \details For each axis, picks the smallest coordinate among the three vertices.
    \return The minimum coordinate of a cuboid containing this object.

    \fn DoubleVec3D Triangle::getMaxCoord()
    \brief Returns the maximum coordinate of a cuboid containing this object.
    \details For each axis, picks the greatest coordinate among the three vertices.
    \return The maximum coordinate of a cuboid containing this object.

    \fn std::ostream& Triangle::getDescription(std::ostream& stream)
    \brief Returns this object's description.
    \param stream The current stream.
    \return The stream with the description.

    \fn std::string Triangle::getType()
    \brief Returns this object type.
    \return "Triangle".

    \fn json Triangle::getLocationJson()
    \brief Converts this objects's location to json.
    \return This triangle's vertices converted to json.

    \fn void Triangle::setLocationJson(const json& j)
    \brief Sets this object's location according to json.
    \param j The json input.
*/

class Triangle : public Object3D {
private:
    DoubleVec3D vertex0, vertex1, vertex2;

public:
    Triangle();
    Triangle(const DoubleVec3D& vertex0, const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, Material* material);
    Triangle(const Triangle& triangle);

    DoubleVec3D getVertex0() const;
    DoubleVec3D getVertex1() const;
    DoubleVec3D getVertex2() const;
    DoubleVec3D getCenter() const;  // virtual method

    void setVertex0(const DoubleVec3D& vertex);
    void setVertex1(const DoubleVec3D& vertex);
    void setVertex2(const DoubleVec3D& vertex);

    void computeArea();
    Object3D* deepCopy() const;

    double closestIntersection(const Ray& ray) const;
    DoubleUnitVec3D getNormal(const DoubleVec3D& point) const;
    DoubleVec3D getRandomPoint() const;
    DoubleVec3D getMinCoord() const;
    DoubleVec3D getMaxCoord() const;

    std::ostream& getDescription(std::ostream& stream) const;
    std::string getType() const;
    json getLocationJson() const;
    void setLocationJson(const json& j);
};

#endif