#include "Camera.h"

// Default constructor. Creates the camera object using default values for position, lookAt, and up.
Camera::Camera()
{
	// Camera will be positioned by the base's door.
	setPosition(-23.2f, 1.9f, 0.0f);
	setLookAt(0.0f, 0.0f, 0.0f);
	setUp(0.0f, 1.0f, 0.0f);
	setCamera(position, lookAt, up);

	// Camera will be rotated 90 degrees around y axis, controlled by the mouse, rotate with a speed of 5, move with a speed of 3, rotate with a speed of 0.25 in third person, orbit the player model with a radius of 2, and start in First Person Perspective.
	pitch = 0;
	yaw = 90;
	roll = 0;
	mouseToggle = true;
	speed = 5;
	movementSpeed = 3;
	tpSpeed = 0.25;
	tpRadius = 2;
	setMode(Mode::FPP);
	
}

// Overloaded constructor. Creates the camera object using Vector3 objects for position, lookAt and up.
Camera::Camera(Vector3 p, Vector3 l, Vector3 u)
{
	// Values determined by constructor arguments
	setPosition(p);
	setLookAt(l);
	setUp(u);
	setCamera(position, lookAt, up);

	// Default values
	pitch = 0;
	yaw = 0;
	roll = 0;
	mouseToggle = true;
	speed = 5;
	movementSpeed = 3;
	tpSpeed = 0.25;
	tpRadius = 2;
	setMode(Mode::FPP);
}

// Overloaded constructor. Creates the camera object using float values for position, lookAt and up's x, y, and z values.
Camera::Camera(float pX, float pY, float pZ, float lX, float lY, float lZ, float uX, float uY, float uZ)
{
	// Values determined by constructor arguments
	setPosition(pX, pY, pZ);
	setLookAt(lX, lY, lZ);
	setUp(uX, uY, uZ);
	setCamera(position, lookAt, up);

	// Default values
	pitch = 0;
	yaw = 0;
	roll = 0;
	mouseToggle = true;
	speed = 5;
	movementSpeed = 3;
	tpSpeed = 0.25;
	tpRadius = 2;
	setMode(Mode::FPP);
}

Camera::~Camera()
{
}

void Camera::update(float dt)
{
	
	if (mouseToggle) // If the camera is being controlled by the mouse...
	{
		glutWarpPointer(width / 2, height / 2); // Move mouse to centre of the screen
		glutSetCursor(GLUT_CURSOR_NONE); // Hide cursor
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW); // Show cursor
	}
	
}

void Camera::handleInput(float dt)
{
	// Resets the camera's position, lookAt, up and mode variables to default values.
	if (input->isKeyDown('r'))
	{
		input->setKeyUp('r');
		setPosition(-23.2f, playerHeight, 0.0f);
		setLookAt(0.0f, 0.0f, 0.0f);
		setUp(0.0f, 1.0f, 0.0f);
		mode = Mode::FPP;
	}

	// Switches the camera mode. Reset rotation, up and moves camera to the correct position.
	if (input->isKeyDown('c'))
	{
		input->setKeyUp('c');
		int current = int(mode);
		current += 1;
		pitch = 0;
		yaw = 90;
		roll = 0;
		setUp(0.0f, 1.0f, 0.0f);
		setPosition(position.x, playerHeight, position.z);
		if (current > 2)
		{
			current = 0;
		}
		mode = Mode(current);
	}

	// Movement controls. Only work when the user has the window focused with their mouse. Some movements are restricted to the free camera.

	if (input->isKeyDown('w') && mouseToggle)
	{
		if (input->isKeyDown('z') && mode == Mode::FREE)
		{
			moveUp(dt); // Move camera up when both z and w are pressed.
		}
		else if (input->isKeyDown('x') && mode == Mode::FREE)
		{
			rotateUp(dt); // Rotate camera up when both x and w are pressed.
		}
		else
		{
			moveForward(dt); // Move camera forward when just w is pressed.
		}
		
	}
	else if (input->isKeyDown('s') && mouseToggle)
	{
		if (input->isKeyDown('z') && mode == Mode::FREE)
		{
			moveDown(dt); // Move camera down when both z and s are pressed.
		}
		else if (input->isKeyDown('x') && mode == Mode::FREE)
		{
			rotateDown(dt); // Rotate camera down when both x and s are pressed.
		}
		else
		{
			moveBackward(dt); // Move camera backward when just s is pressed.
		}
	}

	if (input->isKeyDown('a') && mouseToggle)
	{
		if (input->isKeyDown('x') && mode == Mode::FREE)
		{
			rollLeft(dt); // Roll camera left when both x and a are pressed.
		}
		else
		{
			moveLeft(dt); // Move camera left when just a is pressed.
		}
		
	}
	else if (input->isKeyDown('d') && mouseToggle)
	{
		if (input->isKeyDown('x') && mode == Mode::FREE)
		{
			rollRight(dt); // Roll camera right when both x and d are pressed.
		}
		else
		{
			moveRight(dt); // Move camera right when just d is pressed.
		}
	}

	if (input->isKeyDown('q') && mode == Mode::FREE && mouseToggle) // Rotate camera left when q is pressed.
	{
		rotateLeft(dt);
	}
	else if (input->isKeyDown('e') && mode == Mode::FREE && mouseToggle) // Rotate camera right when e is pressed.
	{
		rotateRight(dt);
	}

	if (input->isKeyDown('t')) // Toggles mouse movement of the camera when t is pressed.
	{
		input->setKeyUp('t');
		
		mouseToggle = !mouseToggle; 

		// Mouse position is set to the middle of the screen to prevent the camera from moving everytime the mouse movement is toggled and the mouse is not at the centre of the screen.
		input->setMouseX(width / 2);
		input->setMouseY(height / 2);
	}

	if (mouseToggle) // When mouse movement is enabled...
	{
		// Get the current mouse co-ordinates
		int mouseX = input->getMouseX();
		int mouseY = input->getMouseY();

		// Calculate the distance between the mouse and the centre of the screen
		int distanceX = mouseX - (width / 2);
		int distanceY = mouseY - (height / 2);

		// Use this distance to calculate the yaw and pitch for the required rotation. The third person camera has a different rotation speed, so is handled seperately from first person and free.
		if (mode == Mode::FPP || mode == Mode::FREE)
		{
			yaw += distanceX * dt * speed;
			pitch -= distanceY * dt * speed;
		}
		else
		{
			yaw += distanceX * dt * tpSpeed;
			pitch -= distanceY * dt * tpSpeed;
		}

		// Call the function to calculate rotations.
		rotate();
	}
}

