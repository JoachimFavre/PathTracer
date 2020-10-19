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


//! Uniform distrbution between 0 and 1.
static std::uniform_real_distribution<double> unif(0, 1);

//! Random engine that has a different seed each compilation.
static std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

//! Computes a random double between 0 and 1
/*!
	\return A random double between 0 and 1 generated following a uniform distrbution.
*/
static double randomDouble() { return unif(re); }

//! 
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
	std::string getCurrentIndex(int currentIndex, bool displayIndex) const;

public:
	//! Default constructor.
	/*!
		By default, samplePerPixel is set to 8, minBounces is set to 5, maxDepth is set to 10 and rrStopProbability is set to 0.1.
	*/
	Scene();

	//! Main constructor.
	/*!
		\param camera The camera that will be used for the render.
		\param samplePerPixel The number of ray casted per pixel. Increasing it will give a higher quality, but at a cost of a linearly increasing time.
		\param minBounces The minimum number of bounces that each ray will do. It can be less if the ray does not intersect with any object.
		\param maxDepth The maximum distance each ray can do between two bounces.
		\param rrStopProbability The probability that the ray stops. See russian roulette path termination in my TM's report for further information.
	*/
	Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth, double rrStopProbability);
	
	//! Copy constructor.
	/*!
		\param scene The scene that will be copied.
	*/
	Scene(const Scene& scene);

	//! Getter for the objects groups.
	/*!
		\return This scene's objects groups.
	*/
	std::vector<Object3DGroup> getObjectsGroups() const;

	//! Getter for a reference to the objects groups.
	/*!
		\return A reference to this scene's objects groups.
	*/
	std::vector<Object3DGroup>& getObjectsGroupsReference();  // Reference -> can modify it -> != const
	
	//! Getter for the objects.
	/*!
		Calls computeObjectsAndLamps().
		\return This scene's objects.
		\sa split()
	*/
	std::vector<Object3D*> getObjects();

	//! Getter for the lamps.
	/*!
		Calls computeObjectsAndLamps().
		\return This scene's objects that have an emittance strictly greater than 0.
		\sa getObjects()
	*/
	std::vector<Object3D*> getLamps();

	//! Getter for the camera.
	/*!
		\return This scene's camera.
	*/
	PerspectiveCamera getCamera() const;

	//! Getter for a reference to the camera.
	/*!
		\return A reference to this scene's camera.
	*/
	PerspectiveCamera& getCameraReference();

	//! Getter for the number of samples per pixel.
	/*!
		\return The number of samples per pixel that will be used during the render.
		\sa Scene()
	*/
	unsigned int getSamplePerPixel() const;

	//! Getter for the minimum number of bounces.
	/*!
		\return The minimum number of bounces that will be used during the render.
		\sa Scene()
	*/
	unsigned int getMinBounces() const;
	
	//! Getter for the maximum depth.
	/*!
		\return The maximum depth that will be used during the render.
		\sa Scene()
	*/
	double getMaxDepth() const;

	//! Getter for the russian roulette.
	/*!
		See my TM's report for further information on this algorithm.
		\return Whether the russian roulette path termination algorithm will be used during the render.
		\sa getRrStopProbability()
	*/
	bool getRussianRoulette() const;

	//! Getter for the russian roulette stop probability.
	/*!
		Russian roulette stop probability that will be used during the render.
		\sa Scene(), getRussianRoulette()
	*/
	double getRrStopProbability() const;

	//! Getter for the next event estimation.
	/*!
		See my TM's report for further information on this algorithm.
		\return Whether the next event estimation algorithm will be used during the render.
	*/
	bool getNextEventEstimation() const;

	//! Getter for the number of CPU threads.
	/*!
		\return The number of threads that will be used on the CPU during the render.
	*/
	unsigned int getNumberThreads() const;


	//! Setter for the objects groups.
	/*!
		\param groups The new objects groups of this scene.
	*/
	void setObjectsGroups(std::vector<Object3DGroup> groups);

	//! Setter for the camera.
	/*!
		\param camera The new camera that will be used during the render.
	*/
	void setCamera(PerspectiveCamera camera);

	//! Setter for the number of samples per pixel.
	/*!
		\param samplePerPixel The new number of samples per pixel that will be used during the render.
		\sa Scene()
	*/
	void setSamplePerPixel(unsigned int samplePerPixel);

	//! Setter for the minimum number of bounces.
	/*!
		\param minBounces The new minimum number of bounces that will be used during the render.
		\sa Scene()
	*/
	void setMinBounces(unsigned int minBounces);
	
	//! Setter for the maximum depth.
	/*!
		\param maxDepth The new maximum depth that will be used during the render.
		\sa Scene()
	*/
	void setMaxDepth(double maxDepth);

	//! Setter for the russian roulette.
	/*!
		See my TM's report for further information on this algorithm.
		\param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.
	*/
	void setRussianRoulette(bool russianRoulette);

	//! Setter for the russian roulette and russian roulette stop probability.
	/*!
		See my TM's report for further information on this algorithm.
		\param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.
		\param rrStopProbability The new russian roulette stop probability that will be used during the render.
		\sa Scene().
	*/
	void setRussianRoulette(bool russianRoulette, double rrStopProbability);

	//! Setter for the russian roulette stop probability
	/*!
		See my TM's report for further information on this algorithm.
		\param rrStopProbability The new russian roulette stop probability that will be used during the render.
		\sa Scene().
	*/
	void setRrStopProbability(double rrStopProbability);

	//! Setter for the next event estimation.
	/*!
		See my TM's report for further information on this algorithm.
		\param nextEventEstimation Whether the next event estimation algorithm will be used during the render.
	*/
	void setNextEventEstimation(bool nextEventEstimation);

	//! Setter for the number of CPU threads.
	/*!
		\param numberThreads The new number of threads that will be used on the CPU during the render.
	*/
	void setNumberThreads(unsigned int numberThreads);


	//! Adds an objects group to the current ones.
	/*!
		\param group The objects group that will be added.
	*/
	void addObjectGroup(const Object3DGroup& group);

	//! Destroys all the objects groups.
	void resetObjectGroups();

	//! Computes all the objects
	/*!
		Also stores a vector of all objects having an emitance strictly greater than 1, to go faster with the next event estimation algorithm.
	*/
	void computeObjectsAndLamps();

	//! Sets this scene's objects to default ones.
	/*!
		The look is similar to the Cornell box.
	*/
	void defaultScene();
	
	//! Imports a FBX file as triangles.
	/*!
		Uses the FBX SDK library.
		\param filePath The path the FBX file.
		\param material The material that will be used for all the triangles which will be imported.
		\param name The name of the objects group in which all triangles will be stored.
		\return True if the importation was successful, false else.
	*/
	bool importFBX(const char* filePath, Material* material, std::string name);


	//! Start the render of the picture.
	/*!
		This uses the path tracing algorithm (you could have read this project's title for this information) and some optimisations such as next event estimation and russian roulette path termination.
		\return A pointer to the rendered picture.
	*/
	Picture* render();

	//! Prints the parameters page.
	/*!
		This is one of the main pages.
		\param displayIndexes If true it will print the indexes before each parameter. This is useful if for the user to be able to change them, but you can remove them if you only want the information.
		\sa displayObjectsPage()
	*/
	void displayParametersPage(bool displayIndexes = true) const;

	//! Prints the objects page.
	/*!
		This is one of the main pages.
		\sa displayParametersPage()
	*/
	void displayObjectsPage() const;
};


//! Prints the progression information
/*!
	This is used during the rendering.
	\param currentPixelX The *x* coordinate of the pixel we are currently treating.
	\param pictureWidth The width of the picture we are rendering.
	\param loopBeginningTime The number of seconds between 01/01/1970 and the beginning of the render.
	\sa render()
*/
void displayRenderingProgression(unsigned int currentPixelX, unsigned int pictureWidth, double loopBeginningTime);

#endif
