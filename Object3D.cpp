#include "Object3D.h"

// Constructors and destructor
Object3D::Object3D()
	: name("none"), material(new DiffuseMaterial) {}

Object3D::Object3D(const std::string& name, Material* material)
	: name(name), material(material) {}

Object3D::Object3D(const Object3D& obj)  {
	operator=(obj);
}

Object3D::~Object3D() { delete material; }


// Getters & Setters
std::string Object3D::getName() const { return name; }
Material* Object3D::getMaterial() const { return material; }

void Object3D::setName(const std::string& name) { this->name = name; }
void Object3D::setMaterial(Material* material) { this->material = material; }


// Ostream operator
std::ostream& operator<<(std::ostream& stream, const Object3D& object) {
	return object.getDescription(stream) << std::endl << "-> " << *(object.getMaterial());
}

Object3D& Object3D::operator=(const Object3D& otherObject) {
	name = otherObject.name;
	material = otherObject.material->deepCopy();
	return *this;
}