#ifndef DEF_KDTREENODE
#define DEF_KDTREENODE

#include "Object3D.h"

class KDTreeNode {
private:
    unsigned int depth;
    DoubleVec3D minCoord;
    DoubleVec3D maxCoord;
    std::vector<Object3D*> objects;

    KDTreeNode* parent = nullptr;
    KDTreeNode* childSmaller = nullptr;
    KDTreeNode* childGreater = nullptr;

public:
    KDTreeNode();
    KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0);
    KDTreeNode(std::vector<Object3D*> objects, DoubleVec3D minCoord, DoubleVec3D maxCoord, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0);
    ~KDTreeNode();

    bool intersects(Ray ray);
    Object3D* getIntersection(Ray ray, KDTreeNode* ignore = nullptr);
};

DoubleVec3D getMinCoord(std::vector<Object3D*> objects);
DoubleVec3D getMaxCoord(std::vector<Object3D*> objects);

#endif
