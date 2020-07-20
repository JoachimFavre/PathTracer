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
	DoubleVec3D normal = closestObject->getNormal(intersection);

	if (nextEventEstimation && objectMaterial->worksWithNextEventEstimation()) {
		for (Object3D* lamp : lamps) {
			DoubleVec3D intersectionToLamp = lamp->getRandomPoint(randomDouble) - intersection;
			if (dotProd(normal, intersectionToLamp) > 0) {
				double distanceLamp = length(intersectionToLamp);
				Ray shadowRay(intersection, intersectionToLamp);
				bool lampIsVisible(true);
				for (Object3D* object : objects) {
					if (object != lamp) {
						double distanceObject = object->closestIntersection(shadowRay);
						if (distanceObject > DBL_EPSILON && distanceObject < distanceLamp) {
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
		// If use the next event estimation, we don't want to add this emittance twice.
		result += rrFactor * DoubleVec3D(objectMaterial->getEmittance());

	DoubleVec3D newDirection = objectMaterial->getNewDirection(ray, normal, randomDouble);
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

	displayRenderingProgression(pictureWidth, loopBeginningTime);  // To display 100%
	std::cout << std::endl;

	return result;
}