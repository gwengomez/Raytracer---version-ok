#include<string>
#include <iostream>
#include <vector>
#include "Vecteur3D.h"
#include "Utils.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"
#include "Box.h"
#include <time.h>
#include <omp.h>
#define M_PI 3.14159265

int main()
{
	/*Vecteur3D vecteur0 = Vecteur3D(0, 0, 0);
	Vecteur3D vecteur1 = Vecteur3D(1, 2, 3);
	Vecteur3D vecteur2 = Vecteur3D(3, 4, 6);
	Vecteur3D vecteur3 = Vecteur3D(4, 8, 16);

	Vecteur3D vecteur4 = vecteur1.addition(vecteur2); //(4,6,9)
	Vecteur3D vecteur5 = vecteur2.soustraction(vecteur1); //(2,2,3)
	Vecteur3D vecteur6 = vecteur1.multiplicationTermes(vecteur2); //(3,8,18)
	Vecteur3D vecteur7 = vecteur2.divisionTermes(vecteur1); //(3,2,2)
	Vecteur3D vecteur7 = vecteur2.divisionTermes(vecteur0); //(0,0,0)
	Vecteur3D vecteur8 = vecteur1.multiplicationNombre(5); //(5,10,15)
	Vecteur3D vecteur9 = vecteur3.divisionNombre(2); //(2,4,8)
	float norme1 = vecteur1.norme(); //3.74165...
	float norme2 = vecteur1.normeCarre(); // 14
	Vecteur3D vecteur10 = vecteur1.normalize(); //à vérifier à la calculatrice mais en principe correct
	Vecteur3D vecteur10 = vecteur0.normalize(); //(0,0,0)
	float prodScal = vecteur1.prodScal(vecteur2); //29
	Vecteur3D vecteur11 = vecteur1.prodVect(vecteur2); //(0,3,-2)*/

	/*float testClamp1 = clamp(5, 2, 10);
	float testClamp2 = clamp(1, 2, 10);
	float testClamp3 = clamp(15, 2, 10);*/

	//save_img();

	// Initialise la seed du random
	srand(time(0));

	Light l = Light(Vecteur3D(0, 0, 0), 200000, 1);
	Vecteur3D moy = Vecteur3D(0, 0, 0);
	for (auto p : l.getPointsSphere()) {
		moy = moy.addition(p.soustraction(l.getPosition()));
	}
	moy = moy.divisionNombre(l.getPointsSphere().size());

	// Caractéristiques de la camera
	int const W = 1024;
	int const H = 1024;
	float fov = 60 * M_PI/180;
	Vecteur3D origineCamera = Vecteur3D(0, 0, 20);

	

	// Création des lumieres
	//Light l1 = Light(Vecteur3D(0, 20, -35), 250000, 3); // En haut a droite, a la meme profondeur que la sphere centrale
	//Light l2 = Light(Vecteur3D(-15, 20, -55), 250000, 3); // En haut a gauche, a la meme profondeur que la sphere centrale
	//Light l3 = Light(Vecteur3D(-15, -30, -10), 250000, 3);  // En bas a gauche, au premier plan par rapport a la camera

	// Creation des spheres
	//Sphere s1 = Sphere(Vecteur3D(0, -10, -45), 10, Vecteur3D(1,0,0)); // Sphere centrale, mirroir
	//Sphere s2 = Sphere(Vecteur3D(0, -2000-50, 0), 2000, Vecteur3D(0.1, 1, 0.1)); // Sol, vert
	//Sphere s3 = Sphere(Vecteur3D(0, 2000+50, 0), 2000, Vecteur3D(0.1, 0.1, 1)); // Plafond, bleu
	//Sphere s4 = Sphere(Vecteur3D(-2000 - 50, 0, 0), 2000, Vecteur3D(1, 1, 0.1)); // Mur gauche, jaune
	//Sphere s5 = Sphere(Vecteur3D(2000+50, 0, 0), 2000, Vecteur3D(1, 0.1, 1), true); // Mur droit, rose
	//Sphere s6 = Sphere(Vecteur3D(0, 0, -2000-100), 2000, Vecteur3D(0.1, 1, 1)); //Mur du fond, cyan
	//Sphere s7 = Sphere(Vecteur3D(-25, -30, -80), 15, Vecteur3D(1, 1, 1)); // Sphere en bas a gauche, mirroir
	//Sphere s8 = Sphere(Vecteur3D(15, 10, -65), 6, Vecteur3D(1, 0.1, 0.1)); // Sphere en haut legerement a droite, rouge

	Light l1 = Light(Vecteur3D(-5, -5, -35), 150000, 3);
	Light l2 = Light(Vecteur3D(-5, -5, -45), 150000, 3);
	Light l3 = Light(Vecteur3D(-5, 5, -35), 150000, 3);
	Light l4 = Light(Vecteur3D(-5, 5, -45), 150000, 3);
	Light l5 = Light(Vecteur3D(5, -5, -35), 150000, 3);
	Light l6 = Light(Vecteur3D(5, -5, -45), 150000, 3);
	Light l7 = Light(Vecteur3D(5, 5, -35), 150000, 3);
	Light l8 = Light(Vecteur3D(5, 5, -45), 150000, 3);

	Sphere s1 = Sphere(Vecteur3D(-20, -20, -20), 10, Vecteur3D(1, 0, 0));
	Sphere s2 = Sphere(Vecteur3D(-20, -20, -60), 10, Vecteur3D(1, 0, 0));
	Sphere s3 = Sphere(Vecteur3D(20, -20, -20), 10, Vecteur3D(1, 0, 0));
	Sphere s4 = Sphere(Vecteur3D(20, -20, -60), 10, Vecteur3D(1, 0, 0));
	Sphere s5 = Sphere(Vecteur3D(-20, 20, -20), 10, Vecteur3D(1, 0, 0));
	Sphere s6 = Sphere(Vecteur3D(-20, 20, -60), 10, Vecteur3D(1, 0, 0));
	Sphere s7 = Sphere(Vecteur3D(20, 20, -20), 10, Vecteur3D(1, 0, 0));
	Sphere s8 = Sphere(Vecteur3D(20, 20, -60), 10, Vecteur3D(1, 0, 0));



	// Creation de la scene et ajout des objets
	Scene sc = Scene();
	sc.addSphere(s1);
	sc.addSphere(s2);
	sc.addSphere(s3);
	sc.addSphere(s4);
	sc.addSphere(s5);
	sc.addSphere(s6);
	sc.addLight(l1);
	sc.addLight(l2);
	//sc.addLight(l3);
	sc.addSphere(s7);
	sc.addSphere(s8);

	Box boitePrincipale = Box(sc.getSpheres());

	// Creation du tableau dynamique contenant les pixels
	std::vector<Vecteur3D> pixels(H*W);

	int i, j;
	#pragma omp parallel
	for (i = 0; i < H; i++) {
		#pragma omp parallel for schedule(dynamic)
		for (j = 0; j < W; j++) {
			// Creation du rayon
			Ray r = Ray(origineCamera, Vecteur3D(W-j-W/2.0,i-H/2.0,-W/(2.0*tan(fov/2.0))), false);

			// Recherche de la couleur du pixel
			Vecteur3D couleur = clamp(sc.getCouleur(r, 10), 0, 255);
			 // On associe au pixel la couleur trouvee
			 pixels.at(i*W + j) = couleur;;
		}
	}

	// Creation de l'image
	save_img(pixels, W, H);

	return 0;
}

