#include "ObjectManager.h"

// Arrays to hold the properties of each light.
GLfloat spotDirection[] = { 0.0f, -1.0f, 0.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat pcAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat pcDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat pcPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat sunAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat sunDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat sunPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat spotAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat spotDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat spotPosition[] = { 0.05f, 3.0f, 0.05f, 1.0f };

// Constructing 3 lights to be rendered in the scene.
Light pcLight(GL_LIGHT0, pcAmbient, pcDiffuse, pcPosition, lightSpecular, spotDirection);
Light sunLight(GL_LIGHT1, sunAmbient, sunDiffuse, sunPosition, lightSpecular, spotDirection);
Light spotLight(GL_LIGHT2, spotAmbient, spotDiffuse, spotPosition, lightSpecular, spotDirection, 15.0f, 45.0f);


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::initialise()
{
	// Load, set and generate anything needed in the scene.
	loadTextures();
	loadModels();
	setMaterials();
	generateShapes();
	setPositions();

	// Defines a plane to be used when rendering/calculating shadows.
	shadowVerts = { -1.f, 0.f, -1.f,
					-1.f, 0.f, 1.f,
					1.f, 0.f, 1.f,
					1.f, 0.f, -1.f };

	shadowNormals = {0.0, 1.0, 0.0,
					0.0, 1.0, 0.0,
					0.0, 1.0, 0.0,
					0.0, 1.0, 0.0 };

	shadowTexCoords = { 0.0, 0.0,
						0.0, 1.0,
						1.0, 1.0,
						1.0, 0.0 };

	// Set default values.
	pcLight.setAttenuation(1, 0.15, 0.15);
	currentAnimation = 1;
	computerToggle = false;
	rotate = 0;
	playerHeight = 1.9;
	baseSize = 50;
	camera->setBoundary(baseSize / 2);
	camera->setPlayerHeight(1.9);
}

// Generates shapes and assigns them textures if needed.
void ObjectManager::generateShapes()
{
	deskLeg.setTexture(woodTexture);
	deskLeg.generateCuboid(0.1, 0.1, 1, 1, 1, 10);

	deskTop.setTexture(woodTexture);
	deskTop.generateCuboid(2, 1, 0.1, 10, 10, 1);

	computer.setTexture(metalTexture2);
	computer.generateCuboid(0.6, 0.2, 0.5, 6, 2, 5);

	mouse.setTexture(metalTexture2);
	mouse.generateCuboid(0.1, 0.05, 0.03, 1, 5, 3);

	keyboard.setTexture(metalTexture2);
	keyboard.generateCuboid(0.2, 0.5, 0.02, 2, 5, 2);

	monitor.setTexture(metalTexture);
	monitor.generateCuboid(1, 0.02, 0.75, 10, 2, 5);

	chairLeg.setTexture(woodTexture);
	chairLeg.generateCuboid(0.1, 0.1, 0.5, 1, 1, 5);

	chairSeat.setTexture(woodTexture);
	chairSeat.generateCuboid(0.5, 0.5, 0.1, 5, 5, 1);

	chairBack.setTexture(woodTexture);
	chairBack.generateCuboid(0.1, 0.5, 0.75, 1, 5, 5);

	sun.generateSphere(3, 20);
	planet.generateSphere(1, 20);

	moonFloor.setTexture(moonTexture);
	moonFloor.generatePlane(250, 250, 50, 50);

	tableLeg.setTexture(metalTexture);
	tableLeg.generateCuboid(0.1, 0.1, 1, 1, 1, 10);

	tableTop.setTexture(metalTexture);
	tableTop.generateCuboid(1, 1, 0.1, 50, 50, 1);

	plinth.setTexture(wallTexture);
	plinth.generateCuboid(0.5, 0.5, 1, 1, 1, 2);

	wallTall.setTexture(wallTexture);
	wallTall.generateCuboid(50, 0.2, 4.5, 10, 1, 3);

	wallShort.setTexture(wallTexture);
	wallShort.generateCuboid(50, 0.2, 1.5, 10, 1, 1);

	door.setTexture(doorTexture);
	door.generatePlane(3, 3, 1, 1);

	window.setTexture(windowTexture);
	window.generatePlane(50, 1.5, 1, 1);

	skylight.setTexture(windowTexture);
	skylight.generatePlane(50, 50, 1, 1);
}

// Load all of the textures used in the scene.
void ObjectManager::loadTextures()
{
	// Normal textures
	loadTexture("gfx/checked.png", checkeredTexture);
	loadTexture("gfx/wood.png", woodTexture);
	loadTexture("gfx/metal.png", metalTexture);
	loadTexture("gfx/metal2.jpg", metalTexture2);
	loadTexture("gfx/bars.png", reflectionBarsTexture);
	loadTexture("gfx/bricks.jpg", reflectionWallTexture);
	loadTexture("gfx/imposter.png", shadowTexture);
	loadTexture("gfx/earth.jpg", earthTexture);
	loadTexture("gfx/moon.jpg", moonTexture);
	loadTexture("gfx/scotland.png", flagTexture);
	loadTexture("gfx/hexagonTile.png", wallTexture);
	loadTexture("gfx/transparentCube.png", transparentCubeTexture);
	loadTexture("gfx/window.png", windowTexture);
	loadTexture("gfx/door.png", doorTexture);

	// Animation textures
	loadTexture("gfx/eyebrowsgif.png", eyebrowsGIF);
	loadTexture("gfx/birdgif.png", birdGIF);
	loadTexture("gfx/tomgif.png", tomGIF);
}

// Function that assigns a specified texture (using a string of the texture's address) to the specified texture object.
void ObjectManager::loadTexture(std::string s, GLuint &t)
{
	t = SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

// Load all of the models used in the scene.
void ObjectManager::loadModels()
{
	player.load("models/skeleton2.obj", "models/skeleton2.png");
	spaceship.load("models/spaceship.obj", "models/spaceship.jpg");
	corgi.load("models/corgi2.obj", "models/corgi2black.png");
}

// Setting up all of the planet materials. Only setting colour aspect of the materials, specular/shininess/emissions not needed.
void ObjectManager::setMaterials()
{
	mercury.setColour(0.75, 0.75, 0.75);
	venus.setColour(1, 1, 0.93);
	earth.setColour(0, 0.41, 0.58);
	moon.setColour(0.75, 0.75, 0.75);
	mars.setColour(1.0, 0.27, 0.0);
	jupiter.setColour(1.0, 0.99, 0.82);
	saturn.setColour(0.94, 0.90, 0.55);
	saturnRing.setColour(0.74, 0.72, 0.42);
	uranus.setColour(0.68, 0.85, 0.90);
	neptune.setColour(0.12, 0.56, 1.00);
	pluto.setColour(0.5, 0.5, 0.5);
}

// Setting the position for some objects.
void ObjectManager::setPositions()
{
	computerPosition.set(0, 0, -20);
	playerPosition.set(0, 0, 0);
	reflectionPosition.set(24.999, 0, 15);
	spaceshipPosition.set(0, 0, 35);
	spotlightPosition.set(20, 0, 0);
	cubesPosition.set(0, 0, 20);
}

void ObjectManager::update(float dt)
{
	// Move skybox to the camera's position.
	skybox.setPosition(camera->getPosition());

	// Update the animated texture.
	animation.update(dt);

	// Used as a base variable for various rotations throughout the scene.
	rotate += 10 * dt;

	// Determines speed at which the spotlight rotates.
	lightRotate = dt;

	// glRotate doesn't affect the light position array used when generating a shadow matrix, so the following code manually rotates a light around the y axis so that this is considered in shadow generation.
	float x = spotPosition[0];
	float z = spotPosition[2];
	spotPosition[0] = x * cos(lightRotate) + z * sin(lightRotate);
	spotPosition[2] = -x * sin(lightRotate) + z * cos(lightRotate);
	
}

void ObjectManager::handleInput(float dt)
{
	// When the player presses 'F' and is within 3 units of the computer's position...
	if (input->isKeyDown('f') && abs(computerPosition.x - playerPosition.x) < 3 && abs(computerPosition.z - playerPosition.z) < 3)
	{
		input->setKeyUp('f');
		// Turn on the computer if it is off, turn off the computer if it is on.
		computerToggle = !computerToggle;
		animation.setPlaying(!animation.getPlaying()); // stops the animation from progressing when the computer is off.
		if (!computerToggle)
		{
			glDisable(pcLight.getLight()); // the computer will not emit light when it is off.
		}
		else
		{
			glEnable(pcLight.getLight()); // the computer will emit light when it is on.
		}
	}

	// When the player presses 'N' and is within 3 units of the computer's position...
	if (input->isKeyDown('n') && computerToggle && abs(computerPosition.x - playerPosition.x) < 3 && abs(computerPosition.z - playerPosition.z) < 3)
	{
		input->setKeyUp('n');
		// Increment the current animation variable, loops back to 1 if it exceeds 3.
		currentAnimation += 1;
		if (currentAnimation > 3)
		{
			currentAnimation = 1;
		}

		switch (currentAnimation)
		{
		case 1:
			// Setting up the Emilia Clarke stabilised eyebrows GIF/animation. Has 9 rows/columns and each frame lasts for 0.03 seconds.
			animation.initialise(eyebrowsGIF, 9, 0.03);
			break;
		case 2:
			// Setting up the bird with arms GIF/animation. Has 6 rows/columns and each frame lasts for 0.1 seconds.
			animation.initialise(birdGIF, 6, 0.1);
			break;
		case 3:
			// Setting up the Tom DeLonge reaction GIF/animation. Has 5 rows/columns and each frame lasts for 0.064 seconds.
			animation.initialise(tomGIF, 5, 0.064);
		default:
			break;
		}
	}
}

// Renders each part of the scene.
void ObjectManager::render()
{
	skybox.renderSkybox();
	renderShapeExamples();
	renderComputer();
	renderSolarSystem();
	renderPlayer();
	renderReflection();
	renderMoon();
	renderPlayerShadow(); // rendered after the moon floor is rendered due to transparency render order.
	renderEarth();
	renderSpaceship();
	renderSpotlightShadow();
	renderBase();

	// These have the most transparency so are rendered last.
	renderTransparentCubes();
	renderBaseWindows();
}

// Showcases 1 pre-defined shape and 4 procedurally generated shapes that have been lit and textured.
void ObjectManager::renderShapeExamples()
{
	glPushMatrix();
		// Applies a checkered texture to each object to show how they are textured.
		glBindTexture(GL_TEXTURE_2D, checkeredTexture);

		// Applying transformations to order then render the objects.
		glTranslatef(0, 1, -5);
		shapeManager.renderCube();
		glTranslatef(-1, 0, 2.5);
		shapeManager.renderCuboid(2, 2, 1, 2, 2, 1);
		glTranslatef(1, 0, 4);
		shapeManager.renderCylinder(1, 2, 50);
		glTranslatef(0, 0, 2);
		shapeManager.renderDisc(1, 50);
		glTranslatef(0, 0, 2);
		shapeManager.renderSphere(1, 50);
	glPopMatrix();
}

// A mini scene with a chair, desk, computer and monitor that displays an animated image.
void ObjectManager::renderComputer()
{
	glPushMatrix();
		// Move into position and flip the direction it is facing.
		glTranslatef(computerPosition.x, computerPosition.y, computerPosition.z);
		glRotatef(180, 0, 1, 0);

		// Render desk
		glPushMatrix();
			glTranslatef(-0.5, 1, -0.5);
			deskLeg.render();
			glTranslatef(1.9, 0, 0);
			deskLeg.render();
			glTranslatef(0, 0, 0.9);
			deskLeg.render();
			glTranslatef(-1.9, 0, 0);
			deskLeg.render();
			glTranslatef(0, 0, -0.9);
			deskTop.render();

			// Render PC
			glPushMatrix();
				glTranslatef(0.25, 0.5, 0.75);
				glRotatef(90, 0, 1, 0);
				computer.render();
			glPopMatrix();

			// Render Mouse
			glPushMatrix();
				glTranslatef(0.75, 0.03, 0.35);
				glRotatef(90, 0, 1, 0);
				mouse.render();
			glPopMatrix();

			// Render Keyboard
			glPushMatrix();
				glTranslatef(1, 0.02, 0.45);
				glRotatef(90, 0, 1, 0);
				keyboard.render();
			glPopMatrix();

			// Render Monitor
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, metalTexture);
				glTranslatef(1.25, 0.02, 0.75);
				shapeManager.renderCylinder(0.15, 0.02, 20);
				glTranslatef(0, 0.06, 0.05);
				shapeManager.renderCylinder(0.02, 0.06, 20);
				glTranslatef(-0.5, 0.75, -0.02);
				monitor.render();

				// Render animated plane
				if (computerToggle)
				{
					glPushMatrix();
						glRotatef(180, 0, 1, 0);
						glTranslatef(-0.5, -0.35, -0.4999);
						glScalef(0.5, 0.35, 0.5);

						glDisable(GL_LIGHTING); // the idea is that screen will be emitting a lot of light, so lighting won't be needed on the screen itself.
						animation.render(); 
						glEnable(GL_LIGHTING);

						// Render light
						glPushMatrix();
							glTranslatef(0, 0, 1.1);
							pcLight.render();
							//shapeManager.renderSphere(0.1, 20); // sphere to show light's position
						glPopMatrix();
					glPopMatrix();
				}
			glPopMatrix();
		glPopMatrix();

		// Render chair
		glPushMatrix();
			glTranslatef(0.5, 0, -1);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(-0.5, 0.5, -0.5);
			chairLeg.render();
			glTranslatef(0.4, 0, 0);
			chairLeg.render();
			glTranslatef(0, 0, 0.4);
			chairLeg.render();
			glTranslatef(-0.4, 0, 0);
			chairLeg.render();
			glTranslatef(0, 0, -0.4);
			chairSeat.render();
			glTranslatef(0, 0.75, 0);
			chairBack.render();
		glPopMatrix();
	glPopMatrix();
}

// A model of our solar system floating above the base. This showcases lighting, materials and heirarchical modelling.
void ObjectManager::renderSolarSystem()
{
	glPushMatrix();
		// Rotates the sun around the centre of the scene.
		glRotatef(rotate, 0, 1, 0);
		glTranslatef(15, 10, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0, 0.65, 0.0);

		// Renders the sun and lighting
		glDisable(GL_LIGHTING); // this sphere represents a light source, therefore should not be affected by other sources of light.
		sun.render();
		glEnable(GL_LIGHTING);
		sunLight.render();

		// Each planet is rotated around the sun at different speeds, is equally spaced out from each other and then scaled to size before being rendered. 

		// Mercury
		glPushMatrix();
			glRotatef(rotate * 4.8, 0, 1, 0);
			glTranslatef(5, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			mercury.applyMaterial();
			planet.render();
		glPopMatrix();

		// Venus
		glPushMatrix();
			glRotatef(rotate * 3.5, 0, 1, 0);
			glTranslatef(10, 0, 0);
			glScalef(0.4, 0.4, 0.4);
			venus.applyMaterial();
			planet.render();
		glPopMatrix();

		// Earth
		glPushMatrix();
			glRotatef(rotate * 3, 0, 1, 0);
			glTranslatef(15, 0, 0);
			glScalef(0.5, 0.5, 0.5);
			earth.applyMaterial();
			planet.render();

			// Earth's moon
			glPushMatrix();
				glRotatef(rotate * 0.1, 0, 1, 0);
				glTranslatef(2, 0, 0);
				glScalef(0.15, 0.15, 0.15);
				moon.applyMaterial();
				planet.render();
			glPopMatrix();

		glPopMatrix();

		// Mars
		glPushMatrix();
			glRotatef(rotate * 2.4, 0, 1, 0);
			glTranslatef(20, 0, 0);
			glScalef(0.25, 0.25, 0.25);
			mars.applyMaterial();
			planet.render();
		glPopMatrix();

		// Jupiter
		glPushMatrix();
			glRotatef(rotate * 1.3, 0, 1, 0);
			glTranslatef(25, 0, 0);
			glScalef(2, 2, 2);
			jupiter.applyMaterial();
			planet.render();
		glPopMatrix();

		// Saturn
		glPushMatrix();
			glRotatef(rotate * 0.9, 0, 1, 0);
			glTranslatef(30, 0, 0);
			glScalef(1.75, 1.75, 1.75);
			saturn.applyMaterial();
			planet.render();

			// Saturn's ring
			glPushMatrix();
				glRotatef(90, 1, 0, 0);
				saturnRing.applyMaterial();
				shapeManager.renderDisc(1.5, 20);
			glPopMatrix();

		glPopMatrix();

		// Uranus
		glPushMatrix();
			glRotatef(rotate * 0.7, 0, 1, 0);
			glTranslatef(35, 0, 0);
			glScalef(1.0, 1.0, 1.0);
			uranus.applyMaterial();
			planet.render();
		glPopMatrix();

		// Neptune
		glPushMatrix();
			glRotatef(rotate * 0.5, 0, 1, 0);
			glTranslatef(40, 0, 0);
			glScalef(0.9, 0.9, 0.9);
			neptune.applyMaterial();
			planet.render();
		glPopMatrix();

		// Pluto
		glPushMatrix();
			glRotatef(rotate * 0.4, 0, 1, 0);
			glTranslatef(45, 0, 0);
			glScalef(0.05, 0.05, 0.05);
			pluto.applyMaterial();
			planet.render();
		glPopMatrix();

		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
}

// This function renders the player model and performs any manipulations needed on the player/camera.
void ObjectManager::renderPlayer()
{
	glPushMatrix();
		// If in first person mode then...
		if (camera->getMode() == Camera::Mode::FPP)
		{
			playerPosition = camera->getPosition(); // Set the player's position to the camera's current position.
			glTranslatef(playerPosition.x, playerPosition.y, playerPosition.z); // Move model to player's position.
			playerRotation = -camera->getYaw() + 90;
			glRotatef(playerRotation, 0, 1, 0); // Rotate model as the camera rotates.
			glTranslatef(-0.2, -playerHeight, 0); // Move so that the camera is at the right height and not inside the model.
		}
		else if (camera->getMode() == Camera::Mode::TPP) // If in third person mode...
		{
			glTranslatef(playerPosition.x, 0, playerPosition.z); // Move model into position.
			camera->setLookAt(playerPosition.x, playerPosition.y, playerPosition.z); // Set the camera to look at the model.
			glRotatef(playerRotation, 0, 1, 0); // Rotate player model to face the correct direction.
		}
		else if (camera->getMode() == Camera::Mode::FREE) // If in free camera mode...
		{
			glTranslatef(playerPosition.x, 0, playerPosition.z); // Move model into position.
			glRotatef(playerRotation, 0, 1, 0); // Rotate player model to face the correct direction.
		}

		// Render the player model.
		player.render();
	glPopMatrix();
}

// This function renders a reflection of the player's model and shadow into a mini dungeon cell scene using a stencil buffer.
void ObjectManager::renderReflection()
{
	// Render reflection
	glPushMatrix();
		// Move into position.
		glTranslatef(reflectionPosition.x, reflectionPosition.y, reflectionPosition.z);
		glRotatef(90, 0, 1, 0);

		glPushMatrix();
			// Set up stencil buffer
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS, 1, 1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glDisable(GL_DEPTH_TEST);
			
			// Set stencil buffer plane
			renderReflectionPlane();

			glEnable(GL_DEPTH_TEST);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glStencilFunc(GL_EQUAL, 1, 1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			glDisable(GL_LIGHTING);

			// Render a cube with its front face culled to act as the walls of the dungeon cell.
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, reflectionWallTexture);
				glScalef(1.5, 1.5, 1.5);
				glTranslatef(1, 1, 1);
				shapeManager.renderCube();
			glPopMatrix();
			glDisable(GL_CULL_FACE);

			// Render a reflection of the player model and its shadow.
			glPushMatrix();
				glTranslatef(0, 0, 0);
				glRotatef(90, 0, 1, 0);
				glScalef(1.0f, 1.0f, -1.0f);
				float x = playerPosition.x - reflectionPosition.x;
				float z = playerPosition.z - reflectionPosition.z;

				// Restrict the model's reflection to be within the cell's limits.
				if (x < -2.5)
				{
					x = -2.5;
				}
				else if (x > -0.5)
				{
					x = -0.5;
				}

				if (z < -2.5)
				{
					z = -2.5;
				}
				else if (z > -0.5)
				{
					z = -0.5;
				}

				// Match the player's position within the boundaries of the cell.
				glTranslatef(x, 0, z);

				// Match the players rotation,
				glRotatef(playerRotation, 0, 1, 0);

				// Render the player's reflection.
				player.render();

				// Renders the shadow.
				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glTranslatef(0, 0.001, 0);
				glBindTexture(GL_TEXTURE_2D, shadowTexture);
				glScalef(0.5, 1, 0.5);
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				glVertexPointer(3, GL_FLOAT, 0, shadowVerts.data());
				glNormalPointer(GL_FLOAT, 0, shadowNormals.data());
				glTexCoordPointer(2, GL_FLOAT, 0, shadowTexCoords.data());

				glDrawArrays(GL_QUADS, 0, 4);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);

				glDisable(GL_BLEND);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			// Finish drawing reflection.
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
			glDisable(GL_TEXTURE_2D);
			renderReflectionPlane();
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		// Draw cell bars in front of the reflection.
		glPushMatrix();
			glEnable(GL_BLEND);
			glBindTexture(GL_TEXTURE_2D, reflectionBarsTexture);
			glTranslatef(0, 0, -0.01);
			renderReflectionPlane();
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();
}

// Function that draws the plane used in reflection.
void ObjectManager::renderReflectionPlane()
{
	glBegin(GL_QUADS);

		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);

		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 1);
		glVertex3f(0, 3, 0);

		glNormal3f(0, 0, -1);
		glTexCoord2f(1, 1);
		glVertex3f(3, 3, 0);

		glNormal3f(0, 0, -1);
		glTexCoord2f(1, 0);
		glVertex3f(3, 0, 0);

	glEnd();
}

