#include "shape.h"
#define GL_CLAMP_TO_EDGE 0x812F

// Vertex arrays of a plane.
extern float verts[] = {	-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
						};

extern float norms[] = { 0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						};		


extern float texcoords[]= {	0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

extern GLubyte indices[] = { 0, 1, 2, 3 };

// Vertex arrays of a cube.
extern float cubeVerts[] = { 
							// Front
							-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3

							// Right
							1.0, 1.0, 1.0, //4
							1.0, -1.0, 1.0, //5
							1.0, -1.0, -1.0, //6
							1.0, 1.0, -1.0, //7

							// Back
							1.0, 1.0, -1.0, //8
							1.0, -1.0, -1.0, //9
							-1.0, -1.0, -1.0, //10
							-1.0, 1.0, -1.0, //11

							// Left
							-1.0, 1.0, -1.0, //12
							-1.0, -1.0, -1.0, //13
							-1.0, -1.0, 1.0, //14
							-1.0, 1.0, 1.0, //15

							// Top
							-1.0, 1.0, -1.0, //16
							-1.0, 1.0, 1.0, //17
							1.0, 1.0, 1.0, //18
							1.0, 1.0, -1.0, //19

							// Bottom
							-1.0, -1.0, 1.0, //20
							-1.0, -1.0, -1.0, //21
							1.0, -1.0, -1.0, //22
							1.0, -1.0, 1.0, //23
};

extern float cubeNorms[] = { 
							// Front
							0.0, 0.0, 1.0,		//0
							0.0, 0.0, 1.0,		//1
							0.0, 0.0, 1.0,		//2
							0.0, 0.0, 1.0,		//3

							// Right
							1.0, 0.0, 0.0, //4
							1.0, 0.0, 0.0, //5
							1.0, 0.0, 0.0, //6
							1.0, 0.0, 0.0, //7

							// Back
							0.0, 0.0, -1.0, //8
							0.0, 0.0, -1.0, //9
							0.0, 0.0, -1.0, //10
							0.0, 0.0, -1.0, //11

							// Left
							-1.0, 0.0, 0.0, //12
							-1.0, 0.0, 0.0, //13
							-1.0, 0.0, 0.0, //14
							-1.0, 0.0, 0.0, //15

							// Top
							0.0, 1.0, 0.0, //16
							0.0, 1.0, 0.0, //17
							0.0, 1.0, 0.0, //18
							0.0, 1.0, 0.0, //19

							// Bottom
							0.0, -1.0, 0.0, //20
							0.0, -1.0, 0.0, //21
							0.0, -1.0, 0.0, //22
							0.0, -1.0, 0.0, //23

};


extern float cubeTexCoords[] = {
								// Front
								0.0, 0.0, 		//0
								0.0, 1.0, 		//1
								1.0, 1.0, 		//2
								1.0, 0.0, 		//3

								// Right
								0.0, 0.0, 		//4
								0.0, 1.0, 		//5
								1.0, 1.0, 		//6
								1.0, 0.0, 		//7

								// Back
								0.0, 0.0, 		//8
								0.0, 1.0, 		//9
								1.0, 1.0, 		//10
								1.0, 0.0, 		//11

								// Left
								0.0, 0.0, 		//12
								0.0, 1.0, 		//13
								1.0, 1.0, 		//14
								1.0, 0.0, 		//15

								// Top
								0.0, 0.0, 		//16
								0.0, 1.0, 		//17
								1.0, 1.0, 		//18
								1.0, 0.0, 		//19
								
								// Bottom
								0.0, 0.0, 		//20
								0.0, 1.0, 		//21
								1.0, 1.0, 		//22
								1.0, 0.0, 		//23
};

extern GLubyte cubeIndices[] = { 
								// Front
								0, 1, 2, 3,

								// Right
								4, 5, 6, 7,

								// Back
								8, 9, 10, 11,

								// Left
								12, 13, 14, 15,

								// Top
								16, 17, 18, 19,

								// Bottom
								20, 21, 22, 23,
};

// Render a plane using vertex arrays as defined above.
void Shape::renderPlane()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Render a cube using vertex arrays as defined above.
void Shape::renderCube()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
	glNormalPointer(GL_FLOAT, 0, cubeNorms);
	glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
}

