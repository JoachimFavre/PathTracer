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

void Object3DGroup::merge(const Object3DGroup& group) {    addObjects(group.getObjects()); }

void Object3DGroup::resetObjects() {
    objects.clear();
}

void Object3DGroup::resetAndDeleteObjects() {
    for (Object3D* object : objects)
        delete object;
    resetObjects();
}


// For the interface
Object3DGroup Object3DGroup::create() {
    std::string name = getStringFromUser("What is the name of this object group?");

    return Object3DGroup(name);
}

void Object3DGroup::printAll() const {
    clearScreenPrintHeader();

    std::cout << name << std::endl << DASH_SPLITTER << std::endl << std::endl;

    if (hide) {
        std::cout << objects.size() << " objects are hidden." << std::endl << "Press h to show them." << std::endl << std::endl;
    } else {
        for (int i = 0; i < objects.size(); i++) {
            std::cout << i << ") " << *(objects[i]) << std::endl << std::endl;
        }
    }

    availableCommandsHeader();
    std::cout << "- a: add an object" << std::endl;
    std::cout << "- b: go back to the objects page" << std::endl;
    std::cout << "- d: delete one or all objects" << std::endl;
    std::cout << "- h: " << (hide ? "show" : "hide") << " all objects" << std::endl;
    std::cout << "- m: modify one or all objects' material" << std::endl;
    std::cout << "- n: change the name of this object group" << std::endl;
}


void Object3DGroup::modify() {
    hide = objects.size() >= MIN_OBJECTS_HIDE;
    bool commandWasInvalid = false;
    while (true) {
        printAll();

        std::cout << std::endl;
        if (commandWasInvalid) {
            std::cout << INVALID_COMMAND << std::endl;
        }
        char command = getLowerCaseCharFromUser();

        if (commandWasInvalid) {
            // Reprint everything to remove the "invalid command"
            printAll();
            std::cout << std::endl << PROMPT << command << std::endl;
            commandWasInvalid = false;
        }
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
                    int index = getIntFromUser("What is the index of the object you want to delete? (-1 = cancel / -2 = delete all)");
                    if (index == -1)
                        break;
                    if (index == -2) {
                        std::cout << std::endl;
                        bool confirmation = getBoolFromUser("Do you confirm the deletion of all the objects? " + BOOL_INFO);
                        if (confirmation) {
                            for (Object3D* object : objects)
                                delete object;
                            objects.clear();
                        }
                        break;
                    }
                    if (index >= 0 && index < objects.size()) {
                        std::cout << std::endl;
                        bool confirmation = getBoolFromUser("Do you confirm the deletion of this object? " + BOOL_INFO);
                        if (confirmation) {
                            delete objects[index];
                            objects.erase(objects.begin() + index);
                        }
                        break;
                    }
                    std::cout << "This index is invalid!" << std::endl << std::endl;
                }
            }
            else
                commandWasInvalid = true;
            break;
        }
        case 'h': {
            if (hide && objects.size() >= MIN_OBJECTS_HIDE)
                if (!getBoolFromUser("There are more than " + std::to_string(MIN_OBJECTS_HIDE) + " hidden objects, are you sure you want to show them? " + BOOL_INFO))
                    break;
            hide = !hide;
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
std::vector<Object3D*> split(const std::vector<Object3DGroup>& groups) {
    std::vector<Object3D*> result;
    
    for (Object3DGroup group : groups) {
        std::vector<Object3D*> currentObjects = group.getObjects();
        result.insert(result.end(), currentObjects.begin(), currentObjects.end());
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
