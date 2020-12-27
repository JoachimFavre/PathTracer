#include "Scene.h"

// Constructors & Destructors
Scene::Scene() : Scene(PerspectiveCamera(), 8, 5, 10, 0.1) {}

Scene::Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth, double rrStopProbability)
    : camera(camera), samplePerPixel(samplePerPixel), minBounces(minBounces), maxDepth(maxDepth), rrStopProbability(rrStopProbability) {}

Scene::Scene(const Scene& scene)
    : Scene(scene.camera, scene.samplePerPixel, scene.minBounces, scene.maxDepth, scene.rrStopProbability) {}


// Getters
std::vector<Object3DGroup> Scene::getObjectsGroups() const { return objectsGroups; }
std::vector<Object3DGroup>& Scene::getObjectsGroupsReference() { return objectsGroups; }


std::vector<Object3D*> Scene::getObjects() {
    // May take a long time to compute -> must be absolutely necessary
    computeObjectsAndLamps();
    return objects;
}

std::vector<Object3D*> Scene::getLamps() {
    // May take a long time to compute -> must be absolutely necessary
    computeObjectsAndLamps();
    return lamps;
}

PerspectiveCamera Scene::getCamera() const { return camera; }
PerspectiveCamera& Scene::getCameraReference() { return camera; }
unsigned int Scene::getSamplePerPixel() const { return samplePerPixel; }
unsigned int Scene::getMinBounces() const { return minBounces; }
double Scene::getMaxDepth() const { return maxDepth; }
bool Scene::getRussianRoulette() const { return russianRoulette; }
double Scene::getRrStopProbability() const { return rrStopProbability; }
bool Scene::getNextEventEstimation() const { return nextEventEstimation; }
unsigned int Scene::getNumberThreads() const { return numberThreads; }


// Setters
void Scene::setObjectsGroups(std::vector<Object3DGroup> groups) { objectsGroups = groups; }
void Scene::setCamera(PerspectiveCamera camera) { this->camera = camera; }
void Scene::setSamplePerPixel(unsigned int samplePerPixel) { this->samplePerPixel = samplePerPixel; }
void Scene::setMinBounces(unsigned int minBounces) { this->minBounces = minBounces; }
void Scene::setMaxDepth(double maxDepth) { this->maxDepth = maxDepth; }
void Scene::setRussianRoulette(bool russianRoulette) { this->russianRoulette = russianRoulette; }
void Scene::setRussianRoulette(bool russianRoulette, double rrStopProbability) {
    this->russianRoulette = russianRoulette;
    this->rrStopProbability = rrStopProbability;
}
void Scene::setRrStopProbability(double rrStopProbability) { this->rrStopProbability = rrStopProbability; }
void Scene::setNextEventEstimation(bool nextEventEstimation) { this->nextEventEstimation = nextEventEstimation; }
void Scene::setNumberThreads(unsigned int numberThreads) { this->numberThreads = numberThreads; }


// Objects groups management
void Scene::addObjectGroup(const Object3DGroup& group) {
    objectsGroups.push_back(group);
}

void Scene::resetObjectGroups() {
    objectsGroups.clear();  // Calls their destructor -> no memory leak
}

void Scene::computeObjectsAndLamps() {
    for (Object3D* object : objects)
        delete object;

    objects = split(objectsGroups);
    lamps.clear();

    for (Object3D* object : objects)
        if (!object->getMaterial()->getEmittance().isZero())
            lamps.push_back(object);
}