void Shape::renderDisc(float r, int s)
{
	// Set variables needed for calculations.
	radius = r;
	diameter = radius * 2;
	segments = s;
	interval = (2 * PI) / segments;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < segments + 1; i++) // segments + 1 solved problem where there was a tiny gap between the first and last triangles, so this just loops one more time to add another triangle to fill the gap
	{
		glPushMatrix();
			// Render first point of triangle.
			glNormal3f(0, 0, 1); // normal is same on each vertex
			glTexCoord2f(0.5, 0.5); // texture co-ordinate for the middle is 0.5, 0.5
			glVertex3f(0, 0, 0); // centre point

			// Calculate first set of x and y co-ordinates and texture co-ordinates of the disc.
			angle = interval * i;
			x = radius * cosf(angle);
			y = radius * sinf(angle);
			u = (cos(angle) / diameter) + 0.5;
			v = -(sin(angle) / diameter) + 0.5;

			// Render second point using calculated values.
			glNormal3f(0, 0, 1);
			glTexCoord2f(u, v);
			glVertex3f(x, y, 0);

			// Calculate second set of x and y co-ordinates and texture co-ordinates of the disc.
			angle = interval * (i + 1);
			x = radius * cosf(angle);
			y = radius * sinf(angle);
			u = (cos(angle) / diameter) + 0.5;
			v = -(sin(angle) / diameter) + 0.5;

			// Render third point using calculated values.
			glNormal3f(0, 0, 1);
			glTexCoord2f(u, v);
			glVertex3f(x, y, 0); 
		glPopMatrix();
	}
	glEnd();
}

void Shape::renderSphere(float r, int s)
{
	// Set variables needed for calculations.
	radius = r;
	segments = s;
	latInterval = (2 * PI) / segments;
	longInterval = PI / segments;

	glBegin(GL_QUADS);
	for (int lo = 0; lo < segments + 1; lo++) // longitude. + 1 to close tiny gap by going round again by 1 increment
	{
		for (int la = 0; la < segments + 1; la++) // latitude. + 1 to close tiny gap by going round again by 1 increment
		{
			glPushMatrix();

			// Calculate first set of vertices and texture co-ordinates.
			x = ((radius * cosf(latInterval * la)) * sinf(longInterval * lo));
			y = (radius * cosf(longInterval * lo));
			z = ((radius * sinf(latInterval * la)) * sinf(longInterval * lo));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5; // textures were upside down so multiplied by -1

			// Render first set of normals, texture co-ordinates and vertices.
			glNormal3f(x / radius, y / radius, z / radius);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);

			// Second set of calculations.
			x = ((radius * cosf(latInterval * (la + 1))) * sinf(longInterval * lo));
			y = (radius * cosf(longInterval * lo));
			z = ((radius * sinf(latInterval * (la + 1))) * sinf(longInterval * lo));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			// Second point.
			glNormal3f(x / radius, y / radius, z / radius);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);

			// Third calculations.
			x = ((radius * cosf(latInterval * (la + 1))) * sinf(longInterval * (lo + 1)));
			y = (radius * cosf(longInterval * (lo + 1)));
			z = ((radius * sinf(latInterval * (la + 1))) * sinf(longInterval * (lo + 1)));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			// Third point.
			glNormal3f(x / radius, y / radius, z / radius);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);

			// Last calculations.
			x = ((radius * cosf(latInterval * la)) * sinf(longInterval * (lo + 1)));
			y = (radius * cosf(longInterval * (lo + 1)));
			z = ((radius * sinf(latInterval * la)) * sinf(longInterval * (lo + 1)));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			// Last point.
			glNormal3f(x / radius, y / radius, z / radius);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);

			glPopMatrix();
		}
	}
	glEnd();
}

void Shape::renderCylinder(float r, float h, int c)
{
	// Variables for calculations.
	radius = r;
	height = h;
	columns = c;

	interval = (2 * PI) / columns;
	heightInterval = height / columns;
	bottom = 0;

	// Top of cylinder is just a disc
	glPushMatrix();
		glTranslatef(0, 0.5 * height, 0); // start at half the height so that it is centred
		glRotatef(-90, 1, 0, 0);
		renderDisc(radius, columns);
	glPopMatrix();

	glBegin(GL_QUADS);
	for (int i = 0; i < columns + 1; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			// Calculate the vertices.
			angle = interval * i;
			x = radius * cosf(angle);
			y = 0.5 * height - j * heightInterval;
			z = radius * sinf(angle);

			angle2 = interval * (i + 1);
			x2 = radius * cosf(angle2);
			y2 = 0.5 * height - (j + 1) * heightInterval;
			z2 = radius * sinf(angle2);

			glPushMatrix();
				// Calculate texture co-ordinates and then render each point of the face.
				u = asin(x2 / radius) / PI + 0.5;
				v = asin(y / radius) / PI * -1 + 0.5; // textures were upside down so multiplied by -1
				glNormal3f(x2 / radius, y / radius, z2 / radius);
				glTexCoord2f(u, v);
				glVertex3f(x2, y, z2);

				u = asin(x2 / radius) / PI + 0.5;
				v = asin(y2 / radius) / PI * -1 + 0.5;
				glNormal3f(x2 / radius, y2 / radius, z2 / radius);
				glTexCoord2f(u, v);
				glVertex3f(x2, y2, z2);

				u = asin(x / radius) / PI + 0.5;
				v = asin(y2 / radius) / PI * -1 + 0.5;
				glNormal3f(x / radius, y2 / radius, z / radius);
				glTexCoord2f(u, v);
				glVertex3f(x, y2, z);

				u = asin(x / radius) / PI + 0.5;
				v = asin(y / radius) / PI * -1 + 0.5;
				glNormal3f(x / radius, y / radius, z / radius);
				glTexCoord2f(u, v);
				glVertex3f(x, y, z);
			glPopMatrix(); 

			bottom = y2;
		}
	}
	glEnd();

	// Second disc for bottom
	glPushMatrix();
		glTranslatef(0, bottom, 0);
		glRotatef(90, 1, 0, 0);
		renderDisc(radius, columns);
	glPopMatrix();
}

