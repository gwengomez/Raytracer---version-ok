#include "Vecteur3D.h"
#include <cmath>

Vecteur3D::Vecteur3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vecteur3D::Vecteur3D() {}

#pragma region get/set
/*Accesseurs*/
float Vecteur3D::getX()
{
	return x;
}

void Vecteur3D::setX(float x) {
	this->x = x;
}

float Vecteur3D::getY()
{
	return y;
}

void Vecteur3D::setY(float y) {
	this->y = y;
}

float Vecteur3D::getZ()
{
	return z;
}

void Vecteur3D::setZ(float z) {
	this->z = z;
}
#pragma endregion get/set


#pragma region operations
/*Fonction d'addition de 2 vecteurs*/
Vecteur3D Vecteur3D::addition(Vecteur3D vec3)
{
	float a = this->x + vec3.getX();
	float b = this->y + vec3.getY();
	float c = this->z + vec3.getZ();
	return Vecteur3D(a, b, c);
}

/*Fonction de soustraction de 2 vecteurs*/
Vecteur3D Vecteur3D::soustraction(Vecteur3D vec3)
{
	float a = this->x - vec3.getX();
	float b = this->y - vec3.getY();
	float c = this->z - vec3.getZ();
	return Vecteur3D(a, b, c);
}

/*Fonction de multiplication terme par terme de 2 vecteurs*/
Vecteur3D Vecteur3D::multiplicationTermes(Vecteur3D vec3)
{
	float a = this->x * vec3.getX();
	float b = this->y * vec3.getY();
	float c = this->z * vec3.getZ();
	return Vecteur3D(a, b, c);
}

/*Fonction de division terme par terme de 2 vecteurs*/
Vecteur3D Vecteur3D::divisionTermes(Vecteur3D vec3)
{
	float a = 0;
	float b = 0;
	float c = 0;

	// Test de la division par 0. Si oui, la fonction renvoie un vecteur (0,0,0)
	if (vec3.getX() != 0 && vec3.getY() != 0 && vec3.getZ() != 0) {
		a = this->x / vec3.getX();
		b = this->y / vec3.getY();
		c = this->z / vec3.getZ();
	}
	return Vecteur3D(a, b, c);
}

/*Fonction de multiplication par un nombre sur un vecteur*/
Vecteur3D Vecteur3D::multiplicationNombre(float x)
{
	float a = this->x * x;
	float b = this->y * x;
	float c = this->z * x;
	return Vecteur3D(a, b, c);
}

/*Fonction de division par un nombre sur un vecteur*/
Vecteur3D Vecteur3D::divisionNombre(float x)
{
	float a = 0;
	float b = 0;
	float c = 0;

	// Test de la division par 0. Si oui, la fonction renvoie un vecteur (0,0,0)
	if (x != 0) {
		if (this->x != 0)
			a = this->x / x;
		if (this->y != 0)
			b = this->y / x;
		if (this->z != 0)
			c = this->z / x;
	}
	return Vecteur3D(a, b, c);
}
#pragma endregion operations

#pragma region fonctions
/*Calcul de la norme d'un vecteur*/
float Vecteur3D::norme()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

/*Calcul de la norme carré d'un vecteur*/
float Vecteur3D::normeCarre()
{
	return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
}

/*Fonction de normalisation d'un vecteur*/
Vecteur3D Vecteur3D::normalize()
{
	float norme = this->norme();
	float a = 0;
	float b = 0;
	float c = 0;

	// Test de la division par 0. Si oui, la fonction renvoie un vecteur (0,0,0)
	if (norme > 0) {
		a = this->x / norme;
		b = this->y / norme;
		c = this->z / norme;
	}
	return Vecteur3D(a, b, c);
}

/*Calcul du produit scalaire d'un vecteur*/
float Vecteur3D::prodScal(Vecteur3D vec3)
{
	return this->x * vec3.getX() + this->y * vec3.getY() + this->z * vec3.getZ();
}

/*Calcul du produit vectoriel de 2 vecteurs*/
Vecteur3D Vecteur3D::prodVect(Vecteur3D vec3)
{
	float a = this->y * vec3.getZ() - this->z * vec3.getY();
	float b = this->z * vec3.getX() - this->x * vec3.getZ();
	float c = this->x * vec3.getY() - this->y * vec3.getX();
	return Vecteur3D(a, b, c);
}
#pragma endregion fonctions