// Renders a disc with an image of the earth as it's texture. This disc is always moved so that it remains the exact same distance away from the player, so it looks like it remains in the same position in the sky.
void ObjectManager::renderEarth()
{
	glPushMatrix();
		glTranslatef(playerPosition.x + 0, playerPosition.y + 20, playerPosition.z - 75);
		glBindTexture(GL_TEXTURE_2D, earthTexture);
		glScalef(10, 10, 10);
		shapeManager.renderDisc(1, 30);
	glPopMatrix();
}

// Renders a plane to act as the surface of the moon. The plane's size is slightly beyond the render distance, so it'll look like it goes as far as the eye can see.
void ObjectManager::renderMoon()
{
	glPushMatrix();
		glTranslatef(-125, 0, -125);
		moonFloor.render(); 
	glPopMatrix();
}

// Renders a spaceship model that is parked outside the base. There is also a flag next to it.
void ObjectManager::renderSpaceship()
{
	glPushMatrix();
		// Render spaceship.
		glTranslatef(spaceshipPosition.x, spaceshipPosition.y, spaceshipPosition.z);
		glScalef(10, 10, 10);
		spaceship.render();
		// Render flagpole.
		glScalef(0.1, 0.1, 0.1);
		glTranslatef(5, 1, 0);
		glBindTexture(GL_TEXTURE_2D, metalTexture);
		shapeManager.renderCylinder(0.05, 2, 20);
		// Render flag
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, flagTexture);
			glTranslatef(0.05, 1, 0);
			glRotatef(90, 1, 0, 0);
			shapeManager.renderPlane(0.75, 0.5, 1, 1);
		glPopMatrix();
	glPopMatrix();
}

