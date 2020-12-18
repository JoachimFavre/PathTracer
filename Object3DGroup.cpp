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
            objects.push_back(object->deepCopy());
            center += object->getCenter() / totalNumberObjects;
        }
    }
}

void Object3DGroup::merge(const Object3DGroup& group) {    addObjects(group.getObjects()); }

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


// For the interface
Object3DGroup Object3DGroup::create() {
    std::string name = getStringFromUser("What is the name of this object group?");

    return Object3DGroup(name);
}

void Object3DGroup::modify() {
    bool commandWasInvalid = false;
    while (true) {
        clearScreenPrintHeader();

        std::cout << name << std::endl << DASH_SPLITTER << std::endl << std::endl;

        for (int i = 0; i < objects.size(); i++) {
            std::cout << i << ") " << *(objects[i]) << std::endl << std::endl;
        }

        availableCommandsHeader();
        std::cout << "- a: add an object" << std::endl;
        std::cout << "- b: go back to the objects page" << std::endl;
        std::cout << "- d: delete one or all objects" << std::endl;
        std::cout << "- m: modify one or all objects' material" << std::endl;
        std::cout << "- n: change the name of this objects group" << std::endl;
        std::cout << std::endl;


        if (commandWasInvalid) {
            std::cout << INVALID_COMMAND << std::endl;
            commandWasInvalid = false;
        }
        char command = getLowerCaseCharFromUser();
        std::cout << std::endl;

        switch (command) {
        case 'a': {
            Object3D* newObject = createObject3D();
            addObject(newObject);
            break;
        }
        case 'b': return;
        case 'd': {
            if (objects.size() >= 1) {
                while (true) {
                    int index = getIntFromUser("What is the index of the objects groups you want to delete? (-1 = cancel / -2 = delete all)");
                    if (index == -1)
                        break;
                    if (index == -2) {
                        std::cout << std::endl;
                        bool confirmation = getBoolFromUser("Do you confirm the deletion of all the objects? (True=T=true=t / False=F=false=f)");
                        if (confirmation)
                            objects.clear();
                        break;
                    }
                    if (index >= 0 && index < objects.size()) {
                        std::cout << std::endl;
                        bool confirmation = getBoolFromUser("Do you confirm the deletion of this object? (True=T=true=t / False=F=false=f)");
                        if (confirmation)
                            objects.erase(objects.begin() + index);
                        break;
                    }
                    std::cout << "This index is invalid!" << std::endl << std::endl;
                }
            }
            else
                commandWasInvalid = true;
            break;
        }
        case 'm': {
            if (objects.size() >= 1) {
                while (true) {
                    int index = getIntFromUser("What is the index of the object whose material you want to modify? (-1 = cancel / -2 = modify all)");
                    if (index == -1)
                        break;
                    if (index == -2) {
                        std::cout << std::endl;
                        Material* newMaterial = createMaterial();
                        for (Object3D* object : objects)
                            object->setMaterial(newMaterial);
                        break;
                    }
                    if (index >= 0 && index < objects.size()) {
                        std::cout << std::endl;
                        Material* newMaterial = createMaterial();
                        objects[index]->setMaterial(newMaterial);
                        break;
                    }
                    std::cout << "This index is invalid!" << std::endl << std::endl;
                }
            }
            else
                commandWasInvalid = true;
            break;
        }
        case 'n': {
            std::string newName = getStringFromUser("What is the new name?");
            name = newName;
            break;
        }
        default: commandWasInvalid = true;
        }
    }
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
        stream << "Center = " << group.getCenter() << " / " << numberObjects << " objects";

    return stream;
}


// Other function
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


// json
void to_json(json& j, const Object3DGroup& group) {
    std::vector<Object3D*> objects = group.getObjects();
    json objectsJson;
    for (Object3D* object : objects)
        objectsJson.push_back(*object);

    j = { { "Name", group.getName() }, {"Objects", objectsJson} };
}


void from_json(const json& j, Object3DGroup& group) {
    std::vector<Object3D*> objects;
    for (json jObject : j["Objects"]) {
        objects.push_back(importObject3DFromJson(jObject));
    }
    group.addObjects(objects);
    
    std::string name = j["Name"].get<std::string>();
    group.setName(name);
}
