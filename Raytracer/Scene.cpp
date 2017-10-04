#include "Scene.h"
#define M_PI 3.14159265

std::vector<Sphere> Scene::getSpheres()
{
	return spheres;
}

Scene::Scene() {}

void Scene::addSphere(Sphere s)
{
	spheres.push_back(s);
}

void Scene::addLight(Light l)
{
	lumieres.push_back(l);
}

std::vector<Ray> Scene::genererRay(Vecteur3D position, int nbRay, Vecteur3D normale)
{
	std::vector<Ray> rayonsGeneres(nbRay);
	float rayon = 2;
	float r1;
	float r2;

	for (int i = 0; i < nbRay; i++)
	{
		r1 = double(rand()) / double(RAND_MAX);
		r2 = double(rand()) / double(RAND_MAX);
		float x = position.getX() + 2 * rayon * cos(2 * M_PI * r1) * sqrt(r2 * (1 - r2));
		float y = position.getY() + 2 * rayon * sin(2 * M_PI * r1) * sqrt(r2 * (1 - r2));
		float z = position.getZ() + rayon * (1 - 2 * r2);
		Vecteur3D dir = Vecteur3D(x, y, z);
		if (dir.prodScal(normale) < 0)
		{
			dir = dir.multiplicationNombre(-1);
		}
		Ray ray = Ray(position, dir.normalize());
		rayonsGeneres.push_back(ray);
	}

	return rayonsGeneres;
}

/*Fonction qui cherche le rayon de reflexion dans le cas d'un mirroir et qui appelle la fonction de recherche de couleur sur ce rayon*/
Vecteur3D Scene::calculReflections(Sphere s, Ray r, float t, int profondeur)
{
	// Calcul de la position du point d'intersection de l'objet avec le rayon
	Vecteur3D pointIntersec = r.getOrigine().addition(r.getDirection().normalize().multiplicationNombre(t));
	Vecteur3D normalDirectSphere = s.getNormale(pointIntersec);
	// On cherche la direction du rayon reflechi
	Vecteur3D directionRayonReflection = normalDirectSphere.multiplicationNombre(r.getDirection().normalize().prodScal(normalDirectSphere) * (-2)).addition(r.getDirection().normalize());
	Ray rayonReflection = Ray(pointIntersec, directionRayonReflection, true);
	profondeur--;
	// On appelle la fonction de calcul des intersections de manière recursive afin de trouver quelle est la couleur de l'objet sur lequel le rayon est reflechi
	Vecteur3D couleur = getCouleur(rayonReflection, profondeur);
	return couleur;
}