void Shape::renderCuboid(float l, float b, float d, int s1, int s2, int s3) // Length, breadth, depth, segments
{
	// The segment intervals.
	float ls = l / s1;
	float bs = b / s2;
	float ds = d / s3;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // gets rid of seams between textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// For loops that calculate and draw each face of the cuboid.
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			// Top
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(i * ls, 0, j * bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(i * ls + ls, 0, j * bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 1);
			glVertex3f(i * ls + ls, 0, j * bs + bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(i * ls, 0, j * bs + bs);

			// Bottom
			glNormal3f(0, -1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(i * ls, -d, j * bs);

			glNormal3f(0, -1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(i * ls + ls, -d, j * bs);

			glNormal3f(0, -1, 0);
			glTexCoord2f(1, 1);
			glVertex3f(i * ls + ls, -d, j * bs + bs);

			glNormal3f(0, -1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(i * ls, -d, j * bs + bs);

			for (int k = 0; k < s3; k++)
			{
				// Right
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 0);
				glVertex3f(i * ls, -k * ds, b);

				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 1);
				glVertex3f(i * ls + ls, -k * ds, b);

				glNormal3f(0, 0, 1);
				glTexCoord2f(1, 1);
				glVertex3f(i * ls + ls, -k * ds - ds, b);

				glNormal3f(0, 0, 1);
				glTexCoord2f(1, 0);
				glVertex3f(i * ls, -k * ds - ds, b);

				// Left
				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 0);
				glVertex3f(i * ls, -k * ds, 0);

				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 1);
				glVertex3f(i * ls + ls, -k * ds, 0);

				glNormal3f(0, 0, -1);
				glTexCoord2f(1, 1);
				glVertex3f(i * ls + ls, -k * ds - ds, 0);

				glNormal3f(0, 0, -1);
				glTexCoord2f(1, 0);
				glVertex3f(i * ls, -k * ds - ds, 0);

				// Back
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 0);
				glVertex3f(0, -k * ds, j * bs);

				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 1);
				glVertex3f(0, -k * ds - ds, j * bs);

				glNormal3f(-1, 0, 0);
				glTexCoord2f(1, 1);
				glVertex3f(0, -k * ds - ds, j * bs + bs);

				glNormal3f(-1, 0, 0);
				glTexCoord2f(1, 0);
				glVertex3f(0, -k * ds, j * bs + bs);

				// Front
				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 0);
				glVertex3f(l, -k * ds, j * bs);

				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 1);
				glVertex3f(l, -k * ds - ds, j * bs);

				glNormal3f(1, 0, 0);
				glTexCoord2f(1, 1);
				glVertex3f(l, -k * ds - ds, j * bs + bs);

				glNormal3f(1, 0, 0);
				glTexCoord2f(1, 0);
				glVertex3f(l, -k * ds, j * bs + bs);
			}
		}
	}
	glEnd();
}

void Shape::renderPlane(float l, float b, int s1, int s2)
{
	// The segment intervals.
	float ls = l / s1;
	float bs = b / s2;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // gets rid of seams between textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// For loops that calculate and draw each segment of the plane.
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(i * ls, 0, j * bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(i * ls + ls, 0, j * bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 1);
			glVertex3f(i * ls + ls, 0, j * bs + bs);

			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(i * ls, 0, j * bs + bs);
		}
	}
	glEnd();
}

