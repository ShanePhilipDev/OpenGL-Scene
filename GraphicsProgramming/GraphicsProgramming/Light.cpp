#include "Light.h"

Light::Light(GLenum n, GLfloat(&a)[4], GLfloat(&d)[4], GLfloat(&p)[4], GLfloat(&s)[4], GLfloat(&spot)[3]) : ambient(a), diffuse(d), position(p), specular(s), spotDirection(spot) // Set array pointers.
{
	// Apply argument.
	lightNo = n;
	spotlightBool = false; // Not a spotlight as cutoff and exponent were not given in constructor.

	// Default attenuation values.
	con = 1;
	lin = 0;
	quad = 0;
}

Light::Light(GLenum n, GLfloat (&a)[4], GLfloat (&d)[4], GLfloat (&p)[4], GLfloat(&s)[4], GLfloat (&spot)[3], float c, float e) : ambient(a), diffuse(d), position(p), specular(s), spotDirection(spot) // Set array pointers.
{
	// Apply arguments.
	lightNo = n;
	spotCutoff = c;
	spotExponent = e;
	
	// Set spotlight status to true.
	spotlightBool = true;

	// Default attenuation values.
	con = 1;
	lin = 0;
	quad = 0;
}

Light::~Light()
{
}

// Render the light.
void Light::render()
{
	// Functions to adjust the properties of the light.
	glLightfv(lightNo, GL_AMBIENT, ambient);
	glLightfv(lightNo, GL_DIFFUSE, diffuse);
	glLightfv(lightNo, GL_POSITION, position);
	glLightfv(lightNo, GL_SPECULAR, specular);
	glLightf(lightNo, GL_CONSTANT_ATTENUATION, con);
	glLightf(lightNo, GL_LINEAR_ATTENUATION, lin);
	glLightf(lightNo, GL_QUADRATIC_ATTENUATION, quad);

	if (spotlightBool) // additional functions to be called when the light is a spotlight.
	{
		glLightf(lightNo, GL_SPOT_CUTOFF, spotCutoff);
		glLightfv(lightNo, GL_SPOT_DIRECTION, spotDirection);
		glLightf(lightNo, GL_SPOT_EXPONENT, spotExponent);
	}

	// Enable the light.
	glEnable(lightNo);
}
