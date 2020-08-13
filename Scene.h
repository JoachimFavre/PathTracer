#ifndef DEF_SCENE
#define DEF_SCENE

#include <random>
#include <vector>

#include <omp.h>

#include "DiffuseMaterial.h"
#include "DoubleMatrix33.h"
#include "Object3D.h"
#include "Object3DGroup.h"
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

class Scene {
private:
	std::vector<Object3DGroup> objectsGroups;
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

	std::vector<Object3DGroup> getObjectsGroups() const;
	std::vector<Object3DGroup>& getObjectsGroupsReference();  // Reference -> can modify it -> != const
	std::vector<Object3D*> getObjects();
	std::vector<Object3D*> getLamps();
	PerspectiveCamera getCamera() const;
	PerspectiveCamera& getCameraReference();
	unsigned int getSamplePerPixel() const;
	unsigned int getMinBounces() const;
	double getMaxDepth() const;
	bool getRussianRoulette() const;
	double getRrStopProbability() const;
	bool getNextEventEstimation() const;
	unsigned int getNumberThreads() const;

	void setObjectsGroups(std::vector<Object3DGroup> groups);
	void setCamera(PerspectiveCamera camera);
	void setSamplePerPixel(unsigned int samplePerPixel);
	void setMinBounces(unsigned int minBounces);
	void setMaxDepth(double maxDepth);
	void setRussianRoulette(bool russianRoulette);
	void setRussianRoulette(bool russianRoulette, double rrStopProbability);
	void setRrStopProbability(double rrStopProbability);
	void setNextEventEstimation(bool nextEventEstimation);
	void setNumberThreads(unsigned int numberThreads);

	void addObjectGroup(const Object3DGroup& group);
	void resetObjectGroups();
	void computeObjectsAndLamps();
	void defaultScene();
	void importFBX(const char* filePath);

	Picture* render();
};

#endif