// Modified version of the renderSphere function. Adds each point to vertex arrays instead of rendering with quads.
void Shape::generateSphere(float r, int s)
{
	radius = r;
	segments = s;
	latInterval = (2 * PI) / segments;
	longInterval = PI / segments;

	for (int lo = 0; lo < segments + 1; lo++)
	{
		for (int la = 0; la < segments + 1; la++)
		{
			
			x = ((radius * cosf(latInterval * la)) * sinf(longInterval * lo));
			y = (radius * cosf(longInterval * lo));
			z = ((radius * sinf(latInterval * la)) * sinf(longInterval * lo));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			normals.push_back(x / radius);
			normals.push_back(y / radius);
			normals.push_back(z / radius);
			
			texCoords.push_back(u);
			texCoords.push_back(v);

			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);
			
			x = ((radius * cosf(latInterval * (la + 1))) * sinf(longInterval * lo));
			y = (radius * cosf(longInterval * lo));
			z = ((radius * sinf(latInterval * (la + 1))) * sinf(longInterval * lo));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			normals.push_back(x / radius);
			normals.push_back(y / radius);
			normals.push_back(z / radius);

			texCoords.push_back(u);
			texCoords.push_back(v);

			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);

			x = ((radius * cosf(latInterval * (la + 1))) * sinf(longInterval * (lo + 1)));
			y = (radius * cosf(longInterval * (lo + 1)));
			z = ((radius * sinf(latInterval * (la + 1))) * sinf(longInterval * (lo + 1)));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			normals.push_back(x / radius);
			normals.push_back(y / radius);
			normals.push_back(z / radius);

			texCoords.push_back(u);
			texCoords.push_back(v);

			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);

			x = ((radius * cosf(latInterval * la)) * sinf(longInterval * (lo + 1)));
			y = (radius * cosf(longInterval * (lo + 1)));
			z = ((radius * sinf(latInterval * la)) * sinf(longInterval * (lo + 1)));
			u = asin(x / radius) / PI + 0.5;
			v = asin(y / radius) / PI * -1 + 0.5;

			normals.push_back(x / radius);
			normals.push_back(y / radius);
			normals.push_back(z / radius);

			texCoords.push_back(u);
			texCoords.push_back(v);

			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);
		}
	}
}

