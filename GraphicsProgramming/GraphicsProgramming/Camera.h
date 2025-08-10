#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include "Vector3.h"

// Defining pi for rotation calculations
#define PI 3.1415

class Camera
{
public:
	// Constructors and destructor
	Camera(); // to construct with default values
	Camera(Vector3 p, Vector3 l, Vector3 u); // construct with vector3s for position, lookAt and up.
	Camera(float pX, float pY, float pZ, float lX, float lY, float lZ, float uX, float uY, float uZ); // construct with floats for position, lookAt and up.
	~Camera();

	// Functions to update camera variables and handle input
	void update(float dt);
	void handleInput(float dt);

	// Enumerator for the camera modes - First person perspective, third person perspective, and free camera.
	enum class Mode { FPP = 0, TPP = 1, FREE = 2 };
	void setMode(Mode m) { mode = m; };
	Mode getMode() { return mode; };

	// Getter functions
	Vector3 getPosition();
	Vector3 getLookAt();
	Vector3 getUp();
	float getPitch();
	float getYaw();
	float getRoll();

	// Setter functions (with overloads)
	void setPosition(Vector3 p);
	void setPosition(float pX, float pY, float pZ);
	void setLookAt(Vector3 l);
	void setLookAt(float lX, float lY, float lZ);
	void setUp(Vector3 u);
	void setUp(float uX, float uY, float uZ);
	void setBoundary(float s) { boundary = s; };
	void setPlayerHeight(float h) { playerHeight = h; };

	// Functions to pass the position, look at, and up direction to gluLookAt.
	void setCamera();
	void setCamera(Vector3 p, Vector3 l, Vector3 u);
	
	// Function to set input
	void setInput(Input* in) { input = in; };

	// Function to set window width and height
	void setWindow(int w, int h) { width = w; height = h; };

	// Functions to control camera movement
	void moveForward(float dt);
	void moveBackward(float dt);
	void moveUp(float dt);
	void moveDown(float dt);
	void moveRight(float dt);
	void moveLeft(float dt);
	void rotateUp(float dt);
	void rotateDown(float dt);
	void rotateRight(float dt);
	void rotateLeft(float dt);
	void rollLeft(float dt);
	void rollRight(float dt);

	// Function to perform calculations for rotation
	void rotate();

private:
	// Vector3 variables to hold the vectors needed for the camera
	Vector3 position;
	Vector3 lookAt;
	Vector3 up;
	Vector3 forward;
	Vector3 right;

	float pitch; // rotation around x-axis
	float yaw; // rotation around y-axis
	float roll; // rotation around z-axis

	int width; // window width
	int height; // window height

	float boundary; // boundary length to stop the camera from moving out of the base
	float playerHeight; // player height for moving the camera to the correct height

	float speed; // mouse rotation speed
	float movementSpeed; // speed at which the camera moves
	float tpSpeed; // mouse rotation speed for the third person camera
	float tpRadius; // the radius at which the third person camera orbits

	bool mouseToggle; // bool variable for toggling whether the mouse is being used to rotate the camera

	Input* input; // so that the camera can recieve input

	Mode mode; // stores which mode the camera is currently set to

};

