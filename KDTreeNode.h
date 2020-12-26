#ifndef DEF_KDTREENODE
#define DEF_KDTREENODE

#include "Object3D.h"

class KDTreeNode {
private:
    unsigned int depth;
    DoubleVec3D minPoint;
    DoubleVec3D maxPoint;
    std::vector<Object3D*> objects;

    KDTreeNode* parent = nullptr;
    KDTreeNode* childSmaller = nullptr;
    KDTreeNode* childGreater = nullptr;

public:
    KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0);
    ~KDTreeNode();

    bool intersects(Ray ray);
    Object3D* getIntersection(Ray ray, KDTreeNode* ignore = nullptr);
};

#endif
