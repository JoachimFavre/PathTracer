#include "Object3D.h"

// Constructors and destructor
Object3D::Object3D()
	: material(new DiffuseMaterial) {}

Object3D::Object3D(Material* material)
	: material(material) {}

Object3D::Object3D(const Object3D& obj)
	: material(obj.material) {}

Object3D::~Object3D() { delete material; }


// Getters & Setters
Material* Object3D::getMaterial() const { return material; }
void Object3D::setMaterial(Material* material) { this->material = material; }
