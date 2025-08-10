#include "Material.h"

Material::Material()
{
	// Default values
	shininess = 0;
	for (int i = 0; i < 4; i++)
	{
		colour.push_back(0);
		specular.push_back(0);
		emission.push_back(0);
	}
	
}

Material::~Material()
{
}

void Material::applyMaterial()
{
	// Functions to apply a material to an object before rendering.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour.data());
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());
	glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

