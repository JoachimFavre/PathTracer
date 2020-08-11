#ifndef DEF_SCENE
#define DEF_SCENE

#include <chrono>
#include <random>
#include <vector>

#include <omp.h>

#include "DiffuseMaterial.h"
#include "DoubleMatrix33.h"
#include "Object3D.h"
#include "Triangle.h"
#include "PerspectiveCamera.h"
#include "Picture.h"
#include "RefractiveMaterial.h"
#include "SpecularMaterial.h"
#include "Sphere.h"

#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include <fbxsdk/utils/fbxgeometryconverter.h>

// New seed each time
static std::uniform_real_distribution<double> unif(0, 1);
static std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
static double randomDouble() { return unif(re); }

static double getCurrentTimeSeconds() {
	return (double)std::chrono::system_clock::now().time_since_epoch().count() / std::chrono::system_clock::period::den;
}

class Scene {
private:
	std::vector<Object3D*> objects;
	std::vector<Object3D*> lamps;

	PerspectiveCamera camera;
	unsigned int samplePerPixel;
	unsigned int minBounces;
	double maxDepth;
	double rrStopProbability;  // Linked to russianRoulette   /  stopProb=1 <=> russianRoulette=false

	bool russianRoulette = true;
	bool nextEventEstimation = true;
	unsigned int numberThreads = 8;

	DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, unsigned int bounces = 0) const;
	void displayRenderingProgression(unsigned int currentPixelX, double loopBeginningTime) const;

public:
	Scene();
	Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth, double rrStopProbability);
	Scene(const Scene& scene);
	~Scene();

	std::vector<Object3D*> getObjects() const;
	std::vector<Object3D*> getLamps() const;
	PerspectiveCamera getCamera() const;
	unsigned int getSamplePerPixel() const;
	unsigned int getMinBounces() const;
	double getMaxDepth() const;
	bool getRussianRoulette() const;
	double getRrStopProbability() const;
	bool getNextEventEstimation() const;
	unsigned int getNumberThreads() const;

	void setObjects(std::vector<Object3D*> objects);
	void setCamera(PerspectiveCamera camera);
	void setSamplePerPixel(unsigned int samplePerPixel);
	void setMinBounces(unsigned int minBounces);
	void setMaxDepth(double maxDepth);
	void setRussianRoulette(bool russianRoulette);
	void setRussianRoulette(bool russianRoulette, double rrStopProbability);
	void setRrStopProbability(double rrStopProbability);
	void setNextEventEstimation(bool nextEventEstimation);
	void setNumberThreads(unsigned int numberThreads);

	void addObject(Object3D* object);
	void resetObjects();
	void defaultScene();
	void importFBX(const char* filePath);

	Picture* render() const;
};

#endif