#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "Ray.h"
#include "RefractiveMaterial.h"
#include "SpecularMaterial.h"
#include "Sphere.h"
#include "Triangle.h"


// for random
std::uniform_real_distribution<double> unif(0, 1);
std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());  // new seed each time

std::vector<Object3D*> scene;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
constexpr double CAMERA_FOCAL_LENGTH = 3;
constexpr double CAMERA_FOV_X = M_PI_4;

DoubleVec3D picture [PICTURE_WIDTH][PICTURE_HEIGHT];

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MIN_BOUNCES = 5;  // Less if hits nothing
constexpr unsigned int SAMPLE_PER_PIXEL = 64;

constexpr bool RUSSIAN_ROULETTE = true;
constexpr double RR_STOP_PROBABILITY = 0.1;

double randomDouble() {
	return unif(re);
}

DoubleVec3D traceRay(const Ray& ray, unsigned int bounces = 0) {
	DoubleVec3D result(0.0);
	double rrFactor = 1.0;
	if (bounces >= MIN_BOUNCES) {
		if (!RUSSIAN_ROULETTE || randomDouble() < RR_STOP_PROBABILITY)
			return result;
		rrFactor = 1.0/(1.0 - RR_STOP_PROBABILITY);
	}

	double smallestPositiveDistance = MAX_DEPTH + 1;  // Has to be strictly positive -> we don't want it to intersect with same object
	Object3D* closestObject = nullptr;
	for (Object3D* object : scene) {
		double distance = object->closestIntersection(ray);
		if (distance > DBL_EPSILON && distance < smallestPositiveDistance) {
			smallestPositiveDistance = distance;
			closestObject = object;
		}
	}

	if (smallestPositiveDistance > MAX_DEPTH)  // Something must be hit
		return result;

	Material* objectMaterial = closestObject->getMaterial();
	DoubleVec3D intersection = ray.getOrigin() + smallestPositiveDistance*ray.getDirection();
	DoubleVec3D normal = closestObject->getNormal(intersection);

	result += rrFactor * DoubleVec3D(objectMaterial->getEmittance());
	DoubleVec3D newDirection = objectMaterial->getNewDirection(ray, normal, &randomDouble);
	DoubleVec3D recursiveColour = traceRay(Ray(intersection, newDirection), bounces + 1);
	result += rrFactor * objectMaterial->computeCurrentColour(recursiveColour, dotProd(newDirection, normal));

	return result;
}

int main() {
	long long beginningTime = std::chrono::system_clock::now().time_since_epoch().count();

	// Make scene
	// Spheres
	scene.push_back(new Sphere(DoubleVec3D(0, -1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 10000)));
	scene.push_back(new Sphere(DoubleVec3D(0.2, 1.5, -3), 0.5, new RefractiveMaterial(DoubleVec3D(0), 1.5)));
	scene.push_back(new Sphere(DoubleVec3D(1.2, 1.5, -2.4), 0.5, new SpecularMaterial(DoubleVec3D(0))));
	scene.push_back(new Sphere(DoubleVec3D(-1, 1.5, -2.3), 0.5, new DiffuseMaterial(DoubleVec3D(6))));
	// left
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, 1), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(2, 2, 10))));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, -4), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(2, 2, 10))));
	// right
	scene.push_back(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(2, -2, 1), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(10, 2, 2))));
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(2, -2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(10, 2, 2))));
	// Top
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(3))));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(3))));
	// Bottom
	scene.push_back(new Triangle(DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(3))));
	scene.push_back(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, 1), new DiffuseMaterial(DoubleVec3D(3))));
	// Background
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, 2, -4), new DiffuseMaterial(DoubleVec3D(2, 10, 2))));
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, -2, -4), new DiffuseMaterial(DoubleVec3D(2, 10, 2))));
	// Behind camera
	scene.push_back(new Triangle(DoubleVec3D(2, 2, 1), DoubleVec3D(2, -2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(6))));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(6))));
	
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOCAL_LENGTH, CAMERA_FOV_X);

	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	// Print informations
	std::cout << "Width=" << PICTURE_WIDTH << "   Height=" << PICTURE_HEIGHT << "   Sample/Pixel=" << SAMPLE_PER_PIXEL << std::endl;
	std::cout << "RussianRoulette=" << (RUSSIAN_ROULETTE ? "true" : "false") << "   MinBounces=" << MIN_BOUNCES << "   RrStopProbability=" << RR_STOP_PROBABILITY << std::endl;
	std::cout << std::endl;

	// Trace rays
	double loopBeginTime = std::chrono::system_clock::now().time_since_epoch().count();
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		std::cout << "\rProgress: " << (double)pixelX / PICTURE_WIDTH * 100 << "%   Estimated time left: " << (loopBeginTime < 0 ? 0 : (double)(std::chrono::system_clock::now().time_since_epoch().count() - loopBeginTime)*(PICTURE_WIDTH - pixelX)/pixelX/std::chrono::system_clock::period::den) << " seconds       ";
		for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
			// std::cout << "\r" << (double)(pixelX*PICTURE_WIDTH + pixelY) / (PICTURE_WIDTH*PICTURE_HEIGHT) * 100 << "%";
			for (unsigned int samples = 0; samples < SAMPLE_PER_PIXEL; samples++) {
				Ray currentRay = camera.getRayGoingThrough(pixelX + randomDouble() - 0.5, pixelY + randomDouble() - 0.5);
				picture[pixelX][pixelY] += traceRay(currentRay)/SAMPLE_PER_PIXEL;
			}
		}
	}

	// Write picture
	std::ofstream file;
	file.open("picture.ppm");
	file << "P3\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n" << "255\n";
	for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
		for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
			DoubleVec3D currentColour = picture[pixelX][pixelY];
			file << std::min(255, (int)currentColour.getX()) << " ";
			file << std::min(255, (int)currentColour.getY()) << " ";
			file << std::min(255, (int)currentColour.getZ()) << "\n";
		}
	}
	file.close();

	// Delete pointers
	for (Object3D* object : scene)
		delete object;

	// Measure time
	long long endingTime = std::chrono::system_clock::now().time_since_epoch().count();
	std::cout << "\nComputed in " << (double)(endingTime - beginningTime) / std::chrono::system_clock::period::den << " seconds.\n";

	return 0;
}
