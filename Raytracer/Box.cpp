#include "Box.h"
#include "Utils.h"


#pragma region get/set
float Box::getPlanMinX()
{
	return planMinX;
}
void Box::setPlanMinX(float plantMinX)
{
	this->planMinX = plantMinX;
}
float Box::getPlanMaxX()
{
	return planMaxX;
}
void Box::setPlanMaxX(float plantMaxX)
{
	this->planMaxX = plantMaxX;
}
float Box::getPlanMinY()
{
	return planMinY;
}
void Box::setPlanMinY(float plantMinY)
{
	this->planMinY = plantMinY;
}
float Box::getPlanMaxY()
{
	return planMaxY;
}
void Box::setPlanMaxY(float plantMaxY)
{
	this->planMaxY = plantMaxY;
}
float Box::getPlanMinZ()
{
	return planMinZ;
}
void Box::setPlanMinZ(float plantMinZ)
{
	this->planMinZ = plantMinZ;
}
float Box::getPlanMaxZ()
{
	return planMaxZ;
}
void Box::setPlanMaxZ(float plantMaxZ)
{
	this->planMaxZ = plantMaxZ;
}
vector<Sphere> Box::getSpheres()
{
	return spheres;
}
void Box::addSphere(Sphere s)
{
	spheres.push_back(s);
}
vector<Box> Box::getBoites()
{
	return boites;
}
void Box::addBoite(Box b)
{
	boites.push_back(b);
}
#pragma endregion get/set

Box::Box() {}

Box::Box(vector<Sphere> listSpheres)
{
	if (listSpheres.size() > 0)
	{
		bool premiereSphere = true;
		float minX;
		float maxX;
		float minY;
		float maxY;
		float minZ;
		float maxZ;
		for (auto s : listSpheres)
		{
			if (premiereSphere)
			{
				minX = s.getCentre().getX() - s.getRayon();
				maxX = s.getCentre().getX() + s.getRayon();
				minY = s.getCentre().getY() - s.getRayon();
				maxY = s.getCentre().getY() + s.getRayon();
				minZ = s.getCentre().getZ() - s.getRayon();
				maxZ = s.getCentre().getZ() + s.getRayon();
				premiereSphere = false;
			}
			else {
				if (s.getCentre().getX() - s.getRayon() < minX)
					minX = s.getCentre().getX() - s.getRayon();
				if (s.getCentre().getX() + s.getRayon() > maxX)
					maxX = s.getCentre().getX() + s.getRayon();
				if (s.getCentre().getY() - s.getRayon() < minY)
					minY = s.getCentre().getY() - s.getRayon();
				if (s.getCentre().getY() + s.getRayon() > maxY)
					maxY = s.getCentre().getY() + s.getRayon();
				if (s.getCentre().getZ() - s.getRayon() < minZ)
					minZ = s.getCentre().getZ() - s.getRayon();
				if (s.getCentre().getZ() + s.getRayon() > maxZ)
					maxZ = s.getCentre().getZ() + s.getRayon();
			}
			addSphere(s);
		}
		setPlanMinX(minX);
		setPlanMaxX(maxX);
		setPlanMinY(minY);
		setPlanMaxY(maxY);
		setPlanMinZ(minZ);
		setPlanMaxZ(maxZ);

		if (spheres.size() > 1)
		{
			vector<Sphere> spheres1;
			vector<Sphere> spheres2;

			if (valeurAbsolue(planMaxX - planMinX) >= valeurAbsolue(planMaxY - planMinY) && valeurAbsolue(planMaxX - planMinX) >= valeurAbsolue(planMaxZ - planMinZ)) {
				float planX2 = (planMaxX + planMinX) / 2;
				for (auto s : spheres)
				{
					if ((s.getCentre().getX() - s.getRayon()) < planX2)
						spheres1.push_back(s);
					else if ((s.getCentre().getX() + s.getRayon()) > planX2)
						spheres2.push_back(s);
				}
			}
			else if (valeurAbsolue(planMaxY - planMinY) >= valeurAbsolue(planMaxX - planMinX) && valeurAbsolue(planMaxY - planMinY) >= valeurAbsolue(planMaxZ - planMinZ)) {
				float planY2 = (planMaxY + planMinY) / 2;
				for (auto s : spheres)
				{
					if ((s.getCentre().getY() - s.getRayon()) < planY2)
						spheres1.push_back(s);
					else if ((s.getCentre().getY() + s.getRayon()) > planY2)
						spheres2.push_back(s);
				}
			}
			else if (valeurAbsolue(planMaxZ - planMinZ) >= valeurAbsolue(planMaxY - planMinY) && valeurAbsolue(planMaxZ - planMinZ) >= valeurAbsolue(planMaxX - planMinX)) {
				float planZ2 = (planMaxZ + planMinZ) / 2;
				for (auto s : spheres)
				{
					if ((s.getCentre().getZ() - s.getRayon()) < planZ2)
						spheres1.push_back(s);
					else if ((s.getCentre().getZ() + s.getRayon()) > planZ2)
						spheres2.push_back(s);
				}
			}

			if (spheres1.size() > 0) {
				Box b1 = Box(spheres1);
				addBoite(b1);
			}
			if (spheres2.size() > 0) {
				Box b2 = Box(spheres2);
				addBoite(b2);
			}
		}
	}
}

