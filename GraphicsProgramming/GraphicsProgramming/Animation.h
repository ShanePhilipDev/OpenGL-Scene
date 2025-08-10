#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <iostream>
#include <vector>
#include "SOIL.h"

// This class allows you to apply an animated texture to a plane. The class uses a static image file that contains square frames in an equal amount of rows and columns.
class Animation
{
public:
	// Constructor and destructor
	Animation();
	~Animation();

	// Function to update the animation's frame
	void update(float dt);

	// Functions to set the texture of the animation
	void setTexture(std::string s);
	void setTexture(GLuint t) { texture = t; };

	// Getter and setter functions for playing the animation
	void setPlaying(bool) {	playing = true; };
	bool getPlaying() { return playing; };

	// Function to set up a new animation by passing in a texture, the amount of rows/columns, and the time it takes for one frame to play.
	void initialise(GLuint tex, int s, float t);

	// Function to render the animation.
	void render();

private:

	// Stores texture file
	GLuint texture;

	// Stores information about the current animation
	bool playing;
	float speed;
	float playTime;
	int currentRow;
	int currentColumn;
	int segments;
	float segmentSize;

	// The vertex arrays required to render the animation
	std::vector<float> vertex, normals, texCoords;
};