// Returns the camera's current position.
Vector3 Camera::getPosition()
{
	return position;
}

// Returns the camera's current 'look at' values.
Vector3 Camera::getLookAt()
{
	return lookAt;
}

// Returns the camera's current 'up' values.
Vector3 Camera::getUp()
{
	return up;
}

// Returns the camera's current 'pitch' value.
float Camera::getPitch()
{
	return pitch;
}

// Returns the camera's current 'yaw' value.
float Camera::getYaw()
{
	return yaw;
}

// Returns the camera's current 'roll' value.
float Camera::getRoll()
{
	return roll;
}

// Set the camera's position using a Vector3.
void Camera::setPosition(Vector3 p)
{
	position = p;
}

// Set the camera's position using three float values.
void Camera::setPosition(float pX, float pY, float pZ)
{
	position = Vector3(pX, pY, pZ);
}

// Set the camera's 'look at' using a Vector3.
void Camera::setLookAt(Vector3 l)
{
	lookAt = l;
}

// Set the camera's 'look at' using three float values.
void Camera::setLookAt(float lX, float lY, float lZ)
{
	lookAt = Vector3(lX, lY, lZ);
}

// Set the camera's 'up' using a Vector3.
void Camera::setUp(Vector3 u)
{
	up = u;
}

// Set the camera's 'up' using three float values.
void Camera::setUp(float uX, float uY, float uZ)
{
	up = Vector3(uX, uY, uZ);
}

// Function to set gluLookAt using the current values for position, lookAt and up. (So you don't need to call setCamera() with getPosition(), getLookAt() and getUp() as arguments.)
void Camera::setCamera()
{
	gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, up.x, up.y, up.z);
}

// Function to set gluLookAt using provided position, lookAt, and up vectors.
void Camera::setCamera(Vector3 p, Vector3 l, Vector3 u)
{
	gluLookAt(p.x, p.y, p.z, l.x, l.y, l.z, u.x, u.y, u.z);
}

// Move the camera forwards by adding the forward vector to the position.
void Camera::moveForward(float dt)
{
	if (mode == Mode::FREE)
	{
		setPosition(position.x + forward.x * movementSpeed * dt, position.y + forward.y * movementSpeed * dt, position.z + forward.z * movementSpeed * dt);
	}
	else
	{
		setPosition(position.x + forward.x * movementSpeed * dt, position.y, position.z + forward.z * movementSpeed * dt);
	}
}

// Move the camera backwards by subtracting the forward vector from the position.
void Camera::moveBackward(float dt)
{
	if (mode == Mode::FREE)
	{
		setPosition(position.x - forward.x * movementSpeed * dt, position.y - forward.y * movementSpeed * dt, position.z - forward.z * movementSpeed * dt);
	}
	else
	{
		setPosition(position.x - forward.x * movementSpeed * dt, position.y, position.z - forward.z * movementSpeed * dt);
	}

}

// Move the camera up by adding the up vector to the position.
void Camera::moveUp(float dt)
{
	setPosition(position.x + up.x * movementSpeed * dt, position.y + up.y * movementSpeed * dt, position.z + up.z * movementSpeed * dt);
}

// Move the camera down by subtracting the up vector from the position.
void Camera::moveDown(float dt)
{
	setPosition(position.x - up.x * movementSpeed * dt, position.y - up.y * movementSpeed * dt, position.z - up.z * movementSpeed * dt);
}

