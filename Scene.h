#ifndef DEF_SCENE
#define DEF_SCENE

#include <omp.h>

#include "DoubleMatrix33.h"
#include "KDTreeNode.h"
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

    \fn Scene::Scene(PerspectiveCamera camera = PerspectiveCamera(), unsigned int samplePerPixel = 8, unsigned int minBounces = 5)
    \brief Main constructor.
    \param camera The camera that will be used for the render.
    \param samplePerPixel The number of ray casted per pixel. Increasing it will give a higher quality, but at a cost of a linearly increasing time.
    \param minBounces The minimum number of bounces that each ray will do. It can be less if the ray does not intersect with any object.

    \fn Scene::Scene(const Scene& scene)
    \brief Copy constructor.
    \param scene The scene that will be copied.

    \fn std::vector<Object3DGroup> Scene::getObjectsGroups()
    \brief Getter for the objects groups.
    \return This scene's objects groups.

    \fn std::vector<Object3DGroup>& Scene::getObjectsGroupsReference()
    \brief Getter for a reference to the objects groups.
    \return A reference to this scene's objects groups.

    \fn std::vector<Object3D*> Scene::getObjects()
    \brief Getter for the objects.
    \details Calls computeObjectsAndLamps().
    \return This scene's objects.
    \sa split()

    \fn std::vector<Object3D*> Scene::getLamps()
    \brief Getter for the lamps.
    \details Calls computeObjectsAndLamps().
    \return This scene's objects that have an emittance strictly greater than 0.
    \sa getObjects()

    \fn PerspectiveCamera Scene::getCamera()
    \brief Getter for the camera.
    \return This scene's camera.

    \fn PerspectiveCamera& Scene::getCameraReference()
    \brief Getter for a reference to the camera.
    \return A reference to this scene's camera.

    \fn unsigned int Scene::getSamplePerPixel()
    \brief Getter for the number of samples per pixel.
    \return The number of samples per pixel that will be used during the render.
    \sa Scene()

    \fn unsigned int Scene::getMinBounces()
    \brief Getter for the minimum number of bounces.
    \return The minimum number of bounces that will be used during the render.
    \sa Scene()

    \fn bool Scene::getRussianRoulette()
    \brief Getter for the russian roulette.
    \details See my TM's report for further information on this algorithm.
    \return Whether the russian roulette path termination algorithm will be used during the render.
    \sa getRrStopProbability()

    \fn double Scene::getRrStopProbability()
    \brief Getter for the russian roulette stop probability.
    \details Russian roulette stop probability that will be used during the render.
    \return The russian roulette stop probability.
    \sa Scene(), getRussianRoulette()

    \fn bool Scene::getNextEventEstimation()
    \brief Getter for the next event estimation.
    \details See my TM's report for further information on this algorithm.
    \return Whether the next event estimation algorithm will be used during the render.

    \fn unsigned int Scene::getNumberThreads()
    \brief Getter for the number of CPU threads.
    \return The number of threads that will be used on the CPU during the render.

    \fn bool Scene::getKDTree()
    \brief Getter for the k-d tree.
    \details See my TM's report for further information on this data structure. 
    \return Whether a k-d tree will be used during the render.
    \sa Scene::getKDMaxObjectNumber(), Scene::getKDMaxDepth()

    \fn unsigned int Scene::getKDMaxObjectNumber()
    \brief Getter for the maximum number of objects in a k-d tree leaf.
    \details One of the two recursion stop conditions, along with Scene::getKDMaxDepth(). If one of them is fulfilled, the k-d tree recursive creation stops. See my TM's report for further information on this data structure.
    \return The maximum number of objects in a k-d tree leaf.
    \sa Scene::getKDTree(), Scene::getKDMaxDepth()
    
    \fn unsigned int Scene::getKDMaxDepth()
    \brief Getter for the maximum depth recursion of the k-d tree.
    \details One of the two recursion stop conditions, along with Scene::getKDMaxObjectNumber(). If one of them is fulfilled, the k-d tree recursive creation stops. See my TM's report for further information on this data structure.
    \return The maximum number of recursive steps of the k-d tree.
    \sa Scene::getKDTree(), Scene::getKDMaxObjectNumber()

    \fn void Scene::setObjectsGroups(std::vector<Object3DGroup> groups)
    \brief Setter for the objects groups.
    \param groups The new objects groups of this scene.

    \fn void Scene::setCamera(PerspectiveCamera camera)
    \brief Setter for the camera.
    \param camera The new camera that will be used during the render.

    \fn void Scene::setSamplePerPixel(unsigned int samplePerPixel)
    \brief Setter for the number of samples per pixel.
    \param samplePerPixel The new number of samples per pixel that will be used during the render.
    \sa Scene()

    \fn void Scene::setMinBounces(unsigned int minBounces)
    \brief Setter for the minimum number of bounces.
    \param minBounces The new minimum number of bounces that will be used during the render.
    \sa Scene()

    \fn void Scene::setRussianRoulette(bool russianRoulette)
    \brief Setter for the russian roulette.
    \details See my TM's report for further information on this algorithm.
    \param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.

    \fn void Scene::setRussianRoulette(bool russianRoulette, double rrStopProbability)
    \brief Setter for the russian roulette and russian roulette stop probability.
    \details See my TM's report for further information on this algorithm.
    \param russianRoulette Whether the russian roulette path termination algorithm will be used during the render.
    \param rrStopProbability The new russian roulette stop probability that will be used during the render.
    \sa Scene().

    \fn void Scene::setRrStopProbability(double rrStopProbability)
    \brief Setter for the russian roulette stop probability
    \details See my TM's report for further information on this algorithm.
    \param rrStopProbability The new russian roulette stop probability that will be used during the render.
    \sa Scene().

    \fn void Scene::setNextEventEstimation(bool nextEventEstimation)
    \brief Setter for the next event estimation.
    \details See my TM's report for further information on this algorithm.
    \param nextEventEstimation Whether the next event estimation algorithm will be used during the render.

    \fn void Scene::setNumberThreads(unsigned int numberThreads)
    \brief Setter for the number of CPU threads.
    \param numberThreads The new number of threads that will be used on the CPU during the render.

    \fn void Scene::setKDTree(bool kdTree)
    \brief Setter for the k-d tree.
    \details See my TM's report for further information on this data structure.
    \param kdTree Whether a k-d tree will be used during the render.
    \sa Scene::setKDMaxObjectNumber(unsigned int kdMaxObjectNumber), Scene::setKDMaxDepth(unsigned int kdMaxDepth)

    \fn void Scene::setKDMaxObjectNumber(unsigned int kdMaxObjectNumber)
    \brief Setter for the maximum number of objects in a k-d tree leaf. 
    \details One of the two recursion stop conditions, along with Scene::setKDMaxDepth(). If one of them is fulfilled, the k-d tree recursive creation stops. See my TM's report for further information on this data structure.
    \param kdMaxObjectNumber The new maximum number of objects in a k-d tree leaf.
    \sa Scene::setKDTree(bool kdTree), Scene::setKDMaxDepth(unsigned int kdMaxDepth)

    \fn void Scene::setKDMaxDepth(unsigned int kdMaxDepth)
    \brief Setter for the maximum depth recursion of the k-d tree.
    \details One of the two recursion stop conditions, along with Scene::setKDMaxObjectNumber(). If one of them is fulfilled, the k-d tree recursive creation stops. See my TM's report for further information on this data structure.
    \param kdMaxDepth The new maximum number of recursive steps of the k-d tree.
    \sa Scene::setKDTree(bool kdTree), Scene::setKDMaxObjectNumber(unsigned int kdMaxObjectNumber)

    \fn void Scene::addObjectGroup(const Object3DGroup& group)
    \brief Adds an objects group to the current ones.
    \param group The objects group that will be added.

    \fn void Scene::resetObjectGroups()
    \brief Destroys all the objects groups.

    \fn void Scene::computeObjectsAndLamps()
    \brief Computes all the objects
    \details Also stores a vector of all objects having an emitance strictly greater than 1, to go faster with the next event estimation algorithm.

    \fn void Scene::defaultScene()
    \brief Sets this scene's objects to default ones.
    \details The look is similar to the Cornell box.

    \fn bool Scene::importFBX(const char* filePath, Material* material, std::string name)
    \brief Imports a FBX file as triangles.
    \details Uses the FBX SDK library.
    \param filePath The path the FBX file.
    \param material The material that will be used for all the triangles which will be imported.
    \param name The name of the objects group in which all triangles will be stored.
    \return True if the importation was successful, false else.

    \fn Picture* Scene::render()
    \brief Start the render of the picture.
    \details This uses the path tracing algorithm (you could have read this project's title for this information) and some optimisations such as next event estimation and russian roulette path termination.
    \return A pointer to the rendered picture.

    \fn void Scene::displayParametersPage(bool displayIndexes = true)
    \brief Prints the parameters page.
    \details This is one of the main pages.
    \param displayIndexes If true it will print the indexes before each parameter. This is useful if for the user to be able to change them, but you can remove them if you only want the information.
    \sa displayObjectsPage()

    \fn void Scene::displayObjectsPage()
    \brief Prints the objects page.
    \details This is one of the main pages.
    \sa displayParametersPage()

    \fn void displayRenderingProgression(unsigned int numberPixelXAlreadyComputed, unsigned int pictureWidth, double loopBeginningTime)
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
    KDTreeNode* kdTreeRoot = nullptr;

    PerspectiveCamera camera = PerspectiveCamera();
    unsigned int samplePerPixel = 8;
    unsigned int minBounces = 10;

    bool russianRoulette = true;
    double rrStopProbability = 0.1;  // Linked to russianRoulette   /  stopProb=1 <=> russianRoulette=false
    bool nextEventEstimation = true;
    unsigned int numberThreads = 8;
    bool kdTree = true;
    unsigned int kdMaxObjectNumber = 10;
    unsigned int kdMaxDepth = 10;

    KDTreeNode::Intersection bruteForceIntersection(const Ray& ray) const;
    DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, const KDTreeNode* lastNode = nullptr, unsigned int bounces = 0) const;
    std::string getCurrentIndex(int currentIndex, bool displayIndex) const;

