#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include "Vecteur3D.h"
#include "Ray.h"
#include <vector>
#include "Sphere.h"

class Light
{
private:

	Vecteur3D position;
	float intensite;
	float rayon;
	std::vector<Vecteur3D> pointsSphere;

public:

	Vecteur3D getPosition();
	void setPosition(Vecteur3D position);
	float getIntensite();
	void setIntensite(float intensite);
	float getRayon();
	void setRayon(float rayon);
	std::vector<Vecteur3D> getPointsSphere();
	void addPointsSphere(Vecteur3D vec);
	Light();
	Light(Vecteur3D position, float intensite);
	Light(Vecteur3D position, float intensite, float rayon);
	Vecteur3D generateRandomPoint(float r1, float r2);
};
#endif