void Scene::defaultScene() {
    // Spheres
    addObjectGroup(Object3DGroup("Light", {
        new Sphere(DoubleVec3D(0, 1.5, -3.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), DoubleVec3D(4000)))
        }));
    addObjectGroup(Object3DGroup("Testing spheres", {
        new Sphere(DoubleVec3D(0.2, -1.5, -4), 0.5, new RefractiveMaterial(1.5)),
        new Sphere(DoubleVec3D(1.2, -1.5, -3.4), 0.5, new SpecularMaterial),
        new Sphere(DoubleVec3D(-1, -1.5, -3.3), 0.5, new DiffuseMaterial(DoubleVec3D(0.5)))
        }));

    // Walls
    addObjectGroup(Object3DGroup("Left wall", {
        new Triangle(DoubleVec3D(-2, 2, 0), DoubleVec3D(-2, -2, 0), DoubleVec3D(-2, -2, -5), new DiffuseMaterial(DoubleVec3D(0.2, 0.2, 1))),
        new Triangle(DoubleVec3D(-2, 2, 0), DoubleVec3D(-2, -2, -5), DoubleVec3D(-2, 2, -5), new DiffuseMaterial(DoubleVec3D(0.2, 0.2, 1)))
        }));
    addObjectGroup(Object3DGroup("Right wall", {
        new Triangle(DoubleVec3D(2, -2, -5), DoubleVec3D(2, -2, 0), DoubleVec3D(2, 2, 0), new DiffuseMaterial(DoubleVec3D(1, 0.2, 0.2))),
        new Triangle(DoubleVec3D(2, 2, -5), DoubleVec3D(2, -2, -5), DoubleVec3D(2, 2, 0), new DiffuseMaterial(DoubleVec3D(1, 0.2, 0.2)))
        }));
    addObjectGroup(Object3DGroup("Ceiling", {
        new Triangle(DoubleVec3D(2, 2, -5), DoubleVec3D(-2, 2, 0), DoubleVec3D(-2, 2, -5), new DiffuseMaterial(DoubleVec3D(0.3))),
        new Triangle(DoubleVec3D(-2, 2, 0), DoubleVec3D(2, 2, -5), DoubleVec3D(2, 2, 0), new DiffuseMaterial(DoubleVec3D(0.3)))
        }));
    addObjectGroup(Object3DGroup("Floor", {
        new Triangle(DoubleVec3D(-2, -2, 0), DoubleVec3D(2, -2, -5), DoubleVec3D(-2, -2, -5), new DiffuseMaterial(DoubleVec3D(0.3))),
        new Triangle(DoubleVec3D(2, -2, -5), DoubleVec3D(-2, -2, 0), DoubleVec3D(2, -2, 0), new DiffuseMaterial(DoubleVec3D(0.3)))
        }));
    addObjectGroup(Object3DGroup("Background wall", {
        new Triangle(DoubleVec3D(-2, 2, -5), DoubleVec3D(-2, -2, -5), DoubleVec3D(2, 2, -5), new DiffuseMaterial(DoubleVec3D(0.2, 1, 0.2))),
        new Triangle(DoubleVec3D(2, 2, -5), DoubleVec3D(-2, -2, -5), DoubleVec3D(2, -2, -5), new DiffuseMaterial(DoubleVec3D(0.2, 1, 0.2)))
        }));
    addObjectGroup(Object3DGroup("Wall behind camera", {
        new Triangle(DoubleVec3D(2, 2, 0), DoubleVec3D(2, -2, 0), DoubleVec3D(-2, -2, 0), new DiffuseMaterial(DoubleVec3D(0.3))),
        new Triangle(DoubleVec3D(-2, 2, 0), DoubleVec3D(2, 2, 0), DoubleVec3D(-2, -2, 0), new DiffuseMaterial(DoubleVec3D(0.3)))
        }));
}

bool Scene::importFBX(const char* filePath, Material* material, std::string name) {
    double importationBeginningTime = getCurrentTimeSeconds();

    FbxManager* sdkManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
    sdkManager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(sdkManager, "");

    bool importStatus = importer->Initialize(filePath, -1, sdkManager->GetIOSettings());

    if (!importStatus) {
        std::cout << "Error in the importation: " << importer->GetStatus().GetErrorString() << std::endl;
        return false;
    }

    FbxScene* fbxScene = FbxScene::Create(sdkManager, "myScene");
    importer->Import(fbxScene);
    importer->Destroy();

    FbxGeometryConverter clsConverter(sdkManager);
    bool triangulisationStatus = clsConverter.Triangulate(fbxScene, true);
    if (!triangulisationStatus) {
        std::cout << "Error in the importation: triangulisation could not be fully done" << std::endl;
        return false;
    }

    FbxNode* rootNode = fbxScene->GetRootNode();

    for (int childNumber = 0; childNumber < rootNode->GetChildCount(); childNumber++) {
        FbxNode* child = rootNode->GetChild(childNumber);

        FbxAMatrix& childGlobalTransform = child->EvaluateGlobalTransform();
        DoubleVec3D translation = childGlobalTransform.GetT();
        DoubleVec3D rotation = childGlobalTransform.GetR() * M_PI/180; // Gets converted in radians
        DoubleVec3D scaling = childGlobalTransform.GetS();

        DoubleMatrix33 rotationAndScalingMatrix = getRotationMatrixXYZ(rotation)*getScalingMatrixXYZ(scaling);  // order is important

        FbxMesh* mesh = child->GetMesh();

        if (mesh != nullptr) {
            FbxVector4* controlPoints = mesh->GetControlPoints();
            std::vector<Object3D*> objects;

            // Add each triangle to the scene
            for (int polygonIx = 0; polygonIx < mesh->GetPolygonCount(); polygonIx++) {
                if (mesh->GetPolygonSize(polygonIx) != 3) {
                    std::cout << "Error in the importation: a polygon is not a triangle" << std::endl;
                    return false;
                }

                // FbxSurfaceMaterial* material = child->GetMaterial(0);  // assumes one material for each face
                // std::cout << material->GetName() << std::endl;
                FbxLayer* layer = mesh->GetLayer(0);

                DoubleVec3D vertex0 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 0)] + translation;
                DoubleVec3D vertex1 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 1)] + translation;
                DoubleVec3D vertex2 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 2)] + translation;

                Triangle* triangle = new Triangle(vertex0, vertex1, vertex2, material);
                // Emittance is always equal to the diffuse colour -> bug from the library

                // Verify normals?

                objects.push_back(triangle);
            }

            addObjectGroup(Object3DGroup(name, objects));
        }
    }

    std::cout << filePath << " was successfully imported in " << getCurrentTimeSeconds() - importationBeginningTime << " seconds!" << std::endl;
    return true;
}


