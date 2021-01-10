#include "KDTreeNode.h"


// Intersection struct
KDTreeNode::Intersection::Intersection(Object3D* object /*= nullptr*/, double distance /*= INFINITY*/, const KDTreeNode* kdTreeNode /*= nullptr*/)
    : object(object), distance(distance), kdTreeNode(kdTreeNode) {}


// Constructors and destructors
KDTreeNode::KDTreeNode() 
    : depth(0), minCoord(0.0), maxCoord(0.0) {}

KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent /*= nullptr*/, unsigned int depth /*= 0*/) 
    : KDTreeNode(objects, getMinPoint(objects), getMaxPoint(objects), maxObjectNumber, maxDepth, parent, depth) {}

KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, DoubleVec3D minCoord, DoubleVec3D maxCoord, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent /*= nullptr*/, unsigned int depth /*= 0*/) 
    : objects(objects), minCoord(minCoord), maxCoord(maxCoord), parent(parent), depth(depth) {

    // Recursion
    if (objects.size() > maxObjectNumber && depth < maxDepth) {
        // Pick all centers, to know where to cut
        std::vector<double> centers;
        unsigned int currentBasis = depth % 3;  // we alternate basis. First x, then y, and finally z. Then loop again.

        for (Object3D* object : objects) {
            DoubleVec3D center = object->getCenter();

            if (currentBasis == 0)
                centers.push_back(center.getX());
            else if (currentBasis == 1)
                centers.push_back(center.getY());
            else // currentBasis == 2
                centers.push_back(center.getZ());
        }

        // We cut at the median of centers
        double cut = 0.0;
        std::sort(centers.begin(), centers.end());
        unsigned int centersSize = centers.size();
        
        if (centersSize % 2 == 0)
            cut = centers[centersSize / 2];
        else
            cut = (centers[(centersSize - 1) / 2] + centers[(centersSize + 1) / 2]) / 2;

        // Compute min/max coordinates for children
        DoubleVec3D maxCoordChildSmaller(maxCoord);
        DoubleVec3D minCoordChildGreater(minCoord);

        if (currentBasis == 0) {
            maxCoordChildSmaller.setVals(cut, maxCoordChildSmaller.getY(), maxCoordChildSmaller.getZ());
            minCoordChildGreater.setVals(cut, minCoordChildGreater.getY(), minCoordChildGreater.getZ());
        } else if (currentBasis == 1) {
            maxCoordChildSmaller.setVals(maxCoordChildSmaller.getX(), cut, maxCoordChildSmaller.getZ());
            minCoordChildGreater.setVals(minCoordChildGreater.getX(), cut, minCoordChildGreater.getZ());
        } else { // currentBasis == 2
            maxCoordChildSmaller.setVals(maxCoordChildSmaller.getX(), maxCoordChildSmaller.getY(), cut);
            minCoordChildGreater.setVals(minCoordChildGreater.getX(), minCoordChildGreater.getY(), cut);
        }

        // We split the objects according to their position to the cut
        std::vector<Object3D*> objectsChildSmaller;
        std::vector<Object3D*> objectsChildGreater;

        for (Object3D* object : objects) {
            double minCoord;
            double maxCoord;
            if (currentBasis == 0) {
                minCoord = object->getMinCoord().getX();
                maxCoord = object->getMaxCoord().getX();
            }
            else if (currentBasis == 1) {
                minCoord = object->getMinCoord().getY();
                maxCoord = object->getMaxCoord().getY();
            }
            else { // currentBasis == 2
                minCoord = object->getMinCoord().getZ();
                maxCoord = object->getMaxCoord().getZ();
            }

            if (maxCoord < cut)
                objectsChildSmaller.push_back(object);
            else if (minCoord > cut)
                objectsChildGreater.push_back(object);
            else {
                objectsChildSmaller.push_back(object);
                objectsChildGreater.push_back(object);
            }
        }

        // Create the children
        childSmaller = new KDTreeNode(objectsChildSmaller, minCoord, maxCoordChildSmaller, maxObjectNumber, maxDepth, this, depth + 1);
        childGreater = new KDTreeNode(objectsChildGreater, minCoordChildGreater, maxCoord, maxObjectNumber, maxDepth, this, depth + 1);

        // Remove useless children. This should not be useful if the k-d tree has good recursion parameters.
        if (childSmaller->getChildSmaller() == nullptr && childGreater->getChildSmaller() == nullptr) {
            if (objectsChildSmaller.size() == objects.size() && objectsChildGreater.size() == objects.size()) {
                delete childSmaller;
                childSmaller = nullptr;
                delete childGreater;
                childGreater = nullptr;
            }
        }
    }
}

