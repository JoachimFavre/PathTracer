#ifndef DEF_KDTREENODE
#define DEF_KDTREENODE

#include "InterfaceCreation.h"

/*!
    \file KDTreeNode.h
    \brief Defines the KDTreeNode class and the functions around it.

    \class KDTreeNode
    \brief A node of a k-d tree.
    \details See my TM's report for further information on this data structure. 

    \struct KDTreeNode::Intersection
    \brief A struct binding a pointer to an Object3D, a distance, and a pointer to a KDTreeNode.

    \var Object3D* KDTreeNode::Intersection::object
    \brief The Object3D with which the ray intersects.

    \var double KDTreeNode::Intersection::distance
    \brief The distance between the ray origin and the intersection point.

    \var const KDTreeNode* KDTreeNode::Intersection::kdTreeNode
    \brief The KDTreeNode in which the ray and the object intersect.

    \fn KDTreeNode::Intersection::Intersection(Object3D* object = nullptr, double distance = INFINITY, const KDTreeNode* kdTreeNode = nullptr)
    \brief Main constructor.
    \param object The Object3D with which the ray intersects.
    \param distance The distance between the ray origin and the intersection point.
    \param kdTreeNode The KDTreeNode in which the ray and the object intersect.

    \fn KDTreeNode::KDTreeNode()
    \brief Default constructor. Everything is set to 0 by default.

    \fn KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0)
    \brief One of the main constructors.
    \details Computes the minimum and maximum coordinates according to the objects in parameters using getMinPoint(std::vector<Object3D*> objects) and getMaxPoint(std::vector<Object3D*> objects).
    \param objects The objects that are in this node.
    \param maxObjectNumber Maximum number of objects in a k-d tree leaf. One of the two recursion stop conditions. If one of them is fulfilled, stops the recursion.
    \param maxDepth Maximum recursion depth. One of the two recursion stop conditions. If one of them is fulfilled, stops the recursion.
    \param parent A pointer to this node's parent.
    \param depth The current recursive depth.
    \sa getMinPoint(std::vector<Object3D*> objects), getMaxPoint(std::vector<Object3D*> objects)

    \fn KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, DoubleVec3D minCoord, DoubleVec3D maxCoord, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent = nullptr, unsigned int depth = 0)
    \brief One of the main constructors.
    \param objects The objects that are in this node.
    \param minCoord The minimum coordinate of this node.
    \param maxCoord The maximum coordinate of this node.
    \param maxObjectNumber Maximum number of objects in a k-d tree leaf. One of the two recursion stop conditions. If one of them is fulfilled, stops the recursion.
    \param maxDepth Maximum recursion depth. One of the two recursion stop conditions. If one of them is fulfilled, stops the recursion.
    \param parent A pointer to this node's parent.
    \param depth The current recursive depth.
    
    \fn KDTreeNode::~KDTreeNode()
    \brief Destructor.

    \fn unsigned int KDTreeNode::getDepth()
    \brief Getter for this node's depth.
    \return This recursive depth of this node.

    \fn DoubleVec3D KDTreeNode::getMinCoord()
    \brief Getter for this node's minimum coordinate.
    \return The minimum coordinate of this node.

    \fn DoubleVec3D KDTreeNode::getMaxCoord()
    \brief Getter for this node's maximum coordinate.
    \return The maximum coordinate of this node.

    \fn std::vector<Object3D*> KDTreeNode::getObjects()
    \brief Getter for this node's objects.
    \return The objects contained in this node.

    \fn KDTreeNode* KDTreeNode::getParent()
    \brief Getter for this node's parent.
    \return The parent of this node.

    \fn KDTreeNode* KDTreeNode::getChildSmaller()
    \brief Getter for this node's smaller child.
    \details The smaller child and the greater one are distinguished by their position to the cut.
    \return The smaller child of this node.

    \fn KDTreeNode* KDTreeNode::getChildGreater()
    \brief Getter for this node's greater child.
    \details The greater child and the smaller one are distinguished by their position to the cut.
    \return The greater child of this node.

    \fn double KDTreeNode::intersectionDistance(const Ray& ray)
    \brief Gives the distance to the closest intersection between this node's surface and a ray.
    \param ray The ray with which it computes the distance.
    \return The distance to the closest intersection between this node's surface and the ray.

    \fn bool KDTreeNode::isIn(DoubleVec3D point)
    \brief Returns whether a point is inside this node.
    \param point The point for which we want this information.
    \return Whether a point is inside this node.

    \fn KDTreeNode::Intersection KDTreeNode::getIntersectionForward(const Ray& ray)
    \brief Computes the intersection going from the top to the bottom of the tree.
    \param ray The ray with which the intersection is computed.
    \return The intersection.

    \fn KDTreeNode::Intersection KDTreeNode::getIntersectionBackward(const Ray& ray, const KDTreeNode* ignore = nullptr)
    \brief Computes the intersection going from the bottom to the top of the tree.
    \details Starts at a bottom node and alternates between backward and forward intersection.
    \param ray The ray with whcih the intersection is computed.
    \param ignore A KDTreeNode that will be ignored when computing a forward intersection.
    \return The intersection.

    \fn DoubleVec3D getMinPoint(std::vector<Object3D*> objects)
    \brief Computes the minimum point of a cuboid containing all the objects.
    \param objects The objects that will be used for the computation.
    \return The minimum point.
    
    \fn DoubleVec3D getMaxPoint(std::vector<Object3D*> objects)
    \brief Computes the maximum point of a cuboid containing all the objects.
    \param objects The objects that will be used for the computation.
    \return The maximum point.

    \fn void to_json(json& j, const KDTreeNode& node)
    \brief Conversion to json.
    \details Only used for debugging.
    \param j Json output.
    \param node The node that will be converted.
*/

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
    bool isIn(DoubleVec3D point) const;
    Intersection getIntersectionForward(const Ray& ray) const;
    Intersection getIntersectionBackward(const Ray& ray, const KDTreeNode* ignore = nullptr) const;
};

DoubleVec3D getMinPoint(std::vector<Object3D*> objects);
DoubleVec3D getMaxPoint(std::vector<Object3D*> objects);

void to_json(json& j, const KDTreeNode& node);

#endif
