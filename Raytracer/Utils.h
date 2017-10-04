#pragma once
#include <fstream>
#include<string>
#include <iostream>
#include "Vecteur3D.h"

using namespace std;

/*Fonction de troncage d'un nombre entre 2 valeurs définies*/
static float clamp(float val, float min, float max)
{
	float valRetournee = val;
	if (val < min)
		valRetournee = min;
	if (val > max)
		valRetournee = max;
	return valRetournee;
}

/*Utilisation de la fonction clamp directement pour un objet de type Vecteur3D*/
static Vecteur3D clamp(Vecteur3D vec, float min, float max)
{
	return Vecteur3D(clamp(vec.getX(), min, max), clamp(vec.getY(), min, max), clamp(vec.getZ(), min, max));
}

/*Sauvegarde d'une image d'apres un tableau de pixels*/
static void save_img(std::vector<Vecteur3D> pixels, int largeur, int longueur)
{
	// Création et écriture dans le fichier image.ppm
	ofstream outfile("image.ppm");
	outfile << "P3 \n";
	outfile << largeur << " " << longueur << " \n";
	outfile << "255 \n";
	// Pour chaque vecteur du tableau, on affiche une ligne qui contient les 3 valeurs du vecteur correspondant aux couleurs rgb du pixel
	for (vector<Vecteur3D>::size_type i = pixels.size()-1; i > 0; i--) {
			outfile << pixels.at(i).getX() << " " << pixels.at(i).getY() << " " << pixels.at(i).getZ() << " \n";
	}
	outfile.close();
}

static float valeurAbsolue(float nb)
{
	float valeur = nb;
	if (valeur < 0)
		valeur *= (-1);
	return valeur;
}