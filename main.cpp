#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "Object3D.h"
#include "Sphere.h"
#include "TrianglePlane.h"
#include "PerspectiveCamera.h"
#include "Ray.h"
#include "DoubleVec3.h"
#include "Material.h"

std::uniform_real_distribution<double> unif(0, 1);
std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());  // new seed each time

std::vector<Object3D*> scene;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
DoubleVec3 picture [PICTURE_WIDTH][PICTURE_HEIGHT];
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MAX_BOUNCES = 5;
constexpr unsigned int SAMPLE_PER_PIXEL = 1024;

double randomDouble() {
	return unif(re);
}

DoubleVec3 newDirectionOnHemisphere(const DoubleVec3& normal) {
	// Generate vector on sphere and then check if angle with normal is between -pi/2 and pi/2
	double cos_angle = -1;
	DoubleVec3 randomVec;
	while (cos_angle < 0) {
		double theta = M_PI*randomDouble() - M_PI_2;
		double phi = M_PI*randomDouble() - M_PI_2;
		randomVec = DoubleVec3(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
		cos_angle = dotProd(randomVec, normal);
	}
	return randomVec;
}

DoubleVec3 traceRay(const Ray& ray, DoubleVec3 colour = DoubleVec3(0.0), unsigned int bounces = 0) {  // is "colour" necessary ?
	if (bounces < MAX_BOUNCES) {
		double smallestPositiveDistance = MAX_DEPTH + 1;  // Strictly positive -> we don't want it to intersect with same object
		Object3D* closestObject = nullptr;
		for (Object3D* object : scene) {
			double distance = object->closestIntersection(ray);
			if (distance > DBL_EPSILON&& distance < smallestPositiveDistance) {
				smallestPositiveDistance = distance;
				closestObject = object;
			}
		}
		if (smallestPositiveDistance < MAX_DEPTH) {
			Material objectMaterial = closestObject->getMaterial();
			DoubleVec3 objectColour = objectMaterial.getColour();
			colour += DoubleVec3((double)objectMaterial.getEmittance());
			// assume BRDF is diffuse
			DoubleVec3 intersection = ray.getOrigin() + smallestPositiveDistance * ray.getDirection();
			DoubleVec3 normal = closestObject->getNormal(intersection);
			DoubleVec3 newDirection = newDirectionOnHemisphere(normal);
			Ray newRay = Ray(intersection, newDirection);
			DoubleVec3 recursiveColour = traceRay(newRay, DoubleVec3(0.0), bounces + 1);
			colour += DoubleVec3(recursiveColour.getX()*objectColour.getX(),
					             recursiveColour.getY()*objectColour.getY(),
				                 recursiveColour.getZ()*objectColour.getZ())
				      * dotProd(ray.getDirection(), normal);
			return colour;
		}
		else  // did not hit anything
			return colour;
	}
	else // max bounces
		return colour;
}

int main() {
	// Make scene
	// Spheres
	scene.push_back(new Sphere(DoubleVec3(1, 1, -2), 0.5, Material(DoubleVec3(0), BRDF::Diffuse, 255)));
	scene.push_back(new Sphere(DoubleVec3(-1, -1, -3), 0.5, Material(DoubleVec3(2), BRDF::Diffuse)));
	// left
	scene.push_back(new TrianglePlane(DoubleVec3(-2, 2, 1), DoubleVec3(-2, -2, 1), DoubleVec3(-2, -2, -4), Material(DoubleVec3(0, 0, 5), BRDF::Diffuse)));
	scene.push_back(new TrianglePlane(DoubleVec3(-2, 2, 1), DoubleVec3(-2, -2, -4), DoubleVec3(-2, 2, -4), Material(DoubleVec3(0, 0, 5), BRDF::Diffuse)));
	// right
	scene.push_back(new TrianglePlane(DoubleVec3(2, -2, -4), DoubleVec3(2, -2, 1), DoubleVec3(2, 2, 1), Material(DoubleVec3(5, 0, 0), BRDF::Diffuse)));
	scene.push_back(new TrianglePlane(DoubleVec3(2, 2, -4), DoubleVec3(2, -2, -4), DoubleVec3(2, 2, 1), Material(DoubleVec3(5, 0, 0), BRDF::Diffuse)));
	// Top
	scene.push_back(new TrianglePlane(DoubleVec3(2, 2, -4), DoubleVec3(-2, 2, 1), DoubleVec3(-2, 2, -4), Material(DoubleVec3(5), BRDF::Diffuse)));
	scene.push_back(new TrianglePlane(DoubleVec3(-2, 2, 1), DoubleVec3(2, 2, -4), DoubleVec3(2, 2, 1), Material(DoubleVec3(5), BRDF::Diffuse)));
	// Bottom
	scene.push_back(new TrianglePlane(DoubleVec3(-2, -2, 1), DoubleVec3(2, -2, -4), DoubleVec3(-2, -2, -4), Material(DoubleVec3(5), BRDF::Diffuse)));
	scene.push_back(new TrianglePlane(DoubleVec3(2, -2, -4), DoubleVec3(-2, -2, 1), DoubleVec3(2, -2, 1), Material(DoubleVec3(5), BRDF::Diffuse)));
	// Background
	scene.push_back(new TrianglePlane(DoubleVec3(-2, 2, -4), DoubleVec3(-2, -2, -4), DoubleVec3(2, 2, -4), Material(DoubleVec3(0, 5, 0), BRDF::Diffuse)));
	scene.push_back(new TrianglePlane(DoubleVec3(2, 2, -4), DoubleVec3(-2, -2, -4), DoubleVec3(2, -2, -4), Material(DoubleVec3(0, 5, 0), BRDF::Diffuse)));
	// Behind camera
	// scene.push_back(new TrianglePlane(DoubleVec3(2, 2, 1), DoubleVec3(2, -2, 1), DoubleVec3(-2, -2, 1), Material(DoubleVec3(5), BRDF::Diffuse)));
	// scene.push_back(new TrianglePlane(DoubleVec3(-2, 2, 1), DoubleVec3(2, 2, 1), DoubleVec3(-2, -2, 1), Material(DoubleVec3(5), BRDF::Diffuse)));
	
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOV_X);

	// Trace
	for (unsigned int pixelX = 0; pixelX < PICTURE_WIDTH; pixelX++) {
		std::cout << "\r" << (double)pixelX / PICTURE_WIDTH * 100 << "%     ";
		for (unsigned int pixelY = 0; pixelY < PICTURE_HEIGHT; pixelY++) {
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
			DoubleVec3 currentColour = picture[pixelX][pixelY];
			file << std::min(255, (int)currentColour.getX()) << " ";
			file << std::min(255, (int)currentColour.getY()) << " ";
			file << std::min(255, (int)currentColour.getZ()) << "\n";
		}
	}
	file.close();

	return 0;
}
