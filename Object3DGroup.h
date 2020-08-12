#ifndef DEF_OBJECT3DGROUP
#define DEF_OBJECT3DGROUP

#include <string>
#include <vector>

#include "DoubleVec3D.h"
#include "Object3D.h"

class Object3DGroup {
private:
	std::string name;
	std::vector<Object3D*> objects;
	DoubleVec3D center;

public:
	Object3DGroup();
	Object3DGroup(std::string name, std::initializer_list<Object3D*> objectsInitList);
	Object3DGroup(const Object3DGroup& group);

	std::string getName() const;
	std::vector<Object3D*> getObjects() const;
	DoubleVec3D getCenter() const;

	void setName(const std::string& name);
	void addObject(Object3D* object);
	void addObjects(const std::vector<Object3D*>& objects);
	void merge(const Object3DGroup& group);
	void resetObjects();
};

std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group);

#endif
