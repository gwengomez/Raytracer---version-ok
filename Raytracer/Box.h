#pragma once
#ifndef BOX_H
#define BOX_H
#include <vector>
#include "Sphere.h"
#include "Ray.h"

using namespace std;

class Box
{
private:

	float planMinX;
	float planMaxX;
	float planMinY;
	float planMaxY;
	float planMinZ;
	float planMaxZ;
	vector<Sphere> spheres;
	vector<Box> boites;

public:

	float getPlanMinX();
	void setPlanMinX(float plantMinX);
	float getPlanMaxX();
	void setPlanMaxX(float plantMaxX);
	float getPlanMinY();
	void setPlanMinY(float plantMinY);
	float getPlanMaxY();
	void setPlanMaxY(float plantMaxY);
	float getPlanMinZ();
	void setPlanMinZ(float plantMinZ);
	float getPlanMaxZ();
	void setPlanMaxZ(float plantMaxZ);
	vector<Sphere> getSpheres();
	void addSphere(Sphere s);
	vector<Box> getBoites();
	void addBoite(Box b);
	Box();
	Box(vector<Sphere> listSpheres);
	float getIntersection(Ray r);

};
#endif