KDTreeNode::~KDTreeNode() {
    delete childSmaller;
    delete childGreater;
}


// Getters
unsigned int KDTreeNode::getDepth() const { return depth; }
DoubleVec3D KDTreeNode::getMinCoord() const { return minCoord; }
DoubleVec3D KDTreeNode::getMaxCoord() const { return maxCoord; }
std::vector<Object3D*> KDTreeNode::getObjects() const { return objects; }
KDTreeNode* KDTreeNode::getParent() const { return parent; }
KDTreeNode* KDTreeNode::getChildSmaller() const { return childSmaller; }
KDTreeNode* KDTreeNode::getChildGreater() const { return childGreater; }

// Methods
unsigned int KDTreeNode::getMaxDepth() const {
    if (childSmaller == nullptr)
        return depth;
    return std::max(childSmaller->getMaxDepth(), childGreater->getMaxDepth());
}

unsigned int KDTreeNode::getMaxObjectNumberLeaf() const {
    if (childSmaller == nullptr)
        return objects.size();
    return std::max(childSmaller->getMaxObjectNumberLeaf(), childGreater->getMaxObjectNumberLeaf());
}

double KDTreeNode::intersectionDistance(const Ray& ray) const {
    DoubleVec3D rayOrigin = ray.getOrigin();
    DoubleVec3D rayDirection = ray.getDirection();
    double smallestPositiveDistance = INFINITY;

    double distance;
    DoubleVec3D intersectionPoint;

    if (rayDirection.getX() > DBL_EPSILON || rayDirection.getX() < -DBL_EPSILON) {  // not parallel with x-planes
        // Min plane
        distance = (minCoord.getX() - rayOrigin.getX()) / rayDirection.getX();  // x0 + d*a = k <=> d = (k - x0)/a
        intersectionPoint = rayOrigin + rayDirection*distance;
        if (minCoord.getY() <= intersectionPoint.getY() && intersectionPoint.getY() <= maxCoord.getY())
            if (minCoord.getZ() <= intersectionPoint.getZ() && intersectionPoint.getZ() <= maxCoord.getZ())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;

        // Max plane
        distance = (maxCoord.getX() - rayOrigin.getX()) / rayDirection.getX();
        intersectionPoint = rayOrigin + rayDirection * distance;
        if (minCoord.getY() <= intersectionPoint.getY() && intersectionPoint.getY() <= maxCoord.getY())
            if (minCoord.getZ() <= intersectionPoint.getZ() && intersectionPoint.getZ() <= maxCoord.getZ())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;
    }
    if (rayDirection.getY() > DBL_EPSILON || rayDirection.getY() < -DBL_EPSILON) {  // not parallel with y-planes
        // Min plane
        distance = (minCoord.getY() - rayOrigin.getY()) / rayDirection.getY();
        intersectionPoint = rayOrigin + rayDirection * distance;
        if (minCoord.getX() <= intersectionPoint.getX() && intersectionPoint.getX() <= maxCoord.getX())
            if (minCoord.getZ() <= intersectionPoint.getZ() && intersectionPoint.getZ() <= maxCoord.getZ())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;

        // Max plane
        distance = (maxCoord.getY() - rayOrigin.getY()) / rayDirection.getY();
        intersectionPoint = rayOrigin + rayDirection * distance;
        if (minCoord.getX() <= intersectionPoint.getX() && intersectionPoint.getX() <= maxCoord.getX())
            if (minCoord.getZ() <= intersectionPoint.getZ() && intersectionPoint.getZ() <= maxCoord.getZ())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;
    }
    if (rayDirection.getZ() > DBL_EPSILON || rayDirection.getZ() < -DBL_EPSILON) {  // not parallel with z-planes
        // Min plane
        distance = (minCoord.getZ() - rayOrigin.getZ()) / rayDirection.getZ();
        intersectionPoint = rayOrigin + rayDirection * distance;
        if (minCoord.getX() <= intersectionPoint.getX() && intersectionPoint.getX() <= maxCoord.getX())
            if (minCoord.getY() <= intersectionPoint.getY() && intersectionPoint.getY() <= maxCoord.getY())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;

        distance = (maxCoord.getZ() - rayOrigin.getZ()) / rayDirection.getZ();
        intersectionPoint = rayOrigin + rayDirection * distance;
        if (minCoord.getX() <= intersectionPoint.getX() && intersectionPoint.getX() <= maxCoord.getX())
            if (minCoord.getY() <= intersectionPoint.getY() && intersectionPoint.getY() <= maxCoord.getY())
                if (distance < smallestPositiveDistance && distance > 0.00001)
                    smallestPositiveDistance = distance;
    }
    return smallestPositiveDistance;
}