public:
    Scene(PerspectiveCamera camera = PerspectiveCamera(), unsigned int samplePerPixel = 8, unsigned int minBounces = 5);
    Scene(const Scene& scene);

    std::vector<Object3DGroup> getObjectsGroups() const;
    std::vector<Object3DGroup>& getObjectsGroupsReference();  // Reference -> can modify it -> != const
    std::vector<Object3D*> getObjects();
    std::vector<Object3D*> getLamps();
    PerspectiveCamera getCamera() const;
    PerspectiveCamera& getCameraReference();
    unsigned int getSamplePerPixel() const;
    unsigned int getMinBounces() const;
    bool getRussianRoulette() const;
    double getRrStopProbability() const;
    bool getNextEventEstimation() const;
    unsigned int getNumberThreads() const;
    bool getKDTree() const;
    unsigned int getKDMaxObjectNumber() const;
    unsigned int getKDMaxDepth() const;

    void setObjectsGroups(std::vector<Object3DGroup> groups);
    void setCamera(PerspectiveCamera camera);
    void setSamplePerPixel(unsigned int samplePerPixel);
    void setMinBounces(unsigned int minBounces);
    void setRussianRoulette(bool russianRoulette);
    void setRussianRoulette(bool russianRoulette, double rrStopProbability);
    void setRrStopProbability(double rrStopProbability);
    void setNextEventEstimation(bool nextEventEstimation);
    void setNumberThreads(unsigned int numberThreads);
    void setKDTree(bool kdTree);
    void setKDMaxObjectNumber(unsigned int kdMaxObjectNumber);
    void setKDMaxDepth(unsigned int kdMaxDepth);

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
