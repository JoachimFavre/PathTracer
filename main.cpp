#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "Object3D.h"
#include "Sphere.h"
#include "TrianglePlane.h"
#include "PerspectiveCamera.h"
#include "Ray.h"
#include "DoubleVec3.h"
#include "Material.h"

std::vector<Object3D*> scene;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
DoubleVec3 picture [PICTURE_HEIGHT][PICTURE_WIDTH];
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MAX_BOUNCES = 5;
constexpr unsigned int SAMPLE_PER_PIXEL = 8;

DoubleVec3 traceRay(const Ray& ray, DoubleVec3 colour = DoubleVec3(0), unsigned int bounces = 0) {
	double smallestPositiveDistance = MAX_DEPTH + 1;  // Strictly positive -> we don't want it to intersect with same object
	Object3D* closestObject = nullptr;
	for (Object3D* object : scene) {
		double distance = object->closestIntersection(ray);
		if (distance > DBL_EPSILON && distance < smallestPositiveDistance) {
			smallestPositiveDistance = distance;
			closestObject = object;
		}
	}
	if (smallestPositiveDistance < MAX_DEPTH) {
		Material ObjectMaterial = closestObject->getMaterial();
		colour += DoubleVec3(ObjectMaterial.getEmittance());
		// To implement : BRDF and recursion
		return colour;
	}
	else  // did not hit anything
		return colour;
}

int main() {
	scene.push_back(new Sphere(DoubleVec3(0, 0, -5), 1, Material(DoubleVec3(5), BRDF::Diffuse, 200)));
	//scene.push_back(new TrianglePlane(DoubleVec3(1, 1, -5), DoubleVec3(1, 0, -5), DoubleVec3(0, 1, -5), Material(DoubleVec3(5), BRDF::Diffuse, 1000)));

	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOV_X);

	// Trace
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
			for (unsigned int samples = 0; samples < SAMPLE_PER_PIXEL; samples++) {
				Ray currentRay = camera.getRayGoingThrough(pixelX, pixelY);
				picture[pixelY][pixelX] += traceRay(currentRay)/SAMPLE_PER_PIXEL;
			}
		}
	}

	// Write
	std::ofstream file;
	file.open("picture.ppm");
	file << "P3\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n" << "255\n";
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
			DoubleVec3 currentColour = picture[pixelY][pixelX];
			file << std::min(255, (int)currentColour.getX()) << " ";
			file << std::min(255, (int)currentColour.getY()) << " ";
			file << std::min(255, (int)currentColour.getZ()) << "\n";
		}
	}
	file.close();

	return 0;
}
