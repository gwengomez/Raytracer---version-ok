#pragma once
#ifndef VECTEUR3D_H
#define VECTEUR3D_H
#include <string>

class Vecteur3D
{
private:
	
	float x;
	float y;
	float z;

public:

	Vecteur3D(float x, float y, float z);
	Vecteur3D();
	
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);
	Vecteur3D addition(Vecteur3D vec3);
	Vecteur3D soustraction(Vecteur3D vec3);
	Vecteur3D multiplicationTermes(Vecteur3D vec3);
	Vecteur3D divisionTermes(Vecteur3D vec3);
	Vecteur3D multiplicationNombre(float x);
	Vecteur3D divisionNombre(float x);
	float norme();
	float normeCarre();
	Vecteur3D normalize();
	float prodScal(Vecteur3D vec3);
	Vecteur3D prodVect(Vecteur3D vec3);
};
#endif
