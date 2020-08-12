#include "Object3DGroup.h"

// Constructors
Object3DGroup::Object3DGroup()
	: name("none"), objects(), center() {}

Object3DGroup::Object3DGroup(std::string name, std::initializer_list<Object3D*> objectsInitList)
	: name(name) {

	unsigned int numberObjects = objectsInitList.size();

	for (Object3D* object : objectsInitList) {
		center += object->getCenter()/numberObjects;
		objects.push_back(object);
	}
}

Object3DGroup::Object3DGroup(const Object3DGroup& group)
	: name(group.name), objects(group.objects), center(group.center) {}