// Renders a table with a floating corgi above it. This table is then lit with a red rotating spotlight to showcase the planar projected shadow of the corgi.
void ObjectManager::renderSpotlightShadow()
{
	glPushMatrix();
		// Move into position
		glTranslatef(spotlightPosition.x, spotlightPosition.y, spotlightPosition.z);

		// Render light and a sphere to represent it
		glPushMatrix();
			spotLight.render();

			glDisable(GL_TEXTURE_2D);
			glColor3f(1.0, 0.0, 0.0);
			glDisable(GL_LIGHTING); // this sphere represents a light source, therefore should not be affected by other sources of light.
			glTranslatef(spotPosition[0], spotPosition[1], spotPosition[2]);
			shapeManager.renderSphere(0.05, 20);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0, 1.0, 1.0);

		glPopMatrix();

		// Generate shadow matrix
		shadow.generateShadowMatrix(shadowMatrix, spotPosition, shadowVerts.data());

		// Render table
		glPushMatrix();
			glTranslatef(-0.5, 1, -0.5);
			tableLeg.render();
			glTranslatef(0.9, 0, 0);
			tableLeg.render();
			glTranslatef(0, 0, 0.9);
			tableLeg.render();
			glTranslatef(-0.9, 0, 0);
			tableLeg.render();
			glTranslatef(0, 0, -0.9);
			tableTop.render();
		glPopMatrix();

		// Render model's shadow

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor4f(0.1f, 0.1f, 0.1f, 0.5f);

		glPushMatrix();
			glTranslatef(0, 1, 0);
			glMultMatrixf((GLfloat*)shadowMatrix);
			glTranslatef(0, 1.1, 0);
			glScalef(0.2, 0.2, 0.2);
			glRotatef(-rotate, 0, 1, 0);
			corgi.render();
		glPopMatrix();

		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		// Render model
		glPushMatrix();
			glTranslatef(0, 1.1, 0);
			glScalef(0.2, 0.2, 0.2);
			glRotatef(-rotate, 0, 1, 0);
			corgi.render();
		glPopMatrix();
	glPopMatrix();
}

