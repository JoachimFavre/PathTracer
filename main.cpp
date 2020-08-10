#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>
#include <omp.h>

#include "DiffuseMaterial.h"
#include "DoubleMatrix33.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "RefractiveMaterial.h"
#include "Scene.h"
#include "SpecularMaterial.h"
#include "Sphere.h"
#include "Triangle.h"


#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include <fbxsdk/utils/fbxgeometryconverter.h>


constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
constexpr double CAMERA_FOCAL_LENGTH = 3;
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr unsigned int NUMBER_THREADS = 8;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MIN_BOUNCES = 5;  // Less if nothing is hit
constexpr unsigned int SAMPLE_PER_PIXEL = 8;

constexpr bool RUSSIAN_ROULETTE = false;
constexpr double RR_STOP_PROBABILITY = 0.1;

constexpr bool NEXT_EVENT_ESTIMATION = true;

constexpr double MIDDLE_GRAY = 100;

const char* FILE_PATH = "_mesh.fbx";

inline double deg2rad(double degrees) {
	return degrees * M_PI/180;
}


int main() {
	double beginningTime = getCurrentTimeSeconds();
	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	// Instantiate camera and scene
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOCAL_LENGTH, CAMERA_FOV_X);
	Scene scene(camera, SAMPLE_PER_PIXEL, MIN_BOUNCES, MAX_DEPTH, RR_STOP_PROBABILITY);
	scene.setRussianRoulette(RUSSIAN_ROULETTE);
	scene.setNextEventEstimation(NEXT_EVENT_ESTIMATION);
	scene.setNumberThreads(NUMBER_THREADS);

	// Open File
	std::cout << "Opening file " << FILE_PATH << std::endl;
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	FbxManager* sdkManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(sdkManager, "");

	bool importStatus = importer->Initialize(FILE_PATH, -1, sdkManager->GetIOSettings());

	if (!importStatus) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", importer->GetStatus().GetErrorString());
		exit(-1);
	}

	FbxScene* fbxScene = FbxScene::Create(sdkManager, "myScene");
	importer->Import(fbxScene);
	importer->Destroy();
	
	FbxGeometryConverter clsConverter(sdkManager);
	bool triangulisationStatus = clsConverter.Triangulate(fbxScene, true);
	if (!triangulisationStatus) {
		std::cout << "Triangulisation could not be fully done" << std::endl;
		exit(-1);
	}

	FbxNode* rootNode = fbxScene->GetRootNode();

	for (int childNumber = 0; childNumber < rootNode->GetChildCount(); childNumber++) {
		FbxNode* child = rootNode->GetChild(childNumber);

		FbxAMatrix& childGlobalTransform = child->EvaluateGlobalTransform();
		DoubleVec3D translation = childGlobalTransform.GetT();
		DoubleVec3D rotation = childGlobalTransform.GetR();
		// DoubleVec3D scaling = childGlobalTransform.GetS();

		DoubleMatrix33 rotationMatrix = getRotationMatrixXYZ(rotation);

		FbxMesh* mesh = child->GetMesh();
		if (mesh != nullptr) {
			FbxVector4* controlPoints = mesh->GetControlPoints();
			for (int polygonIx = 0; polygonIx < mesh->GetPolygonCount(); polygonIx++) {
				if (mesh->GetPolygonSize(polygonIx) != 3) {
					std::cout << "This polygon is not a triangle";
					exit(-1);
				}

				DoubleVec3D vertex0 = rotationMatrix*controlPoints[mesh->GetPolygonVertex(polygonIx, 0)] + translation;
				DoubleVec3D vertex1 = rotationMatrix*controlPoints[mesh->GetPolygonVertex(polygonIx, 1)] + translation;
				DoubleVec3D vertex2 = rotationMatrix*controlPoints[mesh->GetPolygonVertex(polygonIx, 2)] + translation;
				
				//std::cout << vertex0 << " " << vertex1 << " " << vertex2 << std::endl;

				Triangle* triangle = new Triangle(vertex0, vertex1, vertex2, new DiffuseMaterial(0.8));
				// Verify normals ?

				scene.addObject(triangle);
			}
		}
	}


	scene.addObject(new Sphere(DoubleVec3D(0, 1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 4000)));

	/*
	// Make scene
	// Spheres
	scene.addObject(new Sphere(DoubleVec3D(0, 1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 4000)));
	scene.addObject(new Sphere(DoubleVec3D(0.2, -1.5, -3), 0.5, new RefractiveMaterial(1.5)));
	scene.addObject(new Sphere(DoubleVec3D(1.2, -1.5, -2.4), 0.5, new SpecularMaterial));
	scene.addObject(new Sphere(DoubleVec3D(-1, -1.5, -2.3), 0.5, new DiffuseMaterial(DoubleVec3D(0.5))));
	// left
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, 1), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(0.2, 0.2, 1))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, -4), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(0.2, 0.2, 1))));
	// right
	scene.addObject(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(2, -2, 1), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(1, 0.2, 0.2))));
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(2, -2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(1, 0.2, 0.2))));
	// Top
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(0.3))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(0.3))));
	// Bottom
	scene.addObject(new Triangle(DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(0.3))));
	scene.addObject(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, 1), new DiffuseMaterial(DoubleVec3D(0.3))));
	// Background
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, 2, -4), new DiffuseMaterial(DoubleVec3D(0.2, 1, 0.2))));
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, -2, -4), new DiffuseMaterial(DoubleVec3D(0.2, 1, 0.2))));
	// Behind camera
	scene.addObject(new Triangle(DoubleVec3D(2, 2, 1), DoubleVec3D(2, -2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(0.3))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(0.3))));
	*/
	

	// Render and write picture
	scene.render()->writeToFile(MIDDLE_GRAY);

	// Measure time and make sound to warn that it is ended
	std::cout << std::endl << "Computed in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl;
	std::cout << "\a";
	return 0;
}
