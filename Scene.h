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
    \brief Stores object groups and a camera for the render.

    \fn Scene::Scene(PerspectiveCamera camera = PerspectiveCamera(), unsigned int samplesPerPixel = 8, unsigned int minBounces = 5)
    \brief Main constructor.
    \param camera The camera that will be used for the render.
    \param samplesPerPixel The number of ray casted per pixel. Increasing it will give a higher quality, but at a cost of a linearly increasing time.
    \param minBounces The minimum number of bounces that each ray will do. It can be less if the ray does not intersect with any object.

    \fn Scene::Scene(const Scene& scene)
    \brief Copy constructor.
    \param scene The scene that will be copied.

    \fn std::vector<Object3DGroup> Scene::getObjectGroups()
    \brief Getter for the object groups.
    \return This scene's object groups.

    \fn std::vector<Object3DGroup>& Scene::getObjectGroupsReference()
    \brief Getter for a reference to the object groups.
    \return A reference to this scene's object groups.

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

    \fn unsigned int Scene::getSamplesPerPixel()
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
    \brief Getter for the k-d tree option.
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

    \fn std::string Scene::getBackupFileName() const
    \brief Getter for the name of the file in which backups will be made.
    \details Every backup will be done with the same file name, but using a different file extension.
    \return The name of the file in which backups will be made.

    \fn bool Scene::getBackupParameters() const
    \brief Getter for the option to backup the parameters.
    \return Whether the parameters will be backed up before the render.

    \fn bool Scene::getBackupObjectGroups() const
    \brief Getter for the option to backup the object groups.
    \return Whether the object groups will be backed up before the render.

    \fn bool Scene::getBackupPicture() const
    \brief Getter for the option to backup the picture.
    \return Whether the picture will be backed up after the render.
    \sa Scene::getLeastRenderTime4PictureBackup()

    \fn double Scene::getLeastRenderTime4PictureBackup() const
    \brief Getter for the least render time after which the picture is backed up.
    \details If this value is set to 0.0, the picture will always be backed up after the render.
    \return The least render time after which the picture is backed up.
    \sa Scene::getBackupPicture()

    \fn void Scene::setObjectGroups(std::vector<Object3DGroup> groups)
    \brief Setter for the object groups.
    \param groups The new object groups of this scene.

    \fn void Scene::setCamera(PerspectiveCamera camera)
    \brief Setter for the camera.
    \param camera The new camera that will be used during the render.

    \fn void Scene::setSamplesPerPixel(unsigned int samplesPerPixel)
    \brief Setter for the number of samples per pixel.
    \param samplesPerPixel The new number of samples per pixel that will be used during the render.
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

    \fn void Scene::setBackupFileName(std::string backupFileName);
    \brief Setter for the new name of the file in which backups will be made.
    \details Every backup will be done with the same file name, but using a different file extension.
    \param backupFileName The name of the file in which backups will be made.

    \fn void Scene::setBackupParameters(bool backupParameters);
    \brief Setter for the option to backup the parameters.
    \param backupParameters Whether the parameters will be backed up before the render.

    \fn void Scene::setBackupObjectGroups(bool backupObjectGroups);
    \brief Setter for the option to backup the object groups.
    \param backupObjectGroups Whether the object groups will be backed up before the render.

    \fn void Scene::setBackupPicture(bool backupPicture);
    \brief Setter for the option to backup the picture.
    \param backupPicture Whether the picture will be backed up after the render.
    \sa Scene::setLeastRenderTime4PictureBackup()

    \fn void Scene::setLeastRenderTime4PictureBackup(double leastRenderTime4PictureBackup);
    \brief Setter for the least render time after which the picture is backed up.
    \details If this value is set to 0.0, the picture will always be backed up after the render.
    \param leastRenderTime4PictureBackup The new least render time after which the picture is backed up.
    \sa Scene::setBackupPicture()

    \fn void Scene::addObjectGroup(const Object3DGroup& group)
    \brief Adds an object group to the current ones.
    \param group The object group that will be added.

    \fn void Scene::resetAndDeleteObjectGroups()
    \brief Deletes all object groups and their objects.
    \sa Object3DGroup::resetAndDeleteObjects()

    \fn void Scene::computeObjectsAndLamps()
    \brief Computes all the objects
    \details Also stores a vector of all objects having an emitance strictly greater than 1, to go faster with the next event estimation algorithm.

    \fn void Scene::defaultScene()
    \brief Sets this scene's objects to default ones.
    \details The look is similar to the Cornell box.

    \fn void Scene::saveParameters2File(std::string fileName) const
    \brief Saves parameters to a file.
    \param fileName The name of the file to which the prameters will be saved. It is recommended that this file extension ends with PARAMETERS_SAVE_EXTENSION.
    \sa formatFileName()

    \fn void Scene::saveObjectGroups2File(std::string fileName) const
    \brief Saves object groups to a file.
    \param fileName The name of the file to which the object groups will be saved. It is recommended that this file extension ends with OBJECTS_SAVE_EXTENSION.
    \sa formatFileName()

    \fn bool Scene::importFBXFile(const char* filePath, Material* material, std::string name)
    \brief Imports a fbx file as triangles.
    \details Uses the FBX SDK library.
    \param filePath The path to the fbx file.
    \param material The material that will be used for all the triangles which will be imported.
    \param name The name of the object group in which all triangles will be stored.
    \return True if the importation was successful, false else.
    \sa importTrianglesFromFbxNode()

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

    \fn bool importTrianglesFromFbxNode(FbxNode* node, Material* material, std::vector<Object3D*>& objects)
    \brief Imports recursively all triangles present in a FBXNode.
    \param node The node from which we want to import the mesh.
    \param material The material with which the triangles will be instanciated.
    \param objects A reference to a vector of objects in which the triangles will be added.
    \sa Scene::importFBXFile()

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
    std::vector<Object3DGroup> objectGroups;
    std::vector<Object3D*> objects;
    std::vector<Object3D*> lamps;
    KDTreeNode* kdTreeRoot = nullptr;

    PerspectiveCamera camera = PerspectiveCamera();
    unsigned int samplesPerPixel = 8;
    unsigned int minBounces = 10;

    bool russianRoulette = true;
    double rrStopProbability = 0.1;  // Linked to russianRoulette   /  stopProb=1 <=> russianRoulette=false
    bool nextEventEstimation = true;
    unsigned int numberThreads = omp_get_max_threads();
    bool kdTree = true;
    unsigned int kdMaxObjectNumber = 10;
    unsigned int kdMaxDepth = 10;

    std::string backupFileName = "backup";
    bool backupParameters = true;
    bool backupObjectGroups = true;
    bool backupPicture = true;
    double leastRenderTime4PictureBackup = 180.0;  // Three minutes

    KDTreeNode::Intersection bruteForceIntersection(const Ray& ray) const;
    DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, const KDTreeNode* lastNode = nullptr, unsigned int bounces = 0) const;
    std::string getCurrentIndex(int currentIndex, bool displayIndex) const;