// Renders three cubes with transparent faces to showcase render order and face culling.
void ObjectManager::renderTransparentCubes()
{
	glPushMatrix();
		// Move into position
		glTranslatef(cubesPosition.x, cubesPosition.y, cubesPosition.z);

		// Render plinth
		glPushMatrix();
			glTranslatef(0, 1, 0);
			plinth.render();
		glPopMatrix();

		// Inner cube - has to be rendered first. The cube is rendered twice, once with its front face culled and again with its back face culled. This allows you to look through the cube and still be able to see the other side of it.
		glPushMatrix();
			glTranslatef(0.25, 1.5, 0.25);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glBindTexture(GL_TEXTURE_2D, transparentCubeTexture);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(rotate, 1, 1, 0);
			shapeManager.renderCube();
			glCullFace(GL_BACK);
			shapeManager.renderCube();
			glDisable(GL_CULL_FACE);
			glDisable(GL_BLEND);
		glPopMatrix();

		// Middle cube
		glPushMatrix();
			glTranslatef(0.25, 1.5, 0.25);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glBindTexture(GL_TEXTURE_2D, transparentCubeTexture);
			glScalef(0.15, 0.15, 0.15);
			glRotatef(rotate, 1, 0, 1);
			shapeManager.renderCube();
			glCullFace(GL_BACK);
			shapeManager.renderCube();
			glDisable(GL_CULL_FACE);
			glDisable(GL_BLEND);
		glPopMatrix();

		// Outer cube
		glPushMatrix();
			glTranslatef(0.25, 1.5, 0.25);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glBindTexture(GL_TEXTURE_2D, transparentCubeTexture);
			glScalef(0.25, 0.25, 0.25);
			glRotatef(rotate, 0, 1, 1);
			shapeManager.renderCube();
			glCullFace(GL_BACK);
			shapeManager.renderCube();
			glDisable(GL_CULL_FACE);
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();
}

