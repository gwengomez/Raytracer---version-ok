#include "Ray.h"

#pragma region get/set
Vecteur3D Ray::getOrigine()
{
	return origine;
}

void Ray::setOrigine(Vecteur3D origine)
{
	this->origine.setX(origine.getX());
	this->origine.setY(origine.getY());
	this->origine.setZ(origine.getZ());
}

Vecteur3D Ray::getDirection()
{
	return direction;
}

void Ray::setDirection(Vecteur3D direction)
{
	this->direction.setX(direction.getX());
	this->direction.setY(direction.getY());
	this->direction.setZ(direction.getZ());
}

bool Ray::estReflection()
{
	return reflection;
}

void Ray::setReflection(bool reflection)
{
	this->reflection = reflection;
}
#pragma endregion get/set

Ray::Ray() {}

Ray::Ray(Vecteur3D origine, Vecteur3D direction, bool reflection) {
	setOrigine(origine);
	setDirection(direction);
	setReflection(reflection);
}

Ray::Ray(Vecteur3D origine, Vecteur3D direction) {
	setOrigine(origine);
	setDirection(direction);
	setReflection(false);
}

Vecteur3D Ray::position3D(float t)
{
	return origine.addition(direction.normalize().multiplicationNombre(t));
}

std::ostream& operator<<(std::ostream& os, Vecteur3D& vec3)
{
	os << vec3.getX() << ';' << vec3.getY() << ';' << vec3.getZ();
	return os;
}