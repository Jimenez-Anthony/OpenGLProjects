#include "Pyramid.h"

Pyramid::Pyramid()
{
	setupVertices();
}

void Pyramid::setupVertices() {
	Vertices = {
		{{.0f, 2.f, .0f}, {1,1,1}},
		{{1.0f, .0f, 1.0f}, {0,1,0}},
		{{-1.0f, .0f, 1.0f}, {0,0,1}},
		{{-1.0f, .0f, -1.0f}, {1,0,0}},
		{{1.0f, .0f, -1.0f}, {0,0,1}}
	};

	Indices = {
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,
		1,2,3,
		3,4,1
	};
}

void Pyramid::setupBuffers() {
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

glm::mat4 Pyramid::GetModel()
{
	return pyramidModel;
}

void Pyramid::setupModelMatrix(glm::vec3 pivot, float angle, float scale) {
	pivotLocation = pivot;
	pyramidModel = glm::translate(glm::mat4(1.0f), pivotLocation);
	pyramidModel *= glm::rotate(glm::mat4(1.f), angle, glm::vec3(0., 1., 0));
	pyramidModel *= glm::scale(glm::vec3(scale, scale, scale));
}

void Pyramid::Render(GLint positionAttribLoc, GLint colorAttribLoc) {
	glEnableVertexAttribArray(positionAttribLoc);
	glEnableVertexAttribArray(colorAttribLoc);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(positionAttribLoc);
	glDisableVertexAttribArray(colorAttribLoc);

}

void Pyramid::Initialize(GLint posAttribLoc, GLint colAttribLoc) {

	// Set up your VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// setting the Vertex VBO
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setting the Index VBO
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	// Computing the model matrix
	// Model orientation
	angle = 1 * 3.1415f;

	float tvec1 = glm::linearRand(-5.f, 5.f);
	float tvec2 = glm::linearRand(-5.f, 5.f);
	float tvec3 = glm::linearRand(-2.f, 2.f);

	pyramidModel = glm::translate(glm::mat4(1.0f), glm::vec3(tvec1, tvec2, tvec3));
	pyramidModel *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1.0f, .0f));

}


void Pyramid::Update(unsigned int dt)
{


	pyramidModel = glm::translate(pyramidModel, m_speed);

	//To Do: Extra credit / Grad Only
	//	Make the object move in a circle around the origin

}

Pyramid::~Pyramid()
{
	Vertices.clear();
	Indices.clear();
}