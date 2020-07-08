#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "Object3D.h"
#include "Sphere.h"
#include "Triangle.h"
#include "PerspectiveCamera.h"
#include "Ray.h"
#include "DoubleVec3D.h"
#include "Material.h"
#include "BRDF.h"

std::uniform_real_distribution<double> unif(0, 1);
std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());  // new seed each time

std::vector<Object3D*> scene;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
DoubleVec3D picture [PICTURE_WIDTH][PICTURE_HEIGHT];
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MAX_BOUNCES = 5;
constexpr unsigned int SAMPLE_PER_PIXEL = 64;

double randomDouble() {
	return unif(re);
}

DoubleVec3D traceRay(const Ray& ray, unsigned int bounces = 0) {
	DoubleVec3D result(0.0);
	if (bounces < MAX_BOUNCES) {
		double smallestPositiveDistance = MAX_DEPTH + 1;  // Has to be strictly positive -> we don't want it to intersect with same object
		Object3D* closestObject = nullptr;
		for (Object3D* object : scene) {
			double distance = object->closestIntersection(ray);
			if (distance > DBL_EPSILON && distance < smallestPositiveDistance) {
				smallestPositiveDistance = distance;
				closestObject = object;
			}
		}

		if (smallestPositiveDistance < MAX_DEPTH) {
			DoubleVec3D currentRayDirection = ray.getDirection();
			Material objectMaterial = closestObject->getMaterial();
			DoubleVec3D objectColour = objectMaterial.getColour();

			DoubleVec3D intersection = ray.getOrigin() + smallestPositiveDistance*currentRayDirection;
			DoubleVec3D normal = closestObject->getNormal(intersection);

			result += DoubleVec3D(objectMaterial.getEmittance());

			switch (objectMaterial.getBRDF()) {
			// Diffuse BRDF
			case BRDF::Diffuse:
			{ // Needed to get out of switch scope
				// Generate vector on hemisphere
				double theta = M_PI*(randomDouble() - 0.5);
				double phi = M_PI*(randomDouble() - 0.5);
				DoubleVec3D newDirection(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));  // vector on sphere of radius 1
				double dotProduct = dotProd(newDirection, normal);
				if (dotProduct < 0) { // Wrong hemisphere
					newDirection = -newDirection;
					dotProduct = -dotProduct;
				}

				DoubleVec3D recursiveColour = traceRay(Ray(intersection, newDirection), bounces + 1);
				result += DoubleVec3D(recursiveColour.getX() * objectColour.getX(),
									 recursiveColour.getY() * objectColour.getY(),
					                 recursiveColour.getZ() * objectColour.getZ())
					                 * dotProduct / M_PI / M_PI;
				break;
			}

			// Refractive BRDF
			case BRDF::Refractive: 
			{
				std::cout << "Refractive BRDF will be implemented later." << std::endl;
				break;
			}

			// Specular BRDF
			case BRDF::Specular:
			{
				DoubleVec3D newDirection = ray.getDirection() - normal*dotProd(currentRayDirection, normal)*2;  // gets normalised in ray constructor
				DoubleVec3D recursiveColour = traceRay(Ray(intersection, newDirection), bounces + 1);
				result += recursiveColour;
				break;
			}

			default:
				std::cout << "A BRDF was not implemented." << std::endl;
			}
		} // nothing hit
	} // max bounces
	return result;
}

int main() {
	long long beginningTime = std::chrono::system_clock::now().time_since_epoch().count();

	// Make scene
	// Spheres
	scene.push_back(new Sphere(DoubleVec3D(0, -1.5, -2.5), 0.5, Material(DoubleVec3D(0), BRDF::Diffuse, 10000)));
	// scene.push_back(new Sphere(DoubleVec3D(0.5, 1.5, -2), 0.5, Material(DoubleVec3D(0), BRDF::Specular)));
	scene.push_back(new Sphere(DoubleVec3D(-1, 1.5, -2.5), 0.5, Material(DoubleVec3D(6), BRDF::Diffuse)));
	// left
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, 1), DoubleVec3D(-2, -2, -4), Material(DoubleVec3D(2, 2, 10), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, -4), DoubleVec3D(-2, 2, -4), Material(DoubleVec3D(2, 2, 10), BRDF::Diffuse)));
	// right
	scene.push_back(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(2, -2, 1), DoubleVec3D(2, 2, 1), Material(DoubleVec3D(10, 2, 2), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(2, -2, -4), DoubleVec3D(2, 2, 1), Material(DoubleVec3D(10, 2, 2), BRDF::Diffuse)));
	// Top
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, 2, -4), Material(DoubleVec3D(3), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, -4), DoubleVec3D(2, 2, 1), Material(DoubleVec3D(3), BRDF::Diffuse)));
	// Bottom
	scene.push_back(new Triangle(DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, -4), Material(DoubleVec3D(3), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, 1), Material(DoubleVec3D(3), BRDF::Diffuse)));
	// Background
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, 2, -4), Material(DoubleVec3D(2, 10, 2), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, -2, -4), Material(DoubleVec3D(2, 10, 2), BRDF::Diffuse)));
	// Behind camera
	scene.push_back(new Triangle(DoubleVec3D(2, 2, 1), DoubleVec3D(2, -2, 1), DoubleVec3D(-2, -2, 1), Material(DoubleVec3D(6), BRDF::Diffuse)));
	scene.push_back(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, 1), DoubleVec3D(-2, -2, 1), Material(DoubleVec3D(6), BRDF::Diffuse)));
	
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOV_X);

	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	std::cout << "\r" << "Width=" << PICTURE_WIDTH << "   Height=" << PICTURE_HEIGHT << "   Spp=" << SAMPLE_PER_PIXEL << "   Bounces=" << MAX_BOUNCES << std::endl;

	// Trace
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		std::cout << "\r" << (double)pixelX / PICTURE_WIDTH * 100 << "%";
		for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
			// std::cout << "\r" << (double)(pixelX*PICTURE_WIDTH + pixelY) / (PICTURE_WIDTH*PICTURE_HEIGHT) * 100 << "%";
			for (unsigned int samples = 0; samples < SAMPLE_PER_PIXEL; samples++) {
				Ray currentRay = camera.getRayGoingThrough(pixelX + randomDouble() - 0.5, pixelY + randomDouble() - 0.5);
				picture[pixelX][pixelY] += traceRay(currentRay)/SAMPLE_PER_PIXEL;
			}
		}
	}

	// Write
	std::ofstream file;
	file.open("picture.ppm");
	file << "P3\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n" << "255\n";
	for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
		for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
			DoubleVec3D currentColour = picture[pixelX][pixelY];
			file << std::min(255, (int)currentColour.getX()) << " ";
			file << std::min(255, (int)currentColour.getY()) << " ";
			file << std::min(255, (int)currentColour.getZ()) << "   ";
		}
		file << "\n";
	}
	file.close();

	long long endingTime = std::chrono::system_clock::now().time_since_epoch().count();
	std::cout << "\nComputed in " << (double)(endingTime - beginningTime) / std::chrono::system_clock::period::den << " seconds.\n";

	return 0;
}