/*Recherche l'intersection la plus proche sur une box. S'il y en a une, renvoie le t.*/
float Box::getIntersection(Ray r)
{
	float tMinX = -1;
	float tMaxX = -1;
	float tMinY = -1;
	float tMaxY = -1;
	float tMinZ = -1;
	float tMaxZ = -1;
	float t = -1;

	t = (planMinX - r.getOrigine().getX()) / r.getDirection().getX();
	if (t*r.getDirection().getY() > tMinY && t*r.getDirection().getY() < tMaxY && t*r.getDirection().getZ() > tMinZ && t*r.getDirection().getZ() < tMaxZ && t > 0)
		tMinX = t;
	t = -1;

	t = (planMaxX - r.getOrigine().getX()) / r.getDirection().getX();
	if (t*r.getDirection().getY() > tMinY && t*r.getDirection().getY() < tMaxY && t*r.getDirection().getZ() > tMinZ && t*r.getDirection().getZ() < tMaxZ && t > 0)
		tMaxX = t;
	t = -1;


	t = (planMinY - r.getOrigine().getY()) / r.getDirection().getY();
	if (t*r.getDirection().getX() > tMinX && t*r.getDirection().getX() < tMaxX && t*r.getDirection().getZ() > tMinZ && t*r.getDirection().getZ() < tMaxZ && t > 0)
		tMinY = t;
	t = -1;

	t = (planMaxY - r.getOrigine().getY()) / r.getDirection().getY();
	if (t*r.getDirection().getX() > tMinX && t*r.getDirection().getX() < tMaxX && t*r.getDirection().getZ() > tMinZ && t*r.getDirection().getZ() < tMaxZ && t > 0)
		tMaxY = t;
	t = -1;

	t = (planMinZ - r.getOrigine().getZ()) / r.getDirection().getZ();
	if (t*r.getDirection().getX() > tMinX && t*r.getDirection().getX() < tMaxX && t*r.getDirection().getY() > tMinY && t*r.getDirection().getY() < tMaxY && t > 0)
		tMinZ = t;
	t = -1;

	t = (planMaxZ - r.getOrigine().getZ()) / r.getDirection().getZ();
	if (t*r.getDirection().getX() > tMinX && t*r.getDirection().getX() < tMaxX && t*r.getDirection().getY() > tMinY && t*r.getDirection().getY() < tMaxY && t > 0)
		tMaxZ = t;
	
	t = -1;

	vector<float> listeT;
	listeT.push_back(tMinX);
	listeT.push_back(tMaxX);
	listeT.push_back(tMinY);
	listeT.push_back(tMaxY);
	listeT.push_back(tMinZ);
	listeT.push_back(tMaxZ);

	for (auto tTemp : listeT)
	{
		if (t == -1)
			t = tTemp;
		else if (tTemp < t && tTemp > 0)
		{
			t = tTemp;
		}
	}

	return t;
}