/*Fonction qui, pour un rayon passe en parametre, calcule et renvoie la couleur du pixel par rapport aux lumières de la scene*/
Vecteur3D Scene::getCouleur(Ray rayon, int profondeur) {
	// Initialisation des parametres
	Vecteur3D couleur = Vecteur3D(0,0,0);
	float distance;
	Sphere s;
	Vecteur3D normale;
	Vecteur3D vecL;
	Light l;
	Ray rayonLumiere;
	Vecteur3D pointIntersec;
	// Association d'une sphere et de la distance entre cette sphere et la camera
	std::pair<Sphere, float> intersection;
	std::pair<Sphere, float> intersectionTemp;

	// Recherche de l'objet le plus proche de la camera
	intersection = getIntersec(rayon);

	s = intersection.first;
	distance = intersection.second;

	// Si aucune intersection n'est trouvée, le pixel est noir par default
	if (distance == 0)
	{
		couleur = Vecteur3D(0, 0, 0);
	}
	else
	{
		// Position du point d'intersection entre la camera et l'objet le plus proche
		Vecteur3D pointIntersecTemp = rayon.getOrigine().addition(rayon.getDirection().normalize().multiplicationNombre(distance));
		// Position du point d'intersection replacée afin de sortir legerement de la sphere
		pointIntersec = pointIntersecTemp.addition(s.getNormale(pointIntersecTemp).multiplicationNombre(0.001));

		// Si l'objet regarde est un mirroir
		if (s.estMirroir() && profondeur > 0)
		{
			// On cherche la couleur du pixel par reflection
			couleur = calculReflections(s, rayon, distance, profondeur);
		}
		else
		{
			// On parcourt toutes les lumieres presentes dans la scene
			for (auto l : lumieres) {
				Vecteur3D couleurTemp = Vecteur3D(0, 0, 0);
				if (l.getRayon() > 0)
				{
					for (auto p : l.getPointsSphere())
					{
						// Creation du rayon entre la lumiere et l'objet regarde
						rayonLumiere = Ray(p, pointIntersec.soustraction(p), false);
						// Recherche de l'intersection la plus proche de la lumiere
						intersectionTemp = getIntersec(rayonLumiere);
						// Recuperation de la distance entre l'objet regarde et la lumiere
						float distanceSL = rayonLumiere.getOrigine().soustraction(pointIntersec).norme();
						// Si aucun objet ne se trouve entre l'objet regardé et la lumiere
						if (distanceSL <= intersectionTemp.second)
						{
							normale = s.getNormale(pointIntersec);
							vecL = p.soustraction(pointIntersec).normalize();
							float nl = normale.prodScal(vecL);
							if (normale.prodScal(vecL) > 0)
								// Application de la couleur au pixel en fonction de l'albedo, l'intensite de la lumiere, la normale de la sphere à l'intersection,
								// le vecteur entre l'intersection et la lumiere normalisé et la distance entre l'intersection et la lumiere
								couleurTemp = couleurTemp.addition(s.getAlbedo().multiplicationNombre((normale.prodScal(vecL)* l.getIntensite()) / pow(distanceSL, 2)));
						}
					}
					couleurTemp = couleurTemp.divisionNombre(l.getPointsSphere().size());
				}
				else
				{
					// Creation du rayon entre la lumiere et l'objet regarde
					rayonLumiere = Ray(l.getPosition(), pointIntersec.soustraction(l.getPosition()), false);
					// Recherche de l'intersection la plus proche de la lumiere
					intersectionTemp = getIntersec(rayonLumiere);
					// Recuperation de la distance entre l'objet regarde et la lumiere
					float distanceSL = rayonLumiere.getOrigine().soustraction(pointIntersec).norme();
					// Si aucun objet ne se trouve entre l'objet regardé et la lumiere
					if (distanceSL <= intersectionTemp.second)
					{
						normale = s.getNormale(pointIntersec);
						vecL = l.getPosition().soustraction(pointIntersec).normalize();
						float nl = normale.prodScal(vecL);
						if (normale.prodScal(vecL) > 0)
							// Application de la couleur au pixel en fonction de l'albedo, l'intensite de la lumiere, la normale de la sphere à l'intersection,
							// le vecteur entre l'intersection et la lumiere normalisé et la distance entre l'intersection et la lumiere
							couleurTemp = s.getAlbedo().multiplicationNombre((normale.prodScal(vecL)* l.getIntensite()) / pow(distanceSL, 2));
					}
				}
				couleur = couleur.addition(couleurTemp);
			}
		}
	}

	return couleur;
}

/*Fonction qui cherche parmi toutes les spheres de la scene l'objet avec l'intersection la plus proche d'apres un rayon donne*/
std::pair<Sphere, float> Scene::getIntersec(Ray r)
{
	// Initialisation des variables utilisées
	std::pair<Sphere, float> intersection;
	float t = 0;
	float tTemp = 0;
	Vecteur3D couleur = Vecteur3D(0, 0, 0);
	Sphere sphereVue;
	// Parcours de tous les objets de la scene
	for (std::vector<Sphere>::size_type i = 0; i < spheres.size(); i++) {
		Sphere s = spheres.at(i);

		tTemp = s.possedeIntersec(r);

		if (tTemp != 0)
		{
			if (t == 0)
			{
				t = tTemp;
			}

			// Si l'intersection trouvée est plus proche que l'intersection précedemment trouvée
			if (tTemp <= t)
			{
				// Assignation de la nouvelle intersection la plus proche
				sphereVue = s;
				t = tTemp;
			}
		}
	}

	// On renvoie une paire d'objets composée de la sphere la plus proche et de la distance centre celle-ci et l'origine du vecteur
	intersection = std::make_pair(sphereVue, t);

	return intersection;
}