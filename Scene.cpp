#include "Scene.h"

// Constructors & Destructors
Scene::Scene(PerspectiveCamera camera /*= PerspectiveCamera()*/, unsigned int samplesPerPixel /*= 8*/, unsigned int minBounces /*= 5*/)
    : camera(camera), samplesPerPixel(samplesPerPixel), minBounces(minBounces) {}

Scene::Scene(const Scene& scene)
    : Scene(scene.camera, scene.samplesPerPixel, scene.minBounces) {}


// Getters
std::vector<Object3DGroup> Scene::getObjectGroups() const { return objectGroups; }
std::vector<Object3DGroup>& Scene::getObjectGroupsReference() { return objectGroups; }


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
unsigned int Scene::getSamplesPerPixel() const { return samplesPerPixel; }
unsigned int Scene::getMinBounces() const { return minBounces; }
bool Scene::getRussianRoulette() const { return russianRoulette; }
double Scene::getRrStopProbability() const { return rrStopProbability; }
bool Scene::getNextEventEstimation() const { return nextEventEstimation; }
unsigned int Scene::getNumberThreads() const { return numberThreads; }
bool Scene::getKDTree() const { return kdTree; }
unsigned int Scene::getKDMaxObjectNumber() const { return kdMaxObjectNumber; }
unsigned int Scene::getKDMaxDepth() const { return kdMaxDepth; }
std::string Scene::getBackupFileName() const { return backupFileName; }
bool Scene::getBackupParameters() const { return backupParameters; }
bool Scene::getBackupObjectGroups() const { return backupObjectGroups; }
bool Scene::getBackupPicture() const { return backupPicture; }
double Scene::getLeastRenderTime4PictureBackup() const { return leastRenderTime4PictureBackup; }


// Setters
void Scene::setObjectGroups(std::vector<Object3DGroup> groups) { objectGroups = groups; }
void Scene::setCamera(PerspectiveCamera camera) { this->camera = camera; }
void Scene::setSamplesPerPixel(unsigned int samplesPerPixel) { this->samplesPerPixel = samplesPerPixel; }
void Scene::setMinBounces(unsigned int minBounces) { this->minBounces = minBounces; }
void Scene::setRussianRoulette(bool russianRoulette) { this->russianRoulette = russianRoulette; }
void Scene::setRussianRoulette(bool russianRoulette, double rrStopProbability) {
    this->russianRoulette = russianRoulette;
    this->rrStopProbability = rrStopProbability;
}
void Scene::setRrStopProbability(double rrStopProbability) { this->rrStopProbability = rrStopProbability; }
void Scene::setNextEventEstimation(bool nextEventEstimation) { this->nextEventEstimation = nextEventEstimation; }
void Scene::setNumberThreads(unsigned int numberThreads) { this->numberThreads = numberThreads; }
void Scene::setKDTree(bool kdTree) { this->kdTree = kdTree; }
void Scene::setKDMaxObjectNumber(unsigned int kdMaxObjectNumber) { this->kdMaxObjectNumber = kdMaxObjectNumber; }
void Scene::setKDMaxDepth(unsigned int kdMaxDepth) { this->kdMaxDepth = kdMaxDepth; }
void Scene::setBackupFileName(std::string backupFileName) { this->backupFileName = backupFileName; }
void Scene::setBackupParameters(bool backupParameters) { this->backupParameters = backupParameters; }
void Scene::setBackupObjectGroups(bool backupObjectGroups) { this->backupObjectGroups = backupObjectGroups; }
void Scene::setBackupPicture(bool backupPicture) { this->backupPicture = backupPicture; }
void Scene::setLeastRenderTime4PictureBackup(double leastRenderTime4PictureBackup) { this->leastRenderTime4PictureBackup = leastRenderTime4PictureBackup; }


// Object groups management
void Scene::addObjectGroup(const Object3DGroup& group) {
    objectGroups.push_back(group);
}

void Scene::resetAndDeleteObjectGroups() {
    for (Object3DGroup objectGroup : objectGroups)
        objectGroup.resetAndDeleteObjects();
    objectGroups.clear();
}

