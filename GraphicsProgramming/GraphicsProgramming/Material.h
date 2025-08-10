#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <iostream>
#include <vector>

// Class to store information about a material.
class Material
{
public:
	// Constructor and destructor.
	Material();
	~Material();

	// Setter functions.
	void setShininess(GLfloat s) { shininess = s; };
	void setColour(GLfloat x, GLfloat y, GLfloat z) { colour.clear(); colour.push_back(x); colour.push_back(y); colour.push_back(z); colour.push_back(1); };
	void setMaterial(GLfloat x, GLfloat y, GLfloat z) { specular.clear(); specular.push_back(x); specular.push_back(y); specular.push_back(z); specular.push_back(1); };
	void setEmission(GLfloat x, GLfloat y, GLfloat z) { emission.clear(); emission.push_back(x); emission.push_back(y); emission.push_back(z); emission.push_back(1); };

	// Function to be called whenever you want to apply the material to an object.
	void applyMaterial();
	
private:
	// GLfloat value and GLfloat vectors to hold material's properties.
	GLfloat shininess;
	std::vector<GLfloat> colour;
	std::vector<GLfloat> specular;
	std::vector<GLfloat> emission;
};

