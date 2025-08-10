#include "Animation.h"

// Construct the object with default values.
Animation::Animation() 
{
	// Animation defaults to Emilia Clarke's stabilised eyebrows if no other animation is initialised.
	setTexture("gfx/eyebrowsgif.png");
	speed = 0.03f;
	currentRow = 1;
	currentColumn = 1;
	segments = 9;
	segmentSize = 1 / float(segments);

	// Default vertices
	vertex.push_back(-1);
	vertex.push_back(1);
	vertex.push_back(1);

	vertex.push_back(-1);
	vertex.push_back(-1);
	vertex.push_back(1);

	vertex.push_back(1);
	vertex.push_back(-1);
	vertex.push_back(1);

	vertex.push_back(1);
	vertex.push_back(1);
	vertex.push_back(1);

	// Normals
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	// Texture co-ords of first frame
	texCoords.push_back(0.0);
	texCoords.push_back(0.0);

	texCoords.push_back(0.0);
	texCoords.push_back(segmentSize);

	texCoords.push_back(segmentSize);
	texCoords.push_back(segmentSize);

	texCoords.push_back(segmentSize);
	texCoords.push_back(0.0);

	// Animation is not playing by default
	playing = false;
}

Animation::~Animation()
{
}

// Handles the playing of the animation.
void Animation::update(float dt)
{
	if (playing) // When the animation is playing...
	{
		playTime += dt; // Increased the elapsed time by delta time.
		if (playTime > speed) // Once the elapsed time is greater than the time each frame should be displayed...
		{
			playTime = 0; // Reset the elapsed time.
			currentColumn += 1; // Move to the next column in the animation.
			if (currentColumn > segments) // If already at the last column, move back to the first column and move on to the next row.
			{
				currentColumn = 1;
				currentRow += 1;
			}

			if (currentRow > segments) // Once the animation reaches the end of the last row, it will go back to the first row.
			{
				currentRow = 1;
			}

			// Clear the texture co-ordinates so that new ones can be added.
			texCoords.clear();

			// Add texture co-ordinates to the vector based on the current row, column and segment size.
			texCoords.push_back((currentColumn - 1) * segmentSize);
			texCoords.push_back((currentRow - 1) * segmentSize);

			texCoords.push_back((currentColumn - 1) * segmentSize);
			texCoords.push_back((currentRow - 1) * segmentSize + segmentSize);

			texCoords.push_back((currentColumn - 1) * segmentSize + segmentSize);
			texCoords.push_back((currentRow - 1) * segmentSize + segmentSize);

			texCoords.push_back((currentColumn - 1) * segmentSize + segmentSize);
			texCoords.push_back((currentRow - 1) * segmentSize);
		}
	}
}

// Another way of setting the texture by passing a string and passing that into the load texture function.
void Animation::setTexture(std::string s)
{
	texture = SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

// Set up a new animation.
void Animation::initialise(GLuint tex, int s, float t) // 1 value for segments as textures will be square, so rows and columns is the same.
{
	// Set variables based on the arguments given.
	segments = s;
	segmentSize = 1 / float(segments);

	currentRow = 1;
	currentColumn = 1;

	setTexture(tex);

	speed = t;

	// Clear texture co-ordinates.
	texCoords.clear();

	// Texture co-ords of first frame
	texCoords.push_back(0.0);
	texCoords.push_back(0.0);

	texCoords.push_back(0.0);
	texCoords.push_back(segmentSize);

	texCoords.push_back(segmentSize);
	texCoords.push_back(segmentSize);

	texCoords.push_back(segmentSize);
	texCoords.push_back(0.0);

	// Set animation to play.
	playing = true;
}

// Render the plane using vertex arrays.
void Animation::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, texture);

	glVertexPointer(3, GL_FLOAT, 0, vertex.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
