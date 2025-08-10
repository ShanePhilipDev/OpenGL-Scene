#include "Skybox.h"
#define GL_CLAMP_TO_EDGE 0x812F


Skybox::Skybox()
{
	// Load default textures for the skybox.
	front = SOIL_load_OGL_texture("gfx/skybox_front.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	back = SOIL_load_OGL_texture("gfx/skybox_back.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	left = SOIL_load_OGL_texture("gfx/skybox_left.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	right = SOIL_load_OGL_texture("gfx/skybox_right.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	top = SOIL_load_OGL_texture("gfx/skybox_top.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	bottom = SOIL_load_OGL_texture("gfx/skybox_bottom.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

Skybox::~Skybox()
{
}

// Function to render the skybox.
void Skybox::renderSkybox()
{
	glPushMatrix();

		// Move the skybox to the camera's position.
		glTranslatef(position.x, position.y, position.z);

		// Disable depth test so that the skybox is always behind objects. Re-enabled after object is drawn.
		glDisable(GL_DEPTH_TEST);

		// Don't want lighting to affect the skybox. Re-enabled after object is drawn.
		glDisable(GL_LIGHTING);

		// Bind the texture, then clamp it to the edge so there are no seams.
		glBindTexture(GL_TEXTURE_2D, front);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Drawing each face of the skybox and assigning the texture co-ordinates.
		glBegin(GL_QUADS);

			// draw front
			//glNormal3f(0, 0, 1);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, 1);

			//glNormal3f(0, 0, 1);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, 1);

			//glNormal3f(0, 0, 1);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, 1);

			//glNormal3f(0, 0, 1);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, 1);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, right);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBegin(GL_QUADS);

			// draw right
			//glNormal3f(1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, 1);

			//glNormal3f(1, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(1, -1, 1);

			//glNormal3f(1, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, -1);

			//glNormal3f(1, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, -1);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, back);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBegin(GL_QUADS);

			// draw back
			//glNormal3f(0, 0, -1);
			glTexCoord2f(1, 0);
			glVertex3f(-1, 1, -1);

			//glNormal3f(0, 0, -1);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, -1);

			//glNormal3f(0, 0, -1);
			glTexCoord2f(0, 1);
			glVertex3f(1, -1, -1);

			//glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, -1);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, left);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBegin(GL_QUADS);

			// draw left
			//glNormal3f(-1, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(-1, 1, 1);

			//glNormal3f(-1, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, 1);

			//glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, -1);

			//glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, -1);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, top);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBegin(GL_QUADS);

			// draw top
			//glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, -1);

			//glNormal3f(0, 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-1, 1, 1);

			//glNormal3f(0, 1, 0);
			glTexCoord2f(1, 1);
			glVertex3f(1, 1, 1);

			//glNormal3f(0, 1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, -1);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, bottom);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBegin(GL_QUADS);

			// draw bottom
			//glNormal3f(0, -1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(-1, -1, 1);

			//glNormal3f(0, -1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, -1);

			//glNormal3f(0, -1, 0);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, -1);

			//glNormal3f(0, -1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(1, -1, 1);

		glEnd();

		glEnable(GL_LIGHTING);

		glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}



