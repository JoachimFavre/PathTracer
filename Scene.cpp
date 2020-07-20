#include "Scene.h"

// Constructors & Destructors
Scene::Scene() : Scene(PerspectiveCamera(), 8, 5, 10) {}

Scene::Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth)
	: camera(camera), samplePerPixel(samplePerPixel), minBounces(minBounces), maxDepth(maxDepth), unif(0, 1),
	  re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
{}

Scene::Scene(const Scene& scene)
	: Scene(scene.camera, scene.samplePerPixel, scene.minBounces, scene.maxDepth) {}

Scene::~Scene() { resetObjects(); }