// Private method
KDTreeNode::Intersection Scene::bruteForceIntersection(const Ray& ray) const {
    double smallestPositiveDistance = INFINITY;  // Has to be strictly positive -> we don't want it to intersect with same object
    Object3D* closestObject = nullptr;
    for (Object3D* object : objects) {
        double distance = object->closestIntersection(ray);
        if (distance > 0.00001 && distance < smallestPositiveDistance) {
            smallestPositiveDistance = distance;
            closestObject = object;
        }
    }
    return KDTreeNode::Intersection(closestObject, smallestPositiveDistance);
}

DoubleVec3D Scene::traceRay(const Ray& ray, double usedNextEventEstimation /*= false*/, const KDTreeNode* lastNode /*= nullptr*/, unsigned int bounces /*= 0*/) const {

    DoubleVec3D result(0.0);

    // Russian roulette
    double rrFactor = 1.0;
    if (bounces >= minBounces) {
        if (!russianRoulette || randomDouble() < rrStopProbability)
            return result;
        rrFactor = 1.0 / (1.0 - rrStopProbability);
    }

    // Search for ray intersection
    KDTreeNode::Intersection intersection;
    if (!kdTree)
        intersection = bruteForceIntersection(ray);
    else if (lastNode == nullptr)
        intersection = KDTreeRoot->getIntersectionForward(ray);
    else
        intersection = lastNode->getIntersectionBackward(ray);

    if (intersection.object == nullptr)  // Something must be hit
        return result;

    // Rendering equation
    Material* objectMaterial = intersection.object->getMaterial();
    DoubleVec3D intersectionPoint = ray.getOrigin() + intersection.distance * ray.getDirection();
    DoubleUnitVec3D normal = intersection.object->getNormal(intersectionPoint);

    double neeFactor = 1.0;
    if (nextEventEstimation && objectMaterial->worksWithNextEventEstimation()) {
        neeFactor = 1.0/(1.0 + lamps.size());
        for (Object3D* lamp : lamps) {
            DoubleVec3D intersectionToLamp = lamp->getRandomPoint() - intersectionPoint;
            if (dotProd(normal, intersectionToLamp) > -0.0001) {
                double distanceLamp = length(intersectionToLamp);
                Ray shadowRay(intersectionPoint, intersectionToLamp);  // intersectionToLamp goes in DoubleUnitVec3D constructor => normalised

                KDTreeNode::Intersection shadowRayIntersection;
                if (!kdTree)
                    shadowRayIntersection = bruteForceIntersection(shadowRay);
                else if (intersection.kdTreeNode == nullptr)
                    shadowRayIntersection = KDTreeRoot->getIntersectionForward(shadowRay);
                else
                    shadowRayIntersection = intersection.kdTreeNode->getIntersectionBackward(shadowRay);

                if (shadowRayIntersection.object == lamp) {
                    intersectionToLamp /= distanceLamp;  // Normalised
                    result += rrFactor * neeFactor * objectMaterial->computeCurrentRadiance(lamp->getMaterial()->getEmittance(), dotProd(intersectionToLamp, normal), true)
                              / distanceLamp / distanceLamp / lamp->getArea();
                    // result += rrFactor * lamp->getMaterial()->getEmittance() / distanceLamp / distanceLamp * 0.1;
                }
            }
        }
    }
    if (!nextEventEstimation || !usedNextEventEstimation)
        // If next event estimation was used by last ray, we would be adding the emittance twice.
        result += rrFactor * objectMaterial->getEmittance();

    DoubleUnitVec3D newDirection = objectMaterial->getNewDirection(ray, normal);

    DoubleVec3D recursiveRadiance = traceRay(Ray(intersectionPoint, newDirection), nextEventEstimation && objectMaterial->worksWithNextEventEstimation(), intersection.kdTreeNode, bounces + 1);
    result += rrFactor * neeFactor * objectMaterial->computeCurrentRadiance(recursiveRadiance, dotProd(newDirection, normal));

    return result;
}

