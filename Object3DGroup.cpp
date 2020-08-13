#include "Object3DGroup.h"

// Constructors and destructors
Object3DGroup::Object3DGroup()
	: name("None"), objects(), center(0.0) {}

Object3DGroup::Object3DGroup(const std::string& name, std::vector<Object3D*> objects /* = {}*/)
	: name(name) {
	setObjects(objects);
}

Object3DGroup::Object3DGroup(const Object3DGroup& group) {
	operator=(group);
}

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


// Assignment operator
Object3DGroup& Object3DGroup::operator=(const Object3DGroup& otherGroup) {
	name = otherGroup.name;
	center = otherGroup.center;

	std::vector<Object3D*> objectsCopy;
	for (Object3D* object : otherGroup.objects) {
		objectsCopy.push_back(object->deepCopy());
	}
	objects = objectsCopy;

	return *this;
}


// Ostream operator
std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group) {
	stream << group.getName() << std::endl;
	
	std::vector<Object3D*> objects = group.getObjects();
	unsigned int numberObjects = objects.size();

	if (numberObjects == 0)
		stream << "Empty";
	else if (numberObjects == 1)
		stream << *(objects[0]);
	else
		stream << "Center" << group.getCenter() << " / " << numberObjects << " objects";

	return stream;
}


// Other functions
std::vector<Object3D*> split(std::vector<Object3DGroup> groups) {
	std::vector<Object3D*> result;
	
	for (Object3DGroup group : groups) {
		std::vector<Object3D*> currentObjects = group.getObjects();
		std::vector<Object3D*> copy;

		for (Object3D* object : currentObjects)
			copy.push_back(object->deepCopy());

		result.insert(result.end(), copy.begin(), copy.end());
	}

	return result;
}


// For the interface
Object3DGroup Object3DGroup::create() {
	std::string name = getStringFromUser("What is the name of this object group ?");

	return Object3DGroup(name);
}

void Object3DGroup::modify() {
	bool commandWasInvalid = false;
	while (true) {
		clearScreenPrintHeader();

		std::cout << name << std::endl << dashSplitter << std::endl << std::endl;

		for (int i = 0; i < objects.size(); i++) {
			std::cout << i << ") " << *(objects[i]) << std::endl << std::endl;
		}

		availableCommandsHeader();
		std::cout << "- a: add an object" << std::endl;
		std::cout << "- b: go back to the objects page" << std::endl;
		std::cout << "- g: merge an other objects group into this one" << std::endl;
		std::cout << "- m: modify an object" << std::endl;
		std::cout << "- n: change the name of this objects group" << std::endl;
		std::cout << std::endl;


		char command = getCharFromUser(commandWasInvalid ? invalidCommand : "");
		commandWasInvalid = false;
		std::cout << std::endl;

		switch (command) {
		case 'b': return;
		case 'n': {
			std::string newName = getStringFromUser("What is the new name ?");
			name = newName;
			break;
		}
		default: commandWasInvalid = true;
		}
	}
}
