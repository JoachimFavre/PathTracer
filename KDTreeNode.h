#ifndef DEF_KDTREENODE
#define DEF_KDTREENODE

#include "Object3D.h"
#include "InterfaceCreation.h"

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
    struct Intersection {
        Object3D* object;
        double distance;
        const KDTreeNode* kdTreeNode;

        Intersection(Object3D* object = nullptr, double distance = INFINITY, const KDTreeNode* kdTreeNode = nullptr);
    };

    KDTreeNode();
    KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0);
    KDTreeNode(std::vector<Object3D*> objects, DoubleVec3D minCoord, DoubleVec3D maxCoord, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0);
    ~KDTreeNode();

    unsigned int getDepth() const;
    DoubleVec3D getMinCoord() const;
    DoubleVec3D getMaxCoord() const;
    std::vector<Object3D*> getObjects() const;
    KDTreeNode* getParent() const;
    KDTreeNode* getChildSmaller() const;
    KDTreeNode* getChildGreater() const;

    double intersectionDistance(const Ray& ray) const;
    Intersection getIntersectionForward(const Ray& ray) const;
    Intersection getIntersectionBackward(const Ray& ray, const KDTreeNode* ignore = nullptr) const;
};

DoubleVec3D getMinPoint(std::vector<Object3D*> objects);
DoubleVec3D getMaxPoint(std::vector<Object3D*> objects);

void to_json(json& j, const KDTreeNode& vec);

#endif
