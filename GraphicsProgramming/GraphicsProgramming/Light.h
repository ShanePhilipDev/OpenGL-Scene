#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "SOIL.h"
#include <vector>

class Light
{
public:
	// Constructors and destructor for lights. Parameters are the light enum, pointers to the light's arrays, and the spotlight cutoff and exponent if required.
	Light(GLenum n, GLfloat (&a)[4], GLfloat (&d)[4], GLfloat (&p)[4], GLfloat(&specular)[4], GLfloat(&spot)[3]); // Normal light.
	Light(GLenum n, GLfloat (&a)[4], GLfloat (&d)[4], GLfloat (&p)[4], GLfloat(&specular)[4], GLfloat(&spot)[3], float c, float e); // Spotlight.
	~Light();

	// Set the attenuation of a light.
	void setAttenuation(float c, float l, float q) { con = c; lin = l; quad = q; };

	// Returns which light enum is being used.
	GLenum getLight() { return lightNo; };

	// Render the light.
	void render();

private:
	// Pointers to the light arrays.
	GLfloat (&ambient)[4];
	GLfloat (&diffuse)[4];
	GLfloat (&position)[4];
	GLfloat (&specular)[4];
	GLfloat (&spotDirection)[3];

	// Light enum.
	GLenum lightNo;

	// Spotlight variables.
	float spotCutoff;
	float spotExponent;
	bool spotlightBool;
	
	// Attenuation values.
	float con;
	float lin;
	float quad;
	
};

