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
	Object3DGroup(const std::string& name, std::vector<Object3D*> objects);
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

	virtual Object3DGroup& operator=(const Object3DGroup& otherGroup);
};

std::ostream& operator<<(std::ostream& stream, const Object3DGroup& group);
std::vector<Object3D*> split(std::vector<Object3DGroup> groups);

#endif