// Modified version of the renderCuboid function. Adds each point to vertex arrays instead of rendering with quads.
void Shape::generateCuboid(float l, float b, float d, int s1, int s2, int s3)
{
	float ls = l / s1;
	float bs = b / s2;
	float ds = d / s3;

	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			// Top
			normals.push_back(0); normals.push_back(1); normals.push_back(0);
			texCoords.push_back(0); texCoords.push_back(0);
			vertex.push_back(i * ls); vertex.push_back(0); vertex.push_back(j * bs);

			normals.push_back(0); normals.push_back(1); normals.push_back(0);
			texCoords.push_back(0); texCoords.push_back(1);
			vertex.push_back(i * ls + ls); vertex.push_back(0); vertex.push_back(j * bs);

			normals.push_back(0); normals.push_back(1); normals.push_back(0);
			texCoords.push_back(1); texCoords.push_back(1);
			vertex.push_back(i * ls + ls); vertex.push_back(0); vertex.push_back(j * bs + bs);

			normals.push_back(0); normals.push_back(1); normals.push_back(0);
			texCoords.push_back(1); texCoords.push_back(0);
			vertex.push_back(i * ls); vertex.push_back(0); vertex.push_back(j * bs + bs);

			// Bottom
			normals.push_back(0); normals.push_back(-1); normals.push_back(0);
			texCoords.push_back(0); texCoords.push_back(0);
			vertex.push_back(i * ls); vertex.push_back(-d); vertex.push_back(j * bs);

			normals.push_back(0); normals.push_back(-1); normals.push_back(0);
			texCoords.push_back(0); texCoords.push_back(1);
			vertex.push_back(i * ls + ls); vertex.push_back(-d); vertex.push_back(j * bs);

			normals.push_back(0); normals.push_back(-1); normals.push_back(0);
			texCoords.push_back(1); texCoords.push_back(1);
			vertex.push_back(i * ls + ls); vertex.push_back(-d); vertex.push_back(j * bs + bs);

			normals.push_back(0); normals.push_back(-1); normals.push_back(0);
			texCoords.push_back(1); texCoords.push_back(0);
			vertex.push_back(i * ls); vertex.push_back(-d); vertex.push_back(j * bs + bs);

			for (int k = 0; k < s3; k++)
			{
				// Right
				normals.push_back(0); normals.push_back(0); normals.push_back(1);
				texCoords.push_back(0); texCoords.push_back(0);
				vertex.push_back(i * ls); vertex.push_back(-k * ds); vertex.push_back(b);

				normals.push_back(0); normals.push_back(0); normals.push_back(1);
				texCoords.push_back(0); texCoords.push_back(1);
				vertex.push_back(i * ls + ls); vertex.push_back(-k * ds); vertex.push_back(b);

				normals.push_back(0); normals.push_back(0); normals.push_back(1);
				texCoords.push_back(1); texCoords.push_back(1);
				vertex.push_back(i * ls + ls); vertex.push_back(-k * ds - ds); vertex.push_back(b);

				normals.push_back(0); normals.push_back(0); normals.push_back(1);
				texCoords.push_back(1); texCoords.push_back(0);
				glVertex3f(i * ls, -k * ds - ds, b);
				vertex.push_back(i * ls); vertex.push_back(-k * ds - ds); vertex.push_back(b);

				// Left
				normals.push_back(0); normals.push_back(0); normals.push_back(-1);
				texCoords.push_back(0); texCoords.push_back(0);
				vertex.push_back(i * ls); vertex.push_back(-k * ds); vertex.push_back(0);

				normals.push_back(0); normals.push_back(0); normals.push_back(-1);
				texCoords.push_back(0); texCoords.push_back(1);
				vertex.push_back(i * ls + ls); vertex.push_back(-k * ds); vertex.push_back(0);

				normals.push_back(0); normals.push_back(0); normals.push_back(-1);
				texCoords.push_back(1); texCoords.push_back(1);
				vertex.push_back(i * ls + ls); vertex.push_back(-k * ds - ds); vertex.push_back(0);

				normals.push_back(0); normals.push_back(0); normals.push_back(-1);
				texCoords.push_back(1); texCoords.push_back(0);
				vertex.push_back(i * ls); vertex.push_back(-k * ds - ds); vertex.push_back(0);

				// Back
				normals.push_back(-1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(0); texCoords.push_back(0);
				vertex.push_back(0); vertex.push_back(-k * ds); vertex.push_back(j * bs);

				normals.push_back(-1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(0); texCoords.push_back(1);
				vertex.push_back(0); vertex.push_back(-k * ds - ds); vertex.push_back(j * bs);

				normals.push_back(-1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(1); texCoords.push_back(1);
				vertex.push_back(0); vertex.push_back(-k * ds - ds); vertex.push_back(j * bs + bs);

				normals.push_back(-1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(1); texCoords.push_back(0);
				vertex.push_back(0); vertex.push_back(-k * ds); vertex.push_back(j * bs + bs);

				// Front
				normals.push_back(1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(0); texCoords.push_back(0);
				vertex.push_back(l); vertex.push_back(-k * ds); vertex.push_back(j * bs);

				normals.push_back(1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(0); texCoords.push_back(1);
				vertex.push_back(l); vertex.push_back(-k * ds - ds); vertex.push_back(j * bs);

				normals.push_back(1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(1); texCoords.push_back(1);
				vertex.push_back(l); vertex.push_back(-k * ds - ds); vertex.push_back(j * bs + bs);

				normals.push_back(1); normals.push_back(0); normals.push_back(0);
				texCoords.push_back(1); texCoords.push_back(0);
				vertex.push_back(l); vertex.push_back(-k * ds); vertex.push_back(j * bs + bs);
			}
		}
	}
}

// Modified version of the renderPlane overloaded function. Adds each point to vertex arrays instead of rendering with quads.
void Shape::generatePlane(float l, float b, int s1, int s2)
{
	float ls = l / s1;
	float bs = b / s2;

	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			texCoords.push_back(0);
			texCoords.push_back(0);

			vertex.push_back(i * ls);
			vertex.push_back(0);
			vertex.push_back(j * bs);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			texCoords.push_back(0);
			texCoords.push_back(1);

			vertex.push_back(i * ls + ls);
			vertex.push_back(0);
			vertex.push_back(j * bs);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			texCoords.push_back(1);
			texCoords.push_back(1);

			vertex.push_back(i * ls + ls);
			vertex.push_back(0);
			vertex.push_back(j * bs + bs);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			texCoords.push_back(1);
			texCoords.push_back(0);

			vertex.push_back(i * ls);
			vertex.push_back(0);
			vertex.push_back(j * bs + bs);
		}
	}
}

void Shape::render() // render shapes generated with quads
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // gets rid of seams between textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glDrawArrays(GL_QUADS, 0, vertex.size() / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

// Set texture using a string value.
void Shape::setTexture(std::string s)
{
	texture = SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}






