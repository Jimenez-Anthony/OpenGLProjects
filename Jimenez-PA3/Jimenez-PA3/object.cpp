#include "object.h"
//Objuct constructor
Object::Object()
{
	createVertices();
}
//forms the vertices and indices for the triangle
void Object::createVertices() {
	Vertices = {
				{{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
				{{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
				{{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
				{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
				{{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
				{{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
				{{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
				{{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
	};


	Indices = {
	  2, 3, 4,
	  8, 7, 6,
	  1, 5, 6,
	  2, 6, 7,
	  7, 8, 4,
	  1, 4, 8,
	  1, 2, 4,
	  5, 8, 6,
	  2, 1, 6,
	  3, 2, 7,
	  3, 7, 4,
	  5, 1, 8
	};
	for (unsigned int i = 0; i < Indices.size(); i++) {
		Indices[i] = Indices[i] - 1;
	}
}

void Object::Initialize(GLint posAttribLoc, GLint colAttribLoc) {

	// Set up your VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// setting the Vertex VBO
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setting the Index VBO
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	// Computing the model matrix
	// Model orientation
	int random = rand() % 100;
	angle = 1 * 3.1415f / random;

	float tvec1 = glm::linearRand(-5.f, 5.f);
	float tvec2 = glm::linearRand(-5.f, 5.f);
	float tvec3 = glm::linearRand(-2.f, 2.f);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(tvec1, tvec2, tvec3));
	model *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1.0f, .0f));

}
//deconstructs object 
Object::~Object()
{
	Vertices.clear();
	Indices.clear();
}
//updates the objects position based on movement input
void Object::Update(unsigned int dt)
{


	model = glm::translate(model, m_speed);

	//To Do: Extra credit / Grad Only
	//	Make the object move in a circle around the origin

}

glm::mat4 Object::GetModel()
{
	return model;
}

void Object::Render(GLint posAttribLoc, GLint colAttribLoc)
{
	glEnableVertexAttribArray(posAttribLoc);
	glEnableVertexAttribArray(colAttribLoc);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);
}
