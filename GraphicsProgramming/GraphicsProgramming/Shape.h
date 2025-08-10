#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <iostream>
#include <vector>
#include "SOIL.h"
#define PI 3.1415
class Shape
{
	public:
		void renderPlane(); // render a plane using predefined matrices
		void renderCube(); // render a cube using predefined matrices

		// Functions to render objects in real-time.
		void renderDisc(float r, int s);
		void renderSphere(float r, int s);
		void renderCylinder(float r, float h, int c);
		void renderCuboid(float l, float b, float d, int s1, int s2, int s3);
		void renderPlane(float l, float b, int s1, int s2);

		// Functions to generate vertex arrays for objects to render later.
		void generateSphere(float r, int s);
		void generateCuboid(float l, float b, float d, int s1, int s2, int s3);
		void generatePlane(float l, float b, int s1, int s2);

		// Function to render vertex arrays.
		void render();

		// Functions to set the texture of the shape.
		void setTexture(std::string s);
		void setTexture(GLuint t) { texture = t; };

		// Getters for the shape's vertex arrays.
		std::vector<float> getVertex() { return vertex; };
		std::vector<float> getNormals() { return normals; };
		std::vector<float> getTexCoords() { return texCoords; };

	private:
		// Vertex arrays for storing generated objects.
		std::vector<float> vertex, normals, texCoords;

		// To store the texture.
		GLuint texture;

		// Values for calculating vertices and texture co-ordinates.
		float radius, diameter, angle, angle2, interval, latInterval, longInterval, height, bottom, columns, heightInterval;
		float x, x2, y, y2, z, z2, u, v;
		int segments;
		
};
#endif 
