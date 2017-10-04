#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include <string>
#include "Vecteur3D.h"
#include "Ray.h"

class Sphere
{
private:

	Vecteur3D centre;
	float rayon;
	Vecteur3D albedo;
	bool mirroir;

public:

	Vecteur3D getCentre();
	void setCentre(Vecteur3D origine);
	float getRayon();
	void setRayon(float rayon);
	Vecteur3D getAlbedo();
	void setAlbedo(Vecteur3D albedo);
	bool estMirroir();
	void setMirroir(bool mirroir);
	Sphere();
	Sphere(Vecteur3D centre, float rayon, Vecteur3D couleur);
	Sphere(Vecteur3D centre, float rayon, Vecteur3D couleur, bool miroir);
	float possedeIntersec(Ray rayon);
	Vecteur3D getNormale(Vecteur3D pointIntersec);
};
#endif