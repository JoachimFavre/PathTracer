#ifndef DEF_OBJECT3DGROUP
#define DEF_OBJECT3DGROUP

#include <string>
#include <vector>

#include "DoubleVec3D.h"
#include "Object3D.h"
#include "InterfaceGestion.h"

//! Group of objects.
/*!
	It is used to make the interface clearer. Instead of having all the objects at the same place, they are grouped and have a common name.
*/
class Object3DGroup {
private:
	std::string name;
	std::vector<Object3D*> objects;
	DoubleVec3D center;

public:
	//! Default constructor.
	/*!
		The name is "none" by default.
	*/
	Object3DGroup();

	//! Main constructor.
	/*!
		\param name The name of this Objects Group.
		\param objects The std::vector of Object3D pointers that are in this group.
	*/
	Object3DGroup(const std::string& name, std::vector<Object3D*> objects = {});

	//! Copy constructor.
	/*!
		\param group The group that will be copied.
	*/
	Object3DGroup(const Object3DGroup& group);

	//! Destructor
	/*!
		Deletes all Object3D pointers.
		\sa resetObjects()
	*/
	~Object3DGroup();


	//! Getter for the name.
	/*!
		\return This objects group's name.
	*/
	std::string getName() const;

	//! Getter for the objects.
	/*!
		\return A std::vector of pointers to Object3D that are in this group. The pointers are not deeply copied.
	*/
	std::vector<Object3D*> getObjects() const;

	//! Getter for the center
	/*!
		The center is computed by taking the average of the center of each object.
		\return The center of this objects group.
	*/
	DoubleVec3D getCenter() const;


	//! Setter for the name.
	/*!
		\param name The new name of this objects group.
	*/
	void setName(const std::string& name);

	//! Setter for the objects.
	/*!
		The pointers are deeply copied.
		\param newObjects The new objects of this objects group. 
	*/
	void setObjects(const std::vector<Object3D*>& newObjects);


	//! Adds an object to the current ones.
	/*!
		The pointer is deeply copied.
		\param object The object that will be added.
	*/
	void addObject(Object3D* object);

	//! Add multiple objects to the current ones.
	/*!
		The pointers are deeply copied.
		\param newObjects The objects that will be added.
	*/
	void addObjects(const std::vector<Object3D*>& newObjects);

	//! Merge with an other objects group.
	/*!
		Keeps the current name, but adds the objects of the second one. The pointers are deeply copied.
		\param group The group from which the objects will be copied.
	*/
	void merge(const Object3DGroup& group);

	//! Resets all objects of this objects group.
	/*!
		Deletes all objects.
	*/
	void resetObjects();


	//! Assignment operator.
	/*!
		The objects of the other group are deeply copied.
		\param otherGroup The group to which this group will be equal.
		\return The copy of otherGroup.
	*/
	Object3DGroup& operator=(const Object3DGroup& otherGroup);

	//! Interactive creation of an objects group.
	/*!
		\return The interactively created objects group.
	*/
	static Object3DGroup create();

	//! Interactive modification of this objects group.
	/*!
		This is a page on its own.
	*/
	void modify();
};

//! Ostream operator.
/*!
	\param stream The ostream before.
	\param group The group that will be added to the stream.
	\return The stream with the group added.
*/
std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group);

//! Takes the std::vector of each objects group and merge them.
/*!
	Makes a deep copy of all Object3D pointers.
	\param groups The objects group that will be merges.
	\return All the objects of the objects groups.
*/
std::vector<Object3D*> split(std::vector<Object3DGroup> groups);


//! Conversion to json.
/*!
	\param j Json output.
	\param group The objects group that will be converted.
*/
void to_json(json& j, const Object3DGroup& group);

//! Conversion from json.
/*!
	Used for the .get<Object3DGroup>() function.
	\param j Json input.
	\param group The ouput objects group.
*/
void from_json(const json& j, Object3DGroup& group);

#endif
