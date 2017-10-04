#pragma once
#ifndef RAY_H
#define RAY_H
#include <string>
#include <iostream>
#include "Vecteur3D.h"

class Ray
{
private:

	Vecteur3D origine;
	Vecteur3D direction;
	bool reflection;

public:

	Vecteur3D getOrigine();
	void setOrigine(Vecteur3D origine);
	Vecteur3D getDirection();
	void setDirection(Vecteur3D direction);
	bool estReflection();
	void setReflection(bool reflection);
	Ray();
	Ray(Vecteur3D origine, Vecteur3D direction);
	Ray(Vecteur3D origine, Vecteur3D direction, bool reflection);
	Vecteur3D position3D(float t);

};

std::ostream& operator<<(std::ostream& os, Vecteur3D& vec3);
#endif