// Renders a shadow imposter at the player's feet using blending.
void ObjectManager::renderPlayerShadow()
{
	// Render player shadow
	glPushMatrix();

		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTranslatef(playerPosition.x, 0.001, playerPosition.z);
		glBindTexture(GL_TEXTURE_2D, shadowTexture);
		glScalef(0.5, 1, 0.5);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, shadowVerts.data());
		glNormalPointer(GL_FLOAT, 0, shadowNormals.data());
		glTexCoordPointer(2, GL_FLOAT, 0, shadowTexCoords.data());

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

// Renders the walls of the moonbase.
void ObjectManager::renderBase()
{
	glPushMatrix();
		// Render base perimeter
		glPushMatrix();
			glTranslatef(-baseSize/2, 1.5, -baseSize / 2);
			wallShort.render();
			glTranslatef(0, 3, 0);
			wallShort.render();
			glTranslatef(0, -3, 0);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(0, 3, 0);
			wallTall.render();
			glRotatef(90, 0, 1, 0);
			glTranslatef(baseSize, 0, baseSize);
			glRotatef(90, 0, 1, 0);
			wallTall.render();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, -3, 0);
			wallShort.render();
			glTranslatef(0, 3, 0);
			wallShort.render();
			glTranslatef(0, -3, 0);
		glPopMatrix();

		// Render door
		glPushMatrix();
			glTranslatef(-baseSize / 2 + 0.01, 3, 1.5);
			glRotatef(-90, 0, 0, 1);
			glScalef(1, 1, -1);
			door.render();
		glPopMatrix();
	glPopMatrix();
}

// Renders the windows and skylight of the base.
void ObjectManager::renderBaseWindows()
{
	// Render windows - done last as transparent
	glPushMatrix();
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, windowTexture);
		glTranslatef(-baseSize / 2, 4.5, -baseSize / 2);
		skylight.render();
		glTranslatef(0, -1.5, 0);
		glRotatef(90, 1, 0, 0);
		window.render();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, baseSize);
		glRotatef(90, 1, 0, 0);
		window.render();
		glRotatef(-90, 1, 0, 0);
		glDisable(GL_BLEND);
	glPopMatrix();
}