void displayRenderingProgression(unsigned int numberPixelXAlreadyComputed, unsigned int pictureWidth, double loopBeginningTime) {
    // Cannot be put in a thread -> else time estimation is completely wrong at the beginning of long renders
    // Don't want to redraw the whole picture for speed
    double timeAlreadySpent = getCurrentTimeSeconds() - loopBeginningTime;
    double timeEstimation = timeAlreadySpent * (pictureWidth - numberPixelXAlreadyComputed) / numberPixelXAlreadyComputed;

    // Putting std::string and + instead of << removes the cursor blinking, but we cannot modify the decimal precision
    std::cout << "\rProgress: " << (double)numberPixelXAlreadyComputed/pictureWidth*100
              << "%     Time already spent: " << timeAlreadySpent
              << "s     Estimated time left: " << timeEstimation
              << "s        ";
}


// Render method
Picture* Scene::render() {
    computeObjectsAndLamps();

    unsigned int pictureWidth = camera.getNumberPixelsX();
    unsigned int pictureHeight = camera.getNumberPixelsY();
    omp_set_num_threads(numberThreads);

    // Print informations
    displayParametersPage(false);
    std::cout << "Objects" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << "Number objects = " << objects.size() << std::endl;
    std::cout << "Number objects emitting light = " << lamps.size() << std::endl;
    std::cout << std::endl;
    std::cout << STAR_SPLITTER << std::endl;
    std::cout << std::endl;

    if (kdTree) {
        std::cout << "Creating a k-d tree...";
        double KDTreeBeginningTime = getCurrentTimeSeconds();
        KDTreeRoot = new KDTreeNode(objects, 10, 10);
        std::cout << "\rCreated a k-d tree in " << getCurrentTimeSeconds() - KDTreeBeginningTime << "s" << std::endl;
    }
    /*
    json jsonOutput = *KDTreeRoot;
    std::ofstream file;
    file.open("_tree.json");
    file << std::setw(4) << jsonOutput << std::endl;
    file.close();
    */

    // Compute picture
    Picture* result = new Picture(camera.getNumberPixelsX(), camera.getNumberPixelsY());

    std::cout << "Computing time estimation...";  // That's a lie. We're juste waiting for one iteration of the loop
    double loopBeginningTime = getCurrentTimeSeconds();
// "#pragma omp parallel for schedule(dynamic)" can be put here, but it makes the time estimation go weird (as a thread can go faster than another)
    for (unsigned int pixelX = 0; pixelX < pictureWidth; pixelX++) { 
#pragma omp parallel for
        for (int pixelY = 0; pixelY < pictureHeight; pixelY++) {  // pixelY must be signed for OpenMP
            result->setValuePix(pixelX, pixelY, DoubleVec3D(0.0));
            for (unsigned int sample = 0; sample < samplePerPixel; sample++) {
                Ray currentRay = camera.getRayGoingThrough(pixelX + randomDouble(), pixelY + randomDouble());
                result->addValuePix(pixelX, pixelY, traceRay(currentRay) / samplePerPixel);
            }
        }
        displayRenderingProgression(pixelX + 1, pictureWidth, loopBeginningTime);
    }

    result->setRenderTime(getCurrentTimeSeconds() - loopBeginningTime);
    std::cout << std::endl << std::endl;

    return result;
}


// Methods for interface
std::string Scene::getCurrentIndex(int currentIndex, bool displayIndex) const {  // private
    if (displayIndex)
        return std::to_string(currentIndex) + ") ";
    else
        return "";
}

void Scene::displayParametersPage(bool displayIndexes /*= true*/) const {
    int index = 0;

    std::cout << "Camera" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Picture width = " << camera.getNumberPixelsX() << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Picture height = " << camera.getNumberPixelsY() << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Origin = " << camera.getOrigin() << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Focal = " << camera.getFocal() << std::endl;
    std::cout << std::endl;

    std::cout << "Basic parameters" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Sample per pixel = " << samplePerPixel << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Minimum bounces = " << minBounces << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Max depth = " << maxDepth << std::endl;
    std::cout << std::endl;

    std::cout << "Optimisation parameters" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Number of threads = " << numberThreads << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Russian roulette = " << bool2string(russianRoulette) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Rr stop probability = " << rrStopProbability << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Next event estimation = " << bool2string(nextEventEstimation) << std::endl;
    std::cout << std::endl;
}

void Scene::displayObjectsPage() const {
    for (unsigned int i = 0; i < objectsGroups.size(); i++) {
        Object3DGroup currentObjectGroup = objectsGroups[i];

        std::cout << i << ") " << currentObjectGroup << std::endl << std::endl;
    }
}
