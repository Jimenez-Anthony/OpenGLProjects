#include "Sphere.h"

Sphere::Sphere(int prec)
{
	// Vertex Set Up
	setupVertices(prec);

	// Model Set Up
	angle = 0.0f;
	pivotLocation = glm::vec3(0.f, 0.f, 0.f);
	model = glm::translate(glm::mat4(1.0f), pivotLocation);

	
	if (!InitBuffers()) {
		printf("Some buffers not initialized.\n");
	}

}

Sphere::Sphere() {
	setupVertices(48);
}


Sphere::~Sphere()
{
	Vertices.clear();
	Indices.clear();
}

void Sphere::Update(glm::mat4 inmodel)
{
	model = inmodel;

}

glm::mat4 Sphere::GetModel()
{
	return model;
}

void Sphere::Render(GLint posAttribLoc, GLint colAttribLoc)
{
	// Enable vertex attibute arrays for each vertex attrib
	glEnableVertexAttribArray(posAttribLoc);
	glEnableVertexAttribArray(colAttribLoc);

	// Bind your VBO
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	// Set vertex attribute pointers to the load correct data
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Bind your Element Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	// Render
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// Disable vertex arrays
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);
}


bool Sphere::InitBuffers() {


	// For OpenGL 3
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 12 * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	return true;
}

void Sphere::setupVertices(int prec) {

	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { Vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numIndices; i++) { Indices.push_back(0); }

	for (int i = 0; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			float y = (float)cos(toRadians(180.0f - i * 180.f / prec));
			float x = -(float)cos(toRadians(j * 360.0f / prec)) * float(abs(cos(asin(y))));
			float z = (float)sin(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			Vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
		}
	}

	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			Indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			Indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			Indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			Indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			Indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			Indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}

	std::vector<unsigned int> ind = getIndices();
	std::vector<glm::vec3> vert = getVertices();
	std::vector<glm::vec2> tex = getTexCoords();
	std::vector<glm::vec3> norm = getNormals();

	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;

	int numIndices = getNumIndices();
	for (int i = 0; i < numIndices; i++) {
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);

		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}
}

float Sphere::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

int Sphere::getNumVertices() { return numVertices; }
int Sphere::getNumIndices() { return numIndices; }
std::vector<unsigned int> Sphere::getIndices() { return Indices; }
std::vector<glm::vec3>Sphere::getVertices() { return Vertices; }
std::vector<glm::vec2>Sphere::getTexCoords() { return texCoords; }
std::vector<glm::vec3>Sphere::getNormals() { return normals; }
