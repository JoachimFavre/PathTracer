#include "KDTreeNode.h"

// Constructors and destructors
KDTreeNode::KDTreeNode() 
    : depth(0), minCoord(0.0), maxCoord(0.0) {}

KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent /*= nullptr*/, unsigned int depth /*= 0*/) 
    : KDTreeNode(objects, getMinCoord(objects), getMaxCoord(objects), maxObjectNumber, maxDepth, parent, depth) {}

KDTreeNode::KDTreeNode(std::vector<Object3D*> objects, DoubleVec3D minCoord, DoubleVec3D maxCoord, unsigned int maxObjectNumber, unsigned int maxDepth, KDTreeNode* parent /*= nullptr*/, unsigned int depth /*= 0*/) 
    : objects(objects), minCoord(minCoord), maxCoord(maxCoord), depth(depth) {

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
    }

}

KDTreeNode::~KDTreeNode() {
    delete childSmaller;
    delete childGreater;
}


// Functions
DoubleVec3D getMinCoord(std::vector<Object3D*> objects) {
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

DoubleVec3D getMaxCoord(std::vector<Object3D*> objects) {
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


// Intersection struct
Intersection::Intersection(Object3D* object /*= nullptr*/, double distance /*= 0*/) 
    : object(object), distance(distance) {}
