#include "Object3D.h"

// Constructors and destructor
Object3D::Object3D()
    : material(new DiffuseMaterial) {}

Object3D::Object3D(Material* material)
    : material(material) {}

Object3D::Object3D(const Object3D& obj)  {
    operator=(obj);
}

Object3D::~Object3D() { delete material; }


// Getters & Setters
Material* Object3D::getMaterial() const { return material; }
double Object3D::getArea() const { return area; }
void Object3D::setMaterial(Material* material) { this->material = material; }


// Ostream operator
std::ostream& operator<<(std::ostream& stream, const Object3D& object) {
    return object.getDescription(stream) << std::endl << "-> " << *(object.getMaterial());
}

Object3D& Object3D::operator=(const Object3D& otherObject) {
    material = otherObject.material->deepCopy();
    return *this;
}