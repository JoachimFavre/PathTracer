#include "Scene.h"

// Constructors & Destructors
Scene::Scene() : Scene(PerspectiveCamera(), 8, 5, 10, 0.1) {}

Scene::Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth, double rrStopProbability)
	: camera(camera), samplePerPixel(samplePerPixel), minBounces(minBounces), maxDepth(maxDepth), rrStopProbability(rrStopProbability) {}

Scene::Scene(const Scene& scene)
	: Scene(scene.camera, scene.samplePerPixel, scene.minBounces, scene.maxDepth, scene.rrStopProbability) {}

Scene::~Scene() { resetObjects(); }


// Getters
std::vector<Object3D*> Scene::getObjects() const { return objects; }
std::vector<Object3D*> Scene::getLamps() const { return lamps; }
PerspectiveCamera Scene::getCamera() const { return camera; }
unsigned int Scene::getSamplePerPixel() const { return samplePerPixel; }
unsigned int Scene::getMinBounces() const { return minBounces; }
double Scene::getMaxDepth() const { return maxDepth; }
bool Scene::getRussianRoulette() const { return russianRoulette; }
double Scene::getRrStopProbability() const { return rrStopProbability; }
bool Scene::getNextEventEstimation() const { return nextEventEstimation; }
unsigned int Scene::getNumberThreads() const { return numberThreads; }


// Setters
void Scene::setObjects(std::vector<Object3D*> objects) {
	this->objects = objects;
	lamps = std::vector<Object3D*>();
	for (Object3D* object : objects)
		if (object->getMaterial()->getEmittance() > DBL_EPSILON)
			lamps.push_back(object);
}
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


// Add/Remove objects
void Scene::addObject(Object3D* object) {
	objects.push_back(object);
	if (object->getMaterial()->getEmittance() > DBL_EPSILON)
		lamps.push_back(object);
}

void Scene::resetObjects() {
	for (Object3D* object : objects)
		delete object;
	objects = std::vector<Object3D*>();
}

void Scene::importFBX(const char* filePath) {
	FbxManager* sdkManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(sdkManager, "");

	bool importStatus = importer->Initialize(filePath, -1, sdkManager->GetIOSettings());

	if (!importStatus) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", importer->GetStatus().GetErrorString());
		exit(-1);
	}

	FbxScene* fbxScene = FbxScene::Create(sdkManager, "myScene");
	importer->Import(fbxScene);
	importer->Destroy();

	FbxGeometryConverter clsConverter(sdkManager);
	bool triangulisationStatus = clsConverter.Triangulate(fbxScene, true);
	if (!triangulisationStatus) {
		std::cout << "Triangulisation could not be fully done" << std::endl;
		exit(-1);
	}

	FbxNode* rootNode = fbxScene->GetRootNode();

	for (int childNumber = 0; childNumber < rootNode->GetChildCount(); childNumber++) {
		FbxNode* child = rootNode->GetChild(childNumber);

		FbxAMatrix& childGlobalTransform = child->EvaluateGlobalTransform();
		DoubleVec3D translation = childGlobalTransform.GetT();
		DoubleVec3D rotation = childGlobalTransform.GetR();
		// DoubleVec3D scaling = childGlobalTransform.GetS();

		DoubleMatrix33 rotationMatrix = getRotationMatrixXYZ(rotation);

		FbxMesh* mesh = child->GetMesh();
		if (mesh != nullptr) {
			FbxVector4* controlPoints = mesh->GetControlPoints();
			for (int polygonIx = 0; polygonIx < mesh->GetPolygonCount(); polygonIx++) {
				if (mesh->GetPolygonSize(polygonIx) != 3) {
					std::cout << "This polygon is not a triangle";
					exit(-1);
				}

				DoubleVec3D vertex0 = rotationMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 0)] + translation;
				DoubleVec3D vertex1 = rotationMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 1)] + translation;
				DoubleVec3D vertex2 = rotationMatrix * controlPoints[mesh->GetPolygonVertex(polygonIx, 2)] + translation;

				Triangle* triangle = new Triangle(vertex0, vertex1, vertex2, new DiffuseMaterial(0.8));
				// Verify normals ?

				addObject(triangle);
			}
		}
	}

	std::cout << filePath << " was successfully oppened!" << std::endl << std::endl;
}