void Scene::computeObjectsAndLamps() {
    objects = split(objectGroups);
    lamps.clear();

    for (Object3D* object : objects) {
        if (!object->getMaterial()->getEmittance().isZero())
            lamps.push_back(object);
    }
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

bool Scene::importFBXFile(const char* filePath, Material* material, std::string name) {
    std::cout << "Importing fbx file...";
    double importationBeginningTime = getCurrentTimeSeconds();

    FbxManager* sdkManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
    sdkManager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(sdkManager, "");

    bool importStatus = importer->Initialize(filePath, -1, sdkManager->GetIOSettings());

    if (!importStatus) {
        std::cout << "\rError in the importation: " << importer->GetStatus().GetErrorString() << std::endl;
        return false;
    }

    FbxScene* fbxScene = FbxScene::Create(sdkManager, "myScene");
    importer->Import(fbxScene);
    importer->Destroy();

    FbxGeometryConverter clsConverter(sdkManager);
    bool triangulisationStatus = clsConverter.Triangulate(fbxScene, true);
    if (!triangulisationStatus) {
        std::cout << "\rError in the importation: triangulisation could not be fully done" << std::endl;
        return false;
    }

    FbxNode* rootNode = fbxScene->GetRootNode();
    std::vector<Object3D*> objects;

    bool importedAllFbxNodeAsTriangles = importTrianglesFromFbxNode(rootNode, material, objects);
    delete material; // Only made copies.
    if (!importedAllFbxNodeAsTriangles)
        return false;

    addObjectGroup(Object3DGroup(name, objects));
    std::cout << "\r" << filePath << " was successfully imported in " << getCurrentTimeSeconds() - importationBeginningTime << " seconds!" << std::endl;
    return true;
}

bool importTrianglesFromFbxNode(FbxNode* node, Material* material, std::vector<Object3D*>& objects) {
    for (int childNumber = 0; childNumber < node->GetChildCount(); childNumber++) {
        FbxNode* child = node->GetChild(childNumber);
        
        if (!importTrianglesFromFbxNode(child, material, objects))  // Recursive call
            return false;

        FbxMesh* mesh = child->GetMesh();

        if (mesh != nullptr) {
            FbxAMatrix& childGlobalTransform = child->EvaluateGlobalTransform();
            DoubleVec3D translation = childGlobalTransform.GetT();
            DoubleVec3D rotation = childGlobalTransform.GetR() * M_PI / 180; // Gets converted in radians
            DoubleVec3D scaling = childGlobalTransform.GetS();
            DoubleMatrix33 rotationAndScalingMatrix = getRotationMatrixXYZ(rotation)*getScalingMatrixXYZ(scaling);  // order is important

            FbxVector4* controlPoints = mesh->GetControlPoints();
            // Add each triangle to the scene
            for (int polygonIx = 0; polygonIx < mesh->GetPolygonCount(); polygonIx++) {
                if (mesh->GetPolygonSize(polygonIx) != 3) {
                    std::cout << "\rError in the importation: a polygon is not a triangle" << std::endl;
                    return false;
                }

                FbxLayer* layer = mesh->GetLayer(0);

                DoubleVec3D vertex0 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 0)] + translation;
                DoubleVec3D vertex1 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 1)] + translation;
                DoubleVec3D vertex2 = rotationAndScalingMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 2)] + translation;

                objects.push_back(new Triangle(vertex0, vertex1, vertex2, material->deepCopy()));
            }
        }
    }
    return true;
}


// Save
void Scene::saveParameters2File(std::string fileName) const {
    json jsonOutput = {
    {"Camera", {
        {"NumberPixelsX", camera.getNumberPixelsX()},
        {"NumberPixelsY", camera.getNumberPixelsY()},
        {"Focal", camera.getFocal()},
        {"Origin", camera.getOrigin()}
        }
    },
    {"BasicParameters", {
        {"SamplesPerPixel", samplesPerPixel},
        {"MinBounces", minBounces}
        }
    },
    {"OptimisationParameters", {
        {"NumberThreads", numberThreads},
        {"RussianRoulette", russianRoulette},
        {"RrStopProbability", rrStopProbability},
        {"NextEventEstimation", nextEventEstimation},
        {"KDTree", kdTree},
        {"KDMaxDepth", kdMaxDepth},
        {"KDMaxObjectNumber", kdMaxObjectNumber}
        }
    },
    {"BackupParameters", {
        {"BackupFileName", backupFileName},
        {"BackupParameters", backupParameters},
        {"BackupObjectGroups", backupObjectGroups},
        {"BackupPicture", backupPicture},
        {"LeastRenderTime4PictureBackup", leastRenderTime4PictureBackup}
        }
    }
    };

    std::ofstream file;
    file.open(fileName);
    file << std::setw(4) << jsonOutput << std::endl;
    file.close();
}

