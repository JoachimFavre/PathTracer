#include "Object3DGroup.h"

// Constructors and destructors
Object3DGroup::Object3DGroup()
	: name("none"), objects(), center(0.0) {}

Object3DGroup::Object3DGroup(const std::string& name, std::initializer_list<Object3D*> objectsInitList)
	: name(name) {
	setObjects(objectsInitList);
}

Object3DGroup::Object3DGroup(const Object3DGroup& group)
	: name(group.name), objects(group.objects), center(group.center) {}

Object3DGroup::~Object3DGroup() {
	resetObjects();
}


// Getters
std::string Object3DGroup::getName() const { return name; }
std::vector<Object3D*> Object3DGroup::getObjects() const { return objects; }
DoubleVec3D Object3DGroup::getCenter() const { return center; }


// Setters
void Object3DGroup::setName(const std::string& name) { this->name = name; }

void Object3DGroup::setObjects(const std::vector<Object3D*>& newObjects) { 
	resetObjects();
	addObjects(newObjects);
}


// Objects list management
void Object3DGroup::addObject(Object3D* object) { 
	std::vector<Object3D*> objectInVector;
	objectInVector.push_back(object);
	addObjects(objectInVector);
}

void Object3DGroup::addObjects(const std::vector<Object3D*>& newObjects) {
	unsigned int totalNumberObjects = objects.size() + newObjects.size();
	if (totalNumberObjects > 0) {
		center *= objects.size() / totalNumberObjects;
		for (Object3D* object : newObjects) {
			objects.push_back(object);
			center += object->getCenter() / totalNumberObjects;
		}
	}
}

void Object3DGroup::merge(const Object3DGroup& group) {	addObjects(group.getObjects()); }

void Object3DGroup::resetObjects() {
	for (Object3D* object : objects)
		delete object;
	objects.clear();
}


// Ostream operator
std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group) {
	stream << group.getName() << std::endl;
	
	unsigned int numberObjects = group.getObjects().size();

	if (numberObjects == 0)
		stream << "EMPTY" << std::endl;
	else if (numberObjects == 1)
		stream << group.getObjects()[0];
	else
		stream << "Center = " << group.getCenter() << " / " << group.getObjects.size() << " objects";
}
