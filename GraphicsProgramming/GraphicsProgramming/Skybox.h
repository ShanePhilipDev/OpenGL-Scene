#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "SOIL.h"
#include <vector>
#include "Vector3.h"
#include "Shape.h"

class Skybox
{
public:
	// Constructor and destructor.
	Skybox();
	~Skybox();

	// Assigns textures to be used for the skybox.
	void setTextures(std::string t, std::string f, std::string ba, std::string l, std::string r, std::string bo) {
		top = SOIL_load_OGL_texture(t.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		front = SOIL_load_OGL_texture(f.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		back = SOIL_load_OGL_texture(ba.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		left = SOIL_load_OGL_texture(l.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		right = SOIL_load_OGL_texture(r.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		bottom = SOIL_load_OGL_texture(bo.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	};

	// Sets the skybox's position to the argument's value (the camera's position).
	void setPosition(Vector3 p)
	{
		position = p;
	};

	// Draws the skybox.
	void renderSkybox();

protected:
	// Variables for holding the skybox's textures and position.
	Vector3 position;
	GLuint top;
	GLuint front;
	GLuint back;
	GLuint left;
	GLuint right;
	GLuint bottom;
};

