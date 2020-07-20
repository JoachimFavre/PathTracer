#include <chrono>
#include <random>
#include <vector>

#include <omp.h>

#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "Picture.h"

#ifndef DEF_SCENE
#define DEF_SCENE

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

	bool russianRoulette = true;
	double rrStopProbability = 0.1;
	bool nextEventEstimation = true;
	unsigned int numberThreads = 8;

	DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, unsigned int bounces = 0);

public:
	Scene();
	Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth);
	Scene(const Scene& scene);
	~Scene();

	void addObject(Object3D* object);
	void resetObjects();
	std::vector<Object3D*> getObjects();

	Picture* render();

};

#endif