void Scene::saveObjectGroups2File(std::string fileName) const {
    json jsonOutput;
    for (Object3DGroup group : objectGroups) {
        jsonOutput.push_back(group);
    }

    std::ofstream file;
    file.open(fileName);
    file << std::setw(4) << jsonOutput << std::endl;
    file.close();
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
        intersection = kdTreeRoot->getIntersectionForward(ray);
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
        neeFactor = 1.0 / lamps.size();
        for (Object3D* lamp : lamps) {
            DoubleVec3D pointOnLamp = lamp->getRandomPoint();
            DoubleVec3D intersectionToLamp = pointOnLamp - intersectionPoint;
            if (dotProd(normal, intersectionToLamp) > -0.0001) {
                double distanceLamp = length(intersectionToLamp);
                Ray shadowRay(intersectionPoint, intersectionToLamp);  // intersectionToLamp goes in DoubleUnitVec3D constructor => normalised

                KDTreeNode::Intersection shadowRayIntersection;
                if (!kdTree)
                    shadowRayIntersection = bruteForceIntersection(shadowRay);
                else if (intersection.kdTreeNode == nullptr)
                    shadowRayIntersection = kdTreeRoot->getIntersectionForward(shadowRay);
                else
                    shadowRayIntersection = intersection.kdTreeNode->getIntersectionBackward(shadowRay);

                if (distanceLamp - 0.00001 < shadowRayIntersection.distance && shadowRayIntersection.distance < distanceLamp + 0.00001) {
                    intersectionToLamp /= distanceLamp;  // Normalised

                    result += rrFactor * neeFactor * objectMaterial->computeCurrentRadiance(lamp->getMaterial()->getEmittance(), dotProd(intersectionToLamp, normal), true)
                              * lamp->getArea() / distanceLamp / distanceLamp * dotProd(lamp->getNormal(pointOnLamp), -intersectionToLamp);
                }
            }
        }
    }
    if (!nextEventEstimation || !usedNextEventEstimation)
        // If next event estimation was used by last ray, we would be adding the emittance twice.
        result += rrFactor * objectMaterial->getEmittance();

    DoubleUnitVec3D newDirection = objectMaterial->getNewDirection(ray, normal);

    DoubleVec3D recursiveRadiance = traceRay(Ray(intersectionPoint, newDirection), nextEventEstimation && objectMaterial->worksWithNextEventEstimation(), intersection.kdTreeNode, bounces + 1);
    result += rrFactor * objectMaterial->computeCurrentRadiance(recursiveRadiance, dotProd(newDirection, normal));

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
    showCMDCursor(false);

    // Print information
    clearScreenPrintHeader();
    displayParametersPage(false);
    std::cout << "Objects" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << "Number of objects = " << objects.size() << std::endl;
    std::cout << "Number of objects emitting light = " << lamps.size() << std::endl;
    std::cout << std::endl;
    std::cout << STAR_SPLITTER << std::endl;
    std::cout << std::endl;

    if (backupParameters) {
        std::cout << "Backing up parameters...";
        double parametersBackupBeginningTime = getCurrentTimeSeconds();
        std::string parametersBackupFileName = formatFileName(backupFileName, PARAMETERS_SAVE_EXTENSION);
        saveParameters2File(parametersBackupFileName);
        std::cout << "\rSuccessfully backed up parameters to " << parametersBackupFileName << " in " << getCurrentTimeSeconds() - parametersBackupBeginningTime << " seconds." << std::endl;
    }

    if (backupObjectGroups) {
        std::cout << "Backing up object groups...";
        double objectGroupsBackupBeginningTime = getCurrentTimeSeconds();
        std::string objectGroupsBackupFileName = formatFileName(backupFileName, OBJECTS_SAVE_EXTENSION);
        saveObjectGroups2File(objectGroupsBackupFileName);
        std::cout << "\rSuccessfully backed up object groups to " << objectGroupsBackupFileName << " in " << getCurrentTimeSeconds() - objectGroupsBackupBeginningTime << " seconds." << std::endl;
    }

    if (kdTree) {
        std::cout << "Creating a k-d tree...";
        double kdTreeBeginningTime = getCurrentTimeSeconds();
        kdTreeRoot = new KDTreeNode(objects, kdMaxObjectNumber, kdMaxDepth);
        std::cout << "\rSuccessfully created a k-d tree in " << getCurrentTimeSeconds() - kdTreeBeginningTime << " seconds. Its maximum depth is " << kdTreeRoot->getMaxDepth() << " and the maximum number of objects in a single leaf is " << kdTreeRoot->getMaxObjectNumberLeaf() << "." << std::endl;
    }
    /*
    json jsonOutput = *kdTreeRoot;
    std::ofstream file;
    file.open("_tree.json");
    file << std::setw(4) << jsonOutput << std::endl;
    file.close();
    */

    // Compute picture
    std::cout << "Allocating memory for the picture...";
    double pictureMemoryAllocationBeginningTime = getCurrentTimeSeconds();
    Picture* result = new Picture(camera.getNumberPixelsX(), camera.getNumberPixelsY());
    std::cout << "\rSuccessfully allocated memory for the picture in " << getCurrentTimeSeconds() - pictureMemoryAllocationBeginningTime  << " seconds." << std::endl << std::endl;

    std::cout << "Computing time estimation...";  // That's a lie. We're juste waiting for one iteration of the loop
    double loopBeginningTime = getCurrentTimeSeconds();
