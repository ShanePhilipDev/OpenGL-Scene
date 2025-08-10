#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialise scene variables
	// Pass input pointer to camera and object manager.
	camera.setInput(input);
	objectManager.setInput(input);

	// Pass pointer to camera to the object manager.
	objectManager.setCamera(&camera);
	
	// Initialise all the variables in the object manager.
	objectManager.initialise();

	// Wireframe mode is disabled at the start.
	wireToggle = false;
}

void Scene::handleInput(float dt)
{
	// Handle user input
	// Set the camera's window and handle input.
	camera.setWindow(width, height);
	camera.handleInput(dt);

	// Handle input relating to object interaction.
	objectManager.handleInput(dt);

	// Toggle wireframe mode.
	if (input->isKeyDown('y') && !wireToggle)
	{
		input->setKeyUp('y');
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		wireToggle = !wireToggle;
	}
	else if (input->isKeyDown('y') && wireToggle)
	{
		input->setKeyUp('y');
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		wireToggle = !wireToggle;
	}

}

void Scene::update(float dt)
{
	// update scene related variables.

	// Update the camera and object manager.
	camera.update(dt);
	objectManager.update(dt);

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	camera.setCamera();

	// Render geometry/scene here -------------------------------------

	// Render objects.
	objectManager.render();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Move mouse to the middle of the screen when resized to prevent unexpected movement.
	input->setMouseX(width / 2);
	input->setMouseY(height / 2);

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	glDisable(GL_LIGHTING); // lighting disabled and then re-enabled to have the text coloured. If not disabled the text is black.
	// Render current mouse position, frames per second and the controls.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, "Controls:");
	displayText(-1.f, 0.78f, 1.f, 0.f, 0.f, "FPP: W: Move Forwards, S: Move Backwards, A: Move Left, D: Move Right, Mouse: Look Around");
	displayText(-1.f, 0.72f, 1.f, 0.f, 0.f, "TPP: Mouse: Rotate Around Model");
	displayText(-1.f, 0.66f, 1.f, 0.f, 0.f, "Free Camera: Q: Rotate Left, E: Rotate Right, Z+W: Move Up, Z+S: Move Down, X+W: Rotate Up, X+S: Rotate Down, X+A: Roll Left, X+D: Roll Right, Mouse: Look Around (Unrestricted)");
	displayText(-1.f, 0.60f, 1.f, 0.f, 0.f, "Other: C: Change Camera, R: Reset Camera, T: Toggle Mouse, Y: Toggle Wireframe Mode, F: Turn On PC (must be near PC), N: Next Animation on PC (must be near PC)");
	glEnable(GL_LIGHTING);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
