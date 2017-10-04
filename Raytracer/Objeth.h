#pragma once
#ifndef OBJET_H
#define OBJET_H
#include <string>
#include "Vecteur3D.h"
#include "Ray.h"

class Objet
{
private:
	Vecteur3D couleur;


public:

	Vecteur3D getCouleur();
	void setCouleur(Vecteur3D couleur);
	float possedeIntersec(Ray rayon);
};
#endif