// Move the camera right by adding the right vector to the position.
void Camera::moveRight(float dt)
{
	if (mode == Mode::FREE)
	{
		setPosition(position.x + right.x * movementSpeed * dt, position.y + right.y * movementSpeed * dt, position.z + right.z * movementSpeed * dt);
	}
	else
	{
		setPosition(position.x + right.x * movementSpeed * dt, position.y, position.z + right.z * movementSpeed * dt);
	}

}

// Move the camera left by subtracting the right vector from the position.
void Camera::moveLeft(float dt)
{
	if (mode == Mode::FREE)
	{
		setPosition(position.x - right.x * movementSpeed * dt, position.y - right.y * movementSpeed * dt, position.z - right.z * movementSpeed * dt);
	}
	else
	{
		setPosition(position.x - right.x * movementSpeed * dt, position.y, position.z - right.z * movementSpeed * dt);
	}
}

// Rotate the camera up by increasing the pitch by 90 degrees per second and then calling the rotate function.
void Camera::rotateUp(float dt)
{
	pitch += 90 * dt;
	rotate();
}

// Rotate the camera down by decreasing the pitch by 90 degrees per second and then calling the rotate function.
void Camera::rotateDown(float dt)
{
	pitch -= 90 * dt;
	rotate();
}

// Rotate the camera right by increasing the yaw by 90 degrees per second and then calling the rotate function.
void Camera::rotateRight(float dt)
{
	yaw += 90 * dt;
	rotate();
}

// Rotate the camera left by decreasing the yaw by 90 degrees per second and then calling the rotate function.
void Camera::rotateLeft(float dt)
{
	yaw -= 90 * dt;
	rotate();
}

// Roll the camera left by increasing the roll by 90 degrees per second and then calling the rotate function.
void Camera::rollLeft(float dt)
{
	roll += 90 * dt;
	rotate();
}

// Rolln the camera right by decreasing the roll by 90 degrees per second and then calling the rotate function.
void Camera::rollRight(float dt)
{
	roll -= 90 * dt;
	rotate();
}

// To be called whenever rotation is needed rather than being put in the update function.
// Performs the required calculations for rotation.
void Camera::rotate()
{
	// When in first person mode...
	if (mode == Mode::FPP)
	{
		// If statement to prevent the camera from looking too far up or down in first person perspective.
		if (pitch > 90)
		{
			pitch = 90;
		}
		else if (pitch < -90)
		{
			pitch = -90;
		}

		// If statements to prevent the player from leaving the base in first person mode.
		if (position.x > boundary - 0.5)
		{
			position.x = boundary - 0.5;
		}
		else if (position.x < -boundary + 0.5)
		{
			position.x = -boundary + 0.5;
		}

		if (position.z > boundary - 0.5)
		{
			position.z = boundary - 0.5;
		}
		else if (position.z < -boundary + 0.5)
		{
			position.z = -boundary + 0.5;
		}
	}

	// Formulas for calculating rotation in first person and free cameras.
	if (mode == Mode::FPP || mode == Mode::FREE)
	{
		// Variables for calculating the forward, up and right vectors
		float cosR, cosP, cosY;
		float sinR, sinP, sinY;

		cosY = cosf(yaw * PI / 180);
		cosP = cosf(pitch * PI / 180);
		cosR = cosf(roll * PI / 180);

		sinY = sinf(yaw * PI / 180);
		sinP = sinf(pitch * PI / 180);
		sinR = sinf(roll * PI / 180);

		// Calculate forward vector
		forward.x = sinY * cosP;
		forward.y = sinP;
		forward.z = cosP * -cosY;

		// Calculate up vector
		up.x = -cosY * sinR - sinY * sinP * cosR;
		up.y = cosP * cosR;
		up.z = -sinY * sinR - sinP * cosR * -cosY;

		// Right vector calculated by cross product of forward and up
		right.x = forward.y * up.z - forward.z * up.y;
		right.y = forward.z * up.x - forward.x * up.z;
		right.z = forward.x * up.y - forward.y * up.x;
	}

	// Set the camera to look in the direction of the calculated forward vector in first person and free mode.
	if (mode == Mode::FREE || mode == Mode::FPP)
	{
		setLookAt(position.x + forward.x, position.y + forward.y, position.z + forward.z);
	}
	else if (mode == Mode::TPP) // When in third person, the position is calculated using the yaw and pitch. The look at is always the same.
	{
		//setPosition(lookAt.x + tpRadius * cos(pitch), lookAt.y + tpRadius * sin(pitch), lookAt.z); // rotate up and down
		//setPosition(lookAt.x + tpRadius * sin(yaw), lookAt.y, lookAt.z + tpRadius * cos(yaw)); // rotate left and right
		// Combined:
		setPosition(lookAt.x + tpRadius * cos(pitch) * sin(yaw), lookAt.y + tpRadius * sin(pitch), lookAt.z + tpRadius * cos(yaw));
	}
	
}