// "#pragma omp parallel for schedule(dynamic)" can be put here, but it makes the time estimation go weird (as a thread can go faster than another)
    for (unsigned int pixelX = 0; pixelX < pictureWidth; pixelX++) { 
#pragma omp parallel for
        for (int pixelY = 0; pixelY < pictureHeight; pixelY++) {  // pixelY must be signed for OpenMP
            result->setValuePix(pixelX, pixelY, DoubleVec3D(0.0));
            for (unsigned int sample = 0; sample < samplesPerPixel; sample++) {
                Ray currentRay = camera.getRayGoingThrough(pixelX + randomDouble(), pixelY + randomDouble());
                result->addValuePix(pixelX, pixelY, traceRay(currentRay) / samplesPerPixel);
            }
        }
        displayRenderingProgression(pixelX + 1, pictureWidth, loopBeginningTime);
    }

    double renderTime = getCurrentTimeSeconds() - loopBeginningTime;
    result->setRenderTime(renderTime);

    std::cout << std::endl << std::endl;

    if (backupPicture && renderTime > leastRenderTime4PictureBackup) {
        double beginningTime = getCurrentTimeSeconds();
        std::cout << "Backing up the picture...";

        std::string pictureBackupFileName = formatFileName(backupFileName, PICTURE_SAVE_EXTENSION_JSON);

        json jsonOutput = *result;
        std::ofstream file;
        file.open(pictureBackupFileName);
        file << std::setw(4) << jsonOutput << std::endl;
        file.close();

        std::cout << "\rSuccessfully backed up the picture to " << pictureBackupFileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
    }

    if (kdTree)
        delete kdTreeRoot;

    showCMDCursor(true);
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
    std::cout << getCurrentIndex(index++, displayIndexes) + "Samples per pixel = " << samplesPerPixel << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Minimum bounces = " << minBounces << std::endl;
    std::cout << std::endl;

    std::cout << "Optimisation parameters" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Number of CPU threads = " << numberThreads << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Russian roulette = " << bool2string(russianRoulette) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Rr stop probability = " << rrStopProbability << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Next event estimation = " << bool2string(nextEventEstimation) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "K-d tree = " << bool2string(kdTree) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "K-d maximum depth = " << kdMaxDepth << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "K-d maximum object number = " << kdMaxObjectNumber << std::endl;
    std::cout << std::endl;

    std::cout << "Backup parameters" << std::endl;
    std::cout << DASH_SPLITTER << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Backup file name = " << backupFileName << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Backup parameters = " << bool2string(backupParameters) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Backup object groups = " << bool2string(backupObjectGroups) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Backup picture = " << bool2string(backupPicture) << std::endl;
    std::cout << getCurrentIndex(index++, displayIndexes) + "Least render time for picture backup = " << leastRenderTime4PictureBackup << std::endl;
    std::cout << std::endl;
}

void Scene::displayObjectsPage() const {
    for (unsigned int i = 0; i < objectGroups.size(); i++) {
        Object3DGroup currentObjectGroup = objectGroups[i];

        std::cout << i << ") " << currentObjectGroup << std::endl << std::endl;
    }
}
