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
std::vector<Object3D*> lamps;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
constexpr double CAMERA_FOCAL_LENGTH = 3;
constexpr double CAMERA_FOV_X = M_PI_4;

DoubleVec3D picture [PICTURE_WIDTH][PICTURE_HEIGHT];

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MIN_BOUNCES = 5;  // Less if nothing is hit
constexpr unsigned int SAMPLE_PER_PIXEL = 8;

constexpr bool RUSSIAN_ROULETTE = true;
constexpr double RR_STOP_PROBABILITY = 0.1;

constexpr bool NEXT_EVENT_ESTIMATION = true;

constexpr double MIDDLE_GRAY = 100;

double randomDouble() {
	return unif(re);
}

double getCurrentTimeSeconds() {
	return (double)std::chrono::system_clock::now().time_since_epoch().count() / std::chrono::system_clock::period::den;
}

DoubleVec3D traceRay(const Ray& ray, double usedNextEventEstimation = false, unsigned int bounces = 0) {
	DoubleVec3D result(0.0);

	// Russian roulette
	double rrFactor = 1.0;
	if (bounces >= MIN_BOUNCES) {
		if (!RUSSIAN_ROULETTE || randomDouble() < RR_STOP_PROBABILITY)
			return result;
		rrFactor = 1.0/(1.0 - RR_STOP_PROBABILITY);
	}

	// Search for ray intersection
	double smallestPositiveDistance = MAX_DEPTH + 1;  // Has to be strictly positive -> we don't want it to intersect with same object
	Object3D* closestObject = nullptr;
	for (Object3D* object : scene) {
		double distance = object->closestIntersection(ray);
		if (distance > 0.00001 && distance < smallestPositiveDistance) {
			smallestPositiveDistance = distance;
			closestObject = object;
		}
	}

	if (smallestPositiveDistance > MAX_DEPTH)  // Something must be hit
		return result;

	// Rendering equation
	Material* objectMaterial = closestObject->getMaterial();
	DoubleVec3D intersection = ray.getOrigin() + smallestPositiveDistance*ray.getDirection();
	DoubleVec3D normal = closestObject->getNormal(intersection);

	if (NEXT_EVENT_ESTIMATION && objectMaterial->worksWithNextEventEstimation()) {
		for (Object3D* lamp : lamps) {
			DoubleVec3D intersectionToLamp = lamp->getRandomPoint(randomDouble) - intersection;
			if (dotProd(normal, intersectionToLamp) > 0) {
				double distanceLamp = length(intersectionToLamp);
				Ray shadowRay(intersection, intersectionToLamp);
				bool lampIsVisible(true);
				for (Object3D* object : scene) {
					if (object != lamp) {
						double distanceObject = object->closestIntersection(shadowRay);
						if (distanceObject > DBL_EPSILON && distanceObject < distanceLamp) {
							lampIsVisible = false;
							break;
						}
					}
				}
				if (lampIsVisible) {
					intersectionToLamp /= distanceLamp;  // Normalised
					result += rrFactor * objectMaterial->computeCurrentColour(lamp->getMaterial()->getEmittance(), dotProd(intersectionToLamp, normal)) / distanceLamp / distanceLamp / 4 / M_PI;
					// result += rrFactor * lamp->getMaterial()->getEmittance() / distanceLamp / distanceLamp * 0.1;
				}
			}
		}
	}
	if (!NEXT_EVENT_ESTIMATION || !usedNextEventEstimation)
		// If use the next event estimation, we don't want to add this emittance twice.
		result += rrFactor * DoubleVec3D(objectMaterial->getEmittance());

	DoubleVec3D newDirection = objectMaterial->getNewDirection(ray, normal, randomDouble);
	DoubleVec3D recursiveColour = traceRay(Ray(intersection, newDirection), NEXT_EVENT_ESTIMATION && objectMaterial->worksWithNextEventEstimation(), bounces + 1);
	result += rrFactor * objectMaterial->computeCurrentColour(recursiveColour, dotProd(newDirection, normal));

	return result;
}

int main() {
	double beginningTime = getCurrentTimeSeconds();

	// Make scene
	// Spheres
	scene.push_back(new Sphere(DoubleVec3D(0, -1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 10000)));
	scene.push_back(new Sphere(DoubleVec3D(0.2, 1.5, -3), 0.5, new RefractiveMaterial(1.5)));
	scene.push_back(new Sphere(DoubleVec3D(1.2, 1.5, -2.4), 0.5, new SpecularMaterial));
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

	// Store pointers of objects that emit light
	for (Object3D* object : scene)
		if (object->getMaterial()->getEmittance() > 0)
			lamps.push_back(object);


	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	// Print informations
	std::cout << "Width=" << PICTURE_WIDTH << "     Height=" << PICTURE_HEIGHT << "     Sample/Pixel=" << SAMPLE_PER_PIXEL << std::endl;
	std::cout << "RussianRoulette=" << (RUSSIAN_ROULETTE ? "true" : "false") << "     MinBounces=" << MIN_BOUNCES << "     RrStopProbability=" << RR_STOP_PROBABILITY << std::endl;
	std::cout << "NextEventEstimation=" << (NEXT_EVENT_ESTIMATION ? "true" : "false") << std::endl;
	std::cout << std::endl;

	// Trace rays
	double loopBeginTime = getCurrentTimeSeconds();
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		double timeAlreadySpent = getCurrentTimeSeconds() - loopBeginTime;
		std::cout << "\rProgress: " << (double)pixelX / PICTURE_WIDTH * 100 << "%     Time already spent: " << timeAlreadySpent << "s     Estimated time left: " << timeAlreadySpent*(PICTURE_WIDTH - pixelX)/pixelX << "s        ";
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
			// Very naive tone mapping
			file << (int)(255 * currentColour.getX() / (MIDDLE_GRAY+currentColour.getX())) << " ";
			file << (int)(255 * currentColour.getY() / (MIDDLE_GRAY+currentColour.getY())) << " ";
			file << (int)(255 * currentColour.getZ() / (MIDDLE_GRAY+currentColour.getZ())) << "\n";
		}
	}
	file.close();

	// Delete pointers
	for (Object3D* object : scene)
		delete object;

	// Measure time and make sound to warn that it is ended
	std::cout << "\nComputed in " << getCurrentTimeSeconds() - beginningTime << " seconds.\n";
	std::cout << "\a";

	return 0;
}
