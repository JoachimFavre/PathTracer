#include <chrono>
#include <random>
#include <vector>

#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "Picture.h"

#ifndef DEF_SCENE
#define DEF_SCENE

class Scene {
private:
	std::uniform_real_distribution<double> unif;
	std::default_random_engine re;

	std::vector<Object3D*> objects;
	std::vector<Object3D*> lamps;

	PerspectiveCamera camera;
	unsigned int samplePerPixel;
	unsigned int minBounces;
	double maxDepth;

	bool russianRoulette = true;
	double rrStopProbability = 0.1;
	bool nextEventEstimation = true;
	unsigned int numberThreads = 1;

	double randomDouble();
	DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, unsigned int bounces = 0);

public:
	Scene();
	Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth);
	Scene(const Scene&);
	~Scene();

	void addObject(Object3D* object);
	void resetObjects();
	std::vector<Object3D*> objects;

	Picture* render(double middleGray);

};

#endif