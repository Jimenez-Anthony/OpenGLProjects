#ifndef PYRAMID_H
#define PYRAMID_H

#include <vector>
#include "graphics_headers.h"

class Pyramid {
	public:
		Pyramid();
		~Pyramid();

		void setupVertices();
		void Initialize(GLint, GLint);
		void setupBuffers();
		void setupModelMatrix(glm::vec3, float, float);
		void Render(GLint, GLint);
		void Update(unsigned int dt);

		void setSpeed(glm::vec3 spd) { m_speed = spd; }

		glm::mat4 GetModel();


	private:
		glm::mat4 pyramidModel;
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		glm::vec3 pivotLocation;

		GLuint vao;

		GLuint VB;
		GLuint IB;

		glm::vec3 m_speed = glm::vec3(0., 0., 0.);

		float angle;
};

#endif