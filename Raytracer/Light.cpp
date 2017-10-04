#include "Light.h"
#include "Scene.h"
#define M_PI 3.14159265

#pragma region get/set
Vecteur3D Light::getPosition()
{
	return position;
}

void Light::setPosition(Vecteur3D position)
{
	this->position.setX(position.getX());
	this->position.setY(position.getY());
	this->position.setZ(position.getZ());
}

float Light::getIntensite()
{
	return intensite;
}

void Light::setIntensite(float intensite)
{
	this->intensite = intensite;
}

float Light::getRayon()
{
	return rayon;
}

void Light::setRayon(float rayon)
{
	this->rayon = rayon;
}

std::vector<Vecteur3D> Light::getPointsSphere()
{
	return pointsSphere;
}

void Light::addPointsSphere(Vecteur3D vec)
{
	pointsSphere.push_back(vec);
}

Light::Light() {}

Light::Light(Vecteur3D position, float intensite)
{
	setPosition(position);
	setIntensite(intensite);
	setRayon(0);
}

Light::Light(Vecteur3D position, float intensite, float rayon)
{
	setPosition(position);
	setIntensite(intensite);
	setRayon(rayon);

	float r1;
	float r2;

	for (int i = 0; i < 20; i++)
	{
		r1 = double(rand()) / double(RAND_MAX);
		r2 = double(rand()) / double(RAND_MAX);
		addPointsSphere(generateRandomPoint(r1, r2));
	}
	
}

Vecteur3D Light::generateRandomPoint(float r1, float r2)
{
	
	float x = position.getX() + 2 * rayon * cos(2 * M_PI * r1) * sqrt(r2 * (1 - r2));
	float y = position.getY() + 2 * rayon * sin(2 * M_PI * r1) * sqrt(r2 * (1 - r2));
	float z = position.getZ() + rayon * (1 - 2 * r2);

	return Vecteur3D(x, y, z);
}
#pragma endregion get/set

