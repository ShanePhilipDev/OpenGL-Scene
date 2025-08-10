#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "SOIL.h"
#include <vector>
#include "Shadow.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Skybox.h"
#include "Shape.h"
#include "Animation.h"
#include "Material.h"

class ObjectManager
{
public:
	// Constructor and destructor
	ObjectManager();
	~ObjectManager();

	// Function to be called in the scene's constructor. Initialises all the variables and values needed for each object.
	void initialise();

	// Generate the vertex arrays for stored shapes.
	void generateShapes();

	// Load all of the needed textures.
	void loadTextures(); 

	// Function to make loading and assigning textures simpler.
	void loadTexture(std::string s, GLuint &t);

	// Load all of the needed models.
	void loadModels();

	// Create all of the needed materials.
	void setMaterials();

	// Set the positions for certain objects in the scene.
	void setPositions();

	// Update and handle input functions.
	void update(float dt);
	void handleInput(float dt);

	// Functions to set needed pointers.
	void setInput(Input* in) { input = in; };
	void setCamera(Camera* c) { camera = c; };

	// Function to render every object.
	void render();

	// Functions to render each individual part of the scene.
	void renderShapeExamples();
	void renderComputer();
	void renderSolarSystem();
	void renderPlayer();
	void renderReflection();
	void renderReflectionPlane();
	void renderEarth();
	void renderMoon();
	void renderSpaceship();
	void renderSpotlightShadow();
	void renderTransparentCubes();
	void renderPlayerShadow();
	void renderBase();
	void renderBaseWindows();

private:

	Shape shapeManager; // shape object used for calling general shape functions such as renderCube, renderSphere, etc. Other shape objects will generate and store vertex data, then render them using vertex arrays.
	
	// Rest of the shapes are objects generated and used within the scene.
	Shape deskTop;
	Shape deskLeg;
	Shape computer;
	Shape mouse;
	Shape keyboard;
	Shape monitor;
	Shape chairLeg;
	Shape chairSeat;
	Shape chairBack;
	Shape sun;
	Shape planet;
	Shape moonFloor;
	Shape tableLeg;
	Shape tableTop;
	Shape plinth;
	Shape wallTall;
	Shape wallShort;
	Shape door;
	Shape window;
	Shape skylight;

	// Skybox for the scene
	Skybox skybox;

	// Animated plane object and related variables
	Animation animation;
	int currentAnimation;
	bool computerToggle;

	// GIF Textures
	GLuint eyebrowsGIF;
	GLuint birdGIF;
	GLuint tomGIF;

	// Models
	Model player;
	Model spaceship;
	Model corgi;

	// Variables relating to shadows
	Shadow shadow;
	float shadowMatrix[16];
	std::vector<GLfloat> shadowVerts;
	std::vector<GLfloat> shadowNormals;
	std::vector<GLfloat> shadowTexCoords;

	// Textures
	GLuint checkeredTexture;
	GLuint woodTexture;
	GLuint metalTexture;
	GLuint metalTexture2; 
	GLuint reflectionWallTexture;
	GLuint reflectionBarsTexture;
	GLuint shadowTexture;
	GLuint earthTexture;
	GLuint moonTexture;
	GLuint flagTexture;
	GLuint wallTexture;
	GLuint transparentCubeTexture;
	GLuint doorTexture;
	GLuint windowTexture;

	// Positions
	Vector3 computerPosition;
	Vector3 playerPosition;
	Vector3 reflectionPosition;
	Vector3 spaceshipPosition;
	Vector3 spotlightPosition;
	Vector3 cubesPosition;

	// Player variables
	float playerHeight;
	float playerRotation;

	// Variable to store the size of the base
	float baseSize;

	// Materials for planets
	Material mercury;
	Material venus;
	Material earth;
	Material moon;
	Material mars;
	Material jupiter;
	Material saturn;
	Material saturnRing;
	Material uranus;
	Material neptune;
	Material pluto;

	// Values for rotating objects
	float rotate;
	float lightRotate;

	// Pointers for input and camera
	Input* input;
	Camera* camera;
};

