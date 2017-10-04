#include "Sphere.h"
#include <iostream>
#define M_PI 3.14159265

#pragma region get/set
/*Accesseurs*/
Vecteur3D Sphere::getCentre()
{
	return centre;
}

void Sphere::setCentre(Vecteur3D centre)
{
	this->centre.setX(centre.getX());
	this->centre.setY(centre.getY());
	this->centre.setZ(centre.getZ());
}

float Sphere::getRayon()
{
	return rayon;
}

void Sphere::setRayon(float rayon)
{
	this->rayon = rayon;
}

Vecteur3D Sphere::getAlbedo() {
	return albedo;
}

void Sphere::setAlbedo(Vecteur3D albedo)
{
	this->albedo.setX(albedo.getX());
	this->albedo.setY(albedo.getY());
	this->albedo.setZ(albedo.getZ());
}

bool Sphere::estMirroir()
{
	return mirroir;
}

void Sphere::setMirroir(bool miroir)
{
	this->mirroir = miroir;
}
#pragma endregion get/set

/*Constructeurs*/
Sphere::Sphere(){}

Sphere::Sphere(Vecteur3D centre, float rayon, Vecteur3D albedo)
{
	setCentre(centre);
	setRayon(rayon);
	setAlbedo(albedo);
	setMirroir(false);
}

Sphere::Sphere(Vecteur3D centre, float rayon, Vecteur3D albedo, bool mirroir)
{
	setCentre(centre);
	setRayon(rayon);
	setAlbedo(albedo);
	setMirroir(true);
}

/*Fonction de recherche des intersections du rayon avec la sphere*/
float Sphere::possedeIntersec(Ray rayon) {
	float t = 0;
	float t1 = 0;
	float t2 = 0;
	// Calcul du discriminant
	float b = rayon.getDirection().normalize().prodScal(rayon.getOrigine().soustraction(centre)) * 2;
	float a = 1.0;
	float c = pow(rayon.getOrigine().soustraction(centre).norme(), 2) - pow(this->rayon,2);
	float discriminant = pow(b, 2) - 4 * a * c;

	// discriminant = 0 -> 1 intersection, discriminant > 0 -> 2 intersections, discriminant < 0 -> 0 intersection
	if (discriminant == 0)
		t = -b / 2 * a;
	if (discriminant > 0)
	{
		t1 = (-b + sqrt(discriminant)) / 2 * a;
		t2 = (-b - sqrt(discriminant)) / 2 * a;
		// On choisit le t le plus petit qui symbolise l'intersection la plus proche de la caméra
		if (t1 < t2)
		{
			if (t1 > 0)
				t = t1;
			else
			{
				if (t2 > 0)
					t = t2;
			}
		}
		else
		{
			if (t2 > 0)
				t = t2;
		}
	}

	// Renvoie l'intersection la plus proche de la caméra
	return t;
}

/*Renvoie la normale de la sphere en un point donne*/
Vecteur3D Sphere::getNormale(Vecteur3D pointIntersec) {
	Vecteur3D directSphere = pointIntersec.soustraction(centre);
	Vecteur3D normalDirectSphere = directSphere.normalize();
	return normalDirectSphere;
}