// Private method
DoubleVec3D Scene::traceRay(const Ray& ray, double usedNextEventEstimation /*= false*/, unsigned int bounces /*= 0*/) const {

	DoubleVec3D result(0.0);

	// Russian roulette
	double rrFactor = 1.0;
	if (bounces >= minBounces) {
		if (!russianRoulette || randomDouble() < rrStopProbability)
			return result;
		rrFactor = 1.0 / (1.0 - rrStopProbability);
	}

	// Search for ray intersection
	double smallestPositiveDistance = maxDepth + 1;  // Has to be strictly positive -> we don't want it to intersect with same object
	Object3D* closestObject = nullptr;
	for (Object3D* object : objects) {
		double distance = object->closestIntersection(ray);
		if (distance > 0.00001 && distance < smallestPositiveDistance) {
			smallestPositiveDistance = distance;
			closestObject = object;
		}
	}

	if (smallestPositiveDistance > maxDepth)  // Something must be hit
		return result;

	// Rendering equation
	Material* objectMaterial = closestObject->getMaterial();
	DoubleVec3D intersection = ray.getOrigin() + smallestPositiveDistance * ray.getDirection();
	DoubleUnitVec3D normal = closestObject->getNormal(intersection);

	if (nextEventEstimation && objectMaterial->worksWithNextEventEstimation()) {
		for (Object3D* lamp : lamps) {
			DoubleVec3D intersectionToLamp = lamp->getRandomPoint(randomDouble) - intersection;
			if (dotProd(normal, intersectionToLamp) > 0) {
				double distanceLamp = length(intersectionToLamp);
				Ray shadowRay(intersection, intersectionToLamp);  // intersectionToLamp goes in DoubleUnitVec3D constructor => normalised
				bool lampIsVisible(true);
				for (Object3D* object : objects) {
					if (object != lamp) {
						double distanceObject = object->closestIntersection(shadowRay);
						if (distanceObject > 0.00001 && distanceObject < distanceLamp) {
							lampIsVisible = false;
							break;
						}
					}
				}
				if (lampIsVisible) {
					intersectionToLamp /= distanceLamp;  // Normalised
					result += rrFactor * objectMaterial->computeCurrentColour(lamp->getMaterial()->getEmittance(), dotProd(intersectionToLamp, normal)) / distanceLamp / distanceLamp / 4 / M_PI;
					// result += rrFactor * lamp->getMaterial()->getEmittance() / distanceLamp / distanceLamp * 0.1;
				}
			}
		}
	}
	if (!nextEventEstimation || !usedNextEventEstimation)
		// If next event estimation was used by last ray, we would be adding the emittance twice.
		result += rrFactor * DoubleVec3D(objectMaterial->getEmittance());

	DoubleUnitVec3D newDirection = objectMaterial->getNewDirection(ray, normal, randomDouble);
	DoubleVec3D recursiveColour = traceRay(Ray(intersection, newDirection), nextEventEstimation && objectMaterial->worksWithNextEventEstimation(), bounces + 1);
	result += rrFactor * objectMaterial->computeCurrentColour(recursiveColour, dotProd(newDirection, normal));

	return result;
}

void Scene::displayRenderingProgression(unsigned int currentPixelX, double loopBeginningTime) const {
	unsigned int pictureWidth = camera.getNumberPixelsX();
	double timeAlreadySpent = getCurrentTimeSeconds() - loopBeginningTime;
	std::cout << "\rProgress: " << (double)currentPixelX/pictureWidth*100 << "%     Time already spent: " << timeAlreadySpent;
	std::cout << "s     Estimated time left: " << timeAlreadySpent*(pictureWidth - currentPixelX)/currentPixelX << "s        ";
}


// Other methods
Picture* Scene::render() const {
	unsigned int pictureWidth = camera.getNumberPixelsX();
	unsigned int pictureHeight = camera.getNumberPixelsY();
	omp_set_num_threads(numberThreads);

	// Print informations
	std::cout << "Width=" << pictureWidth << "     Height=" << pictureHeight << "     Sample/Pixel=" << samplePerPixel << "     Threads=" << numberThreads << std::endl;
	std::cout << "RussianRoulette=" << (russianRoulette ? "true" : "false") << "     MinBounces=" << minBounces << "     RrStopProbability=" << rrStopProbability << std::endl;
	std::cout << "NextEventEstimation=" << (nextEventEstimation ? "true" : "false") << std::endl;
	std::cout << std::endl;
	std::cout << "Number objects=" << objects.size() << "     Including lamps=" << lamps.size() << std::endl;
	std::cout << std::endl;

	Picture* result = new Picture(camera.getNumberPixelsX(), camera.getNumberPixelsY());

	double loopBeginningTime = getCurrentTimeSeconds();
	// If #pragma omp parallel for is here, it goes faster, but it cannot display percentage or estimated time left.
	for (unsigned int pixelX = 0; pixelX < pictureWidth; pixelX++) {
		displayRenderingProgression(pixelX, loopBeginningTime);
#pragma omp parallel for
		for (int pixelY = 0; pixelY < pictureHeight; pixelY++) {  // pixelY must be signed for OpenMP
			result->setValuePix(pixelX, pixelY, DoubleVec3D(0.0));
			for (unsigned int sample = 0; sample < samplePerPixel; sample++) {
				Ray currentRay = camera.getRayGoingThrough(pixelX + randomDouble() - 0.5, pixelY + randomDouble() - 0.5);
				result->addValuePix(pixelX, pixelY, traceRay(currentRay) / samplePerPixel);
			}
		}
	}

	displayRenderingProgression(pictureWidth, loopBeginningTime);  // To display the 100%
	std::cout << std::endl;

	return result;
}