public:
    Scene(PerspectiveCamera camera = PerspectiveCamera(), unsigned int samplesPerPixel = 8, unsigned int minBounces = 5);
    Scene(const Scene& scene);

    std::vector<Object3DGroup> getObjectGroups() const;
    std::vector<Object3DGroup>& getObjectGroupsReference();  // Reference -> can modify it -> != const
    std::vector<Object3D*> getObjects();
    std::vector<Object3D*> getLamps();
    PerspectiveCamera getCamera() const;
    PerspectiveCamera& getCameraReference();
    unsigned int getSamplesPerPixel() const;
    unsigned int getMinBounces() const;
    bool getRussianRoulette() const;
    double getRrStopProbability() const;
    bool getNextEventEstimation() const;
    unsigned int getNumberThreads() const;
    bool getKDTree() const;
    unsigned int getKDMaxObjectNumber() const;
    unsigned int getKDMaxDepth() const;
    std::string getBackupFileName() const;
    bool getBackupParameters() const;
    bool getBackupObjectGroups() const;
    bool getBackupPicture() const;
    double getLeastRenderTime4PictureBackup() const;

    void setObjectGroups(std::vector<Object3DGroup> groups);
    void setCamera(PerspectiveCamera camera);
    void setSamplesPerPixel(unsigned int samplesPerPixel);
    void setMinBounces(unsigned int minBounces);
    void setRussianRoulette(bool russianRoulette);
    void setRussianRoulette(bool russianRoulette, double rrStopProbability);
    void setRrStopProbability(double rrStopProbability);
    void setNextEventEstimation(bool nextEventEstimation);
    void setNumberThreads(unsigned int numberThreads);
    void setKDTree(bool kdTree);
    void setKDMaxObjectNumber(unsigned int kdMaxObjectNumber);
    void setKDMaxDepth(unsigned int kdMaxDepth);
    void setBackupFileName(std::string backupFileName);
    void setBackupParameters(bool backupParameters);
    void setBackupObjectGroups(bool backupObjectGroups);
    void setBackupPicture(bool backupPicture);
    void setLeastRenderTime4PictureBackup(double leastRenderTime4PictureBackup);

    void addObjectGroup(const Object3DGroup& group);
    void resetAndDeleteObjectGroups();
    void computeObjectsAndLamps();
    void defaultScene();

    void saveParameters2File(std::string fileName) const;
    void saveObjectGroups2File(std::string fileName) const;

    bool importFBXFile(const char* filePath, Material* material, std::string name);

    Picture* render();

    void displayParametersPage(bool displayIndexes = true) const;
    void displayObjectsPage() const;
};

bool importTrianglesFromFbxNode(FbxNode* node, Material* material, std::vector<Object3D*>& objects);

void displayRenderingProgression(unsigned int numberPixelXAlreadyComputed, unsigned int pictureWidth, double loopBeginningTime);

#endif
