#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <string>
#include "Vecteur3D.h"
#include "Ray.h"
#include <vector>
#include "Sphere.h"
#include "Light.h"

class Scene
{
private:

	std::vector<Sphere> spheres;
	std::vector<Light> lumieres;

public:

	std::vector<Sphere> getSpheres();
	Scene();
	void addSphere(Sphere s);
	void addLight(Light l);
	std::vector<Ray> genererRay(Vecteur3D position, int nbRay, Vecteur3D normale);
	Vecteur3D getCouleur(Ray rayon, int profondeur);
	Vecteur3D calculReflections(Sphere s, Ray r, float t, int profondeur);
	std::pair<Sphere, float> getIntersec(Ray r);
	
};
#endif