bool KDTreeNode::isIn(DoubleVec3D point) const {
    // I do not know not writing it in one line optimises the code (I guess it depends on the compiler), but it does not cost me anything
    if (minCoord.getX() - 0.00001 <= point.getX() && point.getX() <= maxCoord.getX() + 0.00001)
        if (minCoord.getY() - 0.00001 <= point.getY() && point.getY() <= maxCoord.getY() + 0.00001)
            if (minCoord.getZ() - 0.00001 <= point.getZ() && point.getZ() <= maxCoord.getZ() + 0.00001)
                return true;
    return false;
}

KDTreeNode::Intersection KDTreeNode::getIntersectionForward(const Ray& ray) const {
    if (childSmaller != nullptr) {  // both children are nullptr at the same time
        double distanceChildSmaller = childSmaller->intersectionDistance(ray);
        double distanceChildGreater = childGreater->intersectionDistance(ray);
        
        if (distanceChildSmaller == INFINITY && distanceChildGreater == INFINITY)
            return Intersection(nullptr, INFINITY, this);

        if (distanceChildSmaller == INFINITY)
            return childGreater->getIntersectionForward(ray);
        if (distanceChildGreater == INFINITY)
            return childSmaller->getIntersectionForward(ray);

        // equidistant
        if (distanceChildGreater >= distanceChildSmaller - 0.00001 && distanceChildGreater <= distanceChildSmaller + 0.00001) {  // in almost 100% of cases, the ray origin is in one of the children
            if (childSmaller->isIn(ray.getOrigin())) {
                Intersection intersection = childSmaller->getIntersectionForward(ray);
                if (intersection.object != nullptr && childSmaller->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
                    return intersection;
                else
                    return childGreater->getIntersectionForward(ray);
            }
            else {
                Intersection intersection = childGreater->getIntersectionForward(ray);
                if (intersection.object != nullptr && childGreater->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
                    return intersection;
                else
                    return childSmaller->getIntersectionForward(ray);
            }
        }

        if (distanceChildGreater < distanceChildSmaller) {
            Intersection intersection = childGreater->getIntersectionForward(ray);
            if (intersection.object != nullptr && childGreater->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
                return intersection;
            else
                return childSmaller->getIntersectionForward(ray);
        }

        // distanceChildSmaller < distanceChildGreater  
        Intersection intersection = childSmaller->getIntersectionForward(ray);
        if (intersection.object != nullptr && childSmaller->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
            return intersection;
        else
            return childGreater->getIntersectionForward(ray);
    }
    else {
        double smallestPositiveDistance = INFINITY;  // Has to be strictly positive -> we don't want it to intersect with same object
        Object3D* closestObject = nullptr;
        for (Object3D* object : objects) {
            double distance = object->smallestPositiveIntersection(ray);
            if (distance > 0.00001 && distance < smallestPositiveDistance) {
                smallestPositiveDistance = distance;
                closestObject = object;
            }
        }
        return Intersection(closestObject, smallestPositiveDistance, this);
    }
}

KDTreeNode::Intersection KDTreeNode::getIntersectionBackwards(const Ray& ray, const KDTreeNode* ignore /*= nullptr*/) const {
    if (childSmaller == nullptr) {
        Intersection intersection = getIntersectionForward(ray);
        if (intersection.object != nullptr && isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
            return intersection;

        if (parent == nullptr)
            return Intersection(nullptr, INFINITY, this);
        else
            return parent->getIntersectionBackwards(ray, this);
    }
    // One of the children must be ignored
    if (childSmaller == ignore) {
        Intersection intersection = childGreater->getIntersectionForward(ray);
        if((intersection.object == nullptr || !childGreater->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance)) && parent != nullptr)
            return parent->getIntersectionBackwards(ray, this);
        return intersection;
    }
    if (childGreater == ignore) {
        Intersection intersection = childSmaller->getIntersectionForward(ray);
        if ((intersection.object == nullptr || !childSmaller->isIn(ray.getOrigin() + ray.getDirection()*intersection.distance)) && parent != nullptr)
            return parent->getIntersectionBackwards(ray, this);
        return intersection;
    }

    // No child must be ignored
    Intersection intersection = getIntersectionForward(ray);
    if (intersection.object != nullptr && isIn(ray.getOrigin() + ray.getDirection()*intersection.distance))
        return intersection;
    if (parent != nullptr)
        return parent->getIntersectionBackwards(ray, this);
    return intersection;
}

// Functions
DoubleVec3D getMinPoint(std::vector<Object3D*> objects) {
    double minX = INFINITY;
    double minY = INFINITY;
    double minZ = INFINITY;

    for (Object3D* object : objects) {
        DoubleVec3D minCoord = object->getMinCoord();

        if (minCoord.getX() < minX)
            minX = minCoord.getX();
        if (minCoord.getY() < minY)
            minY = minCoord.getY();
        if (minCoord.getZ() < minZ)
            minZ = minCoord.getZ();
    }
    return DoubleVec3D(minX, minY, minZ);
}

DoubleVec3D getMaxPoint(std::vector<Object3D*> objects) {
    double maxX = -INFINITY;
    double maxY = -INFINITY;
    double maxZ = -INFINITY;

    for (Object3D* object : objects) {
        DoubleVec3D maxCoord = object->getMaxCoord();

        if (maxCoord.getX() > maxX)
            maxX = maxCoord.getX();
        if (maxCoord.getY() > maxY)
            maxY = maxCoord.getY();
        if (maxCoord.getZ() > maxZ)
            maxZ = maxCoord.getZ();
    }
    return DoubleVec3D(maxX, maxY, maxZ);
}


// Json
void to_json(json& j, const KDTreeNode& node) {
    DoubleVec3D center;
    for (Object3D* object : node.getObjects())
        center += object->getCenter();
    center /= node.getObjects().size();

    json childrenJson;
    if (node.getChildSmaller() == nullptr) {
        std::vector<Object3D*> objects = node.getObjects();
        json objectsJson;
        for (Object3D* object : objects)
            objectsJson.push_back(*object);
        childrenJson = {"6) Objects", objectsJson};
    }
    else
        childrenJson = { { "6) ChildSmaller", *(node.getChildSmaller()) },
                         { "7) ChildGreater", *(node.getChildGreater()) } };
    
    j = json{ {"1) MinCoord", node.getMinCoord()},
              {"2) MaxCoord", node.getMaxCoord()},
              {"3) Depth", node.getDepth()},
              {"4) ObjectsNumber", node.getObjects().size()},
              {"5) Center", center},
              childrenJson};
}