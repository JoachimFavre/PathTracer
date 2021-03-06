#ifndef DEF_OBJECT3DGROUP
#define DEF_OBJECT3DGROUP

#include <vector>

#include "InterfaceCreation.h"

/*!
    \file Object3DGroup.h
    \brief Defines the Object3DGroup class and some functions around it.

    \class Object3DGroup
    \brief Group of objects.
    \details It is used to make the interface clearer. Instead of having all the objects at the same place, they are grouped and have a common name.

    \fn Object3DGroup::Object3DGroup()
    \brief Default constructor.
    \details The name is "none" by default.

    \fn Object3DGroup::Object3DGroup(const std::string& name, std::vector<Object3D*> objects = {})
    \brief Main constructor.
    \param name The name of this object group.
    \param objects The std::vector of Object3D pointers that are in this group.

    \fn Object3DGroup::Object3DGroup(const Object3DGroup& group)
    \brief Copy constructor.
    \param group The group that will be copied.
    \warning The pointers are not deeply copied.

    \fn Object3DGroup::~Object3DGroup()
    \brief Destructor
    \details Calls Object3DGroup::resetObjects(). 
    \warning The pointers are not deleted.
    \sa Object3DGroup::resetObjects()

    \fn std::string Object3DGroup::getName()
    \brief Getter for the name.
    \return This object group's name.

    \fn std::vector<Object3D*> Object3DGroup::getObjects()
    \brief Getter for the objects.
    \return A std::vector of pointers to Object3D that are in this group. 
    \warning The pointers are not deeply copied.

    \fn DoubleVec3D Object3DGroup::getCenter()
    \brief Getter for the center
    \details The center is computed by taking the average of the center of each object.
    \return The center of this object group.

    \fn void Object3DGroup::setName(const std::string& name)
    \brief Setter for the name.
    \param name The new name of this object group.

    \fn void Object3DGroup::setObjects(const std::vector<Object3D*>& newObjects)
    \brief Setter for the objects.
    \param newObjects The new objects of this object group.
    \warning The pointers are not deeply copied.

    \fn void Object3DGroup::addObject(Object3D* object)
    \brief Adds an object to the current ones.
    \details The pointer is deeply copied.
    \param object The object that will be added.

    \fn void Object3DGroup::addObjects(const std::vector<Object3D*>& newObjects)
    \brief Add multiple objects to the current ones.
    \param newObjects The objects that will be added.
    \warning The pointers are not deeply copied.

    \fn void Object3DGroup::merge(const Object3DGroup& group)
    \brief Merge with an other object group.
    \details Keeps the current name, but adds the objects of the second one. 
    \param group The group from which the objects will be copied.
    \warning The pointers are not deeply copied.

    \fn void Object3DGroup::resetObjects()
    \brief Resets all objects of this object group.
    \sa Object3DGroup::resetAndDeleteObjects()
    \warning The pointers are not deleted.

    \fn void Object3DGroup::resetAndDeleteObjects()
    \brief Deletes all pointers to the objects of this object group, then reset its objects.
    \details Calls the function Object3DGroup::resetObjects().
    \sa Object3DGroup::resetObjects()

    \fn static Object3DGroup Object3DGroup::create()
    \brief Interactive creation of an object group.
    \return The interactively created object group.

    \fn void Object3DGroup::printAll()
    \brief Prints the whole page.
    \details Clears the page, prints the header, information and the available commands.
    \sa clearScreenPrintHeader()

    \fn void Object3DGroup::modify()
    \brief Interactive modification of this object group.
    \details This is a page on its own.

    \fn std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group)
    \brief Ostream operator.
    \param stream The ostream before.
    \param group The group that will be added to the stream.
    \return The stream with the group added.

    \fn std::vector<Object3D*> split(const std::vector<Object3DGroup>& groups)
    \brief Takes the std::vector of each object group and merge them.
    \param groups The object group that will be merges.
    \return All the objects of the object groups.
    \warning The pointers are not deeply copied.

    \fn void to_json(json& j, const Object3DGroup& group)
    \brief Conversion to json.
    \param j Json output.
    \param group The object group that will be converted.

    \fn void from_json(const json& j, Object3DGroup& group)
    \brief Conversion from json.
    \details Used for the .get<Object3DGroup>() function.
    \param j Json input.
    \param group The ouput object group.
*/

class Object3DGroup {
private:
    static const unsigned int MIN_OBJECTS_HIDE = 20;
    bool hide = false;

    std::string name;
    std::vector<Object3D*> objects;
    DoubleVec3D center;

public:
    Object3DGroup();
    Object3DGroup(const std::string& name, std::vector<Object3D*> objects = {});
    Object3DGroup(const Object3DGroup& group);
    ~Object3DGroup();

    std::string getName() const;
    std::vector<Object3D*> getObjects() const;
    DoubleVec3D getCenter() const;

    void setName(const std::string& name);
    void setObjects(const std::vector<Object3D*>& newObjects);

    void addObject(Object3D* object);
    void addObjects(const std::vector<Object3D*>& newObjects);
    void merge(const Object3DGroup& group);
    void resetObjects();
    void resetAndDeleteObjects();

    static Object3DGroup create();
    void printAll() const;
    void modify();
};

std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group);

std::vector<Object3D*> split(const std::vector<Object3DGroup>& groups);

void to_json(json& j, const Object3DGroup& group);
void from_json(const json& j, Object3DGroup& group);

#endif
