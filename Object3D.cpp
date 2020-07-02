#include "Object3D.h"

// Constructors
Object3D::Object3D() : material() {}

Object3D::Object3D(const Material& material) : material(material) {}

Object3D::Object3D(const Object3D& obj) : material(obj.material) {}


// Getters & Setters
Material Object3D::getMaterial() const { return material; }
void Object3D::setMaterial(const Material& material) { this->material = material; }
