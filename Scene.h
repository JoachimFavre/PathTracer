#ifndef DEF_SCENE
#define DEF_SCENE

#include <omp.h>

#include "DoubleMatrix33.h"
#include "Object3DGroup.h"
#include "PerspectiveCamera.h"
#include "Picture.h"

#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include <fbxsdk/utils/fbxgeometryconverter.h>


/*!
    \file Scene.h
    \brief Defines the Scene class and the functions around it.

    \class Scene
    \brief Stores objects groups and a camera for the render.

    \fn Scene::Scene()
    \brief Default constructor.
    \details By default, samplePerPixel is set to 8, minBounces is set to 5, maxDepth is set to 10 and rrStopProbability is set to 0.1.

    \fn Scene::Scene(PerspectiveCamera camera, unsigned int samplePerPixel, unsigned int minBounces, double maxDepth, double rrStopProbability)
    \brief Main constructor.
    \param camera The camera that will be used for the render.
    \param samplePerPixel The number of ray casted per pixel. Increasing it will give a higher quality, but at a cost of a linearly increasing time.
    \param minBounces The minimum number of bounces that each ray will do. It can be less if the ray does not intersect with any object.
    \param maxDepth The maximum distance each ray can do between two bounces.
    \param rrStopProbability The probability that the ray stops. See russian roulette path termination in my TM's report for further information.

    \fn Scene::Scene(const Scene& scene)
    \brief Copy constructor.
    \param scene The scene that will be copied.

    \fn Scene::getObjectsGroups()
    \brief Getter for the objects groups.
    \return This scene's objects groups.

    \fn Scene::getObjectsGroupsReference()
    \brief Getter for a reference to the objects groups.
    \return A reference to this scene's objects groups.

    \fn Scene::getObjects()
    \brief Getter for the objects.
    \details Calls computeObjectsAndLamps().
    \return This scene's objects.
    \sa split()

    \fn Scene::getLamps()
    \brief Getter for the lamps.
    \details Calls computeObjectsAndLamps().
    \return This scene's objects that have an emittance strictly greater than 0.
    \sa getObjects()

    \fn Scene::getCamera()
    \brief Getter for the camera.
    \return This scene's camera.

    \fn Scene::getCameraReference()
    \brief Getter for a reference to the camera.
    \return A reference to this scene's camera.

    \fn Scene::getSamplePerPixel()
    \brief Getter for the number of samples per pixel.
    \return The number of samples per pixel that will be used during the render.
    \sa Scene()

    \fn Scene::getMinBounces()
    \brief Getter for the minimum number of bounces.
    \return The minimum number of bounces that will be used during the render.
    \sa Scene()

    \fn Scene::getMaxDepth()
    \brief Getter for the maximum depth.
    \return The maximum depth that will be used during the render.
    \sa Scene()

    \fn Scene::getRussianRoulette()
    \brief Getter for the russian roulette.
    \details See my TM's report for further information on this algorithm.
    \return Whether the russian roulette path termination algorithm will be used during the render.
    \sa getRrStopProbability()

    \fn Scene::getRrStopProbability()
    \brief Getter for the russian roulette stop probability.
    \details Russian roulette stop probability that will be used during the render.
    \sa Scene(), getRussianRoulette()

    \fn Scene::getNextEventEstimation()
    \brief Getter for the next event estimation.
    \details See my TM's report for further information on this algorithm.
    \return Whether the next event estimation algorithm will be used during the render.

    \fn Scene::getNumberThreads()
    \brief Getter for the number of CPU threads.
    \return The number of threads that will be used on the CPU during the render.

    \fn Scene::setObjectsGroups(std::vector<Object3DGroup> groups)
    \brief Setter for the objects groups.
    \param groups The new objects groups of this scene.

    \fn Scene::setCamera(PerspectiveCamera camera)
    \brief Setter for the camera.
    \param camera The new camera that will be used during the render.

    \fn Scene::setSamplePerPixel(unsigned int samplePerPixel)
    \brief Setter for the number of samples per pixel.
    \param samplePerPixel The new number of samples per pixel that will be used during the render.
    \sa Scene()

    \fn Scene::setMinBounces(unsigned int minBounces)
    \brief Setter for the minimum number of bounces.
    \param minBounces The new minimum number of bounces that will be used during the render.
    \sa Scene()

    \fn Scene::setMaxDepth(double maxDepth)
    \brief Setter for the maximum depth.
    \param maxDepth The new maximum depth that will be used during the render.
    \sa Scene()

    \fn Scene::setRussianRoulette(bool russianRoulette)
    \brief Setter for the russian roulette.
    \details See my TM's report for further information on this algorithm.
    \param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.

    \fn Scene::setRussianRoulette(bool russianRoulette, double rrStopProbability)
    \brief Setter for the russian roulette and russian roulette stop probability.
    \details See my TM's report for further information on this algorithm.
    \param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.
    \param rrStopProbability The new russian roulette stop probability that will be used during the render.
    \sa Scene().

    \fn Scene::setRrStopProbability(double rrStopProbability)
    \brief Setter for the russian roulette stop probability
    \details See my TM's report for further information on this algorithm.
    \param rrStopProbability The new russian roulette stop probability that will be used during the render.
    \sa Scene().

    \fn Scene::setNextEventEstimation(bool nextEventEstimation)
    \brief Setter for the next event estimation.
    \details See my TM's report for further information on this algorithm.
    \param nextEventEstimation Whether the next event estimation algorithm will be used during the render.

    \fn Scene::setNumberThreads(unsigned int numberThreads)
    \brief Setter for the number of CPU threads.
    \param numberThreads The new number of threads that will be used on the CPU during the render.

    \fn Scene::addObjectGroup(const Object3DGroup& group)
    \brief Adds an objects group to the current ones.
    \param group The objects group that will be added.

    \fn Scene::resetObjectGroups()
    \brief Destroys all the objects groups.

    \fn Scene::computeObjectsAndLamps()
    \brief Computes all the objects
    \details Also stores a vector of all objects having an emitance strictly greater than 1, to go faster with the next event estimation algorithm.

    \fn Scene::defaultScene()
    \brief Sets this scene's objects to default ones.
    \details The look is similar to the Cornell box.

    \fn Scene::importFBX(const char* filePath, Material* material, std::string name)
    \brief Imports a FBX file as triangles.
    \details Uses the FBX SDK library.
    \param filePath The path the FBX file.
    \param material The material that will be used for all the triangles which will be imported.
    \param name The name of the objects group in which all triangles will be stored.
    \return True if the importation was successful, false else.

    \fn Scene::render()
    \brief Start the render of the picture.
    \details This uses the path tracing algorithm (you could have read this project's title for this information) and some optimisations such as next event estimation and russian roulette path termination.
    \return A pointer to the rendered picture.

    \fn Scene::displayParametersPage(bool displayIndexes = true)
    \brief Prints the parameters page.
    \details This is one of the main pages.
    \param displayIndexes If true it will print the indexes before each parameter. This is useful if for the user to be able to change them, but you can remove them if you only want the information.
    \sa displayObjectsPage()

    \fn Scene::displayObjectsPage()
    \brief Prints the objects page.
    \details This is one of the main pages.
    \sa displayParametersPage()

    \fn displayRenderingProgression(unsigned int numberPixelXAlreadyComputed, unsigned int pictureWidth, double loopBeginningTime)
    \brief Prints the progression information
    \details This is used during the rendering.
    \param numberPixelXAlreadyComputed The *x* coordinate of the pixel we are currently treating.
    \param pictureWidth The width of the picture we are rendering.
    \param loopBeginningTime The number of seconds between 01/01/1970 and the beginning of the render.
    \sa render()
*/


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
    bool importFBX(const char* filePath, Material* material, std::string name);

    Picture* render();

    void displayParametersPage(bool displayIndexes = true) const;
    void displayObjectsPage() const;
};

void displayRenderingProgression(unsigned int numberPixelXAlreadyComputed, unsigned int pictureWidth, double loopBeginningTime);

#endif
