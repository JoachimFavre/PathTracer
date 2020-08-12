#include "Object3DGroup.h"

// Constructors
Object3DGroup::Object3DGroup()
	: name("none"), objects(), center(0.0) {}

Object3DGroup::Object3DGroup(const std::string& name, std::initializer_list<Object3D*> objectsInitList)
	: name(name) {
	setObjects(objectsInitList);
}

Object3DGroup::Object3DGroup(const Object3DGroup& group)
	: name(group.name), objects(group.objects), center(group.center) {}


// Getters
std::string Object3DGroup::getName() const { return name; }
std::vector<Object3D*> Object3DGroup::getObjects() const { return objects; }
DoubleVec3D Object3DGroup::getCenter() const { return center; }

// Setters
void Object3DGroup::setName(const std::string& name) { this->name = name; }

void Object3DGroup::setObjects(const std::vector<Object3D*>& newObjects) { 
	this->objects = newObjects; 
	center = DoubleVec3D(0.0);

	unsigned int numberNewObjects = newObjects.size();
	for (Object3D* object : newObjects)
		center += object->getCenter() / numberNewObjects;
}

