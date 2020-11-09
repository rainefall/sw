#include "Mesh.h"

using namespace SouthwestEngine;

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind) {
	Vertices = vert;
	Indices = ind;

	// generate objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind vertex array object
	glBindVertexArray(VAO);

	// generate vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// generate element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	// the layout of a vertex is
	// position	| normal	| tex	| colour
	// x|y|z	| x|y|z		| u|v	| r|g|b|a
	// they are all stored as floats because there is no point in
	// giving you special access to the vertex data
	// you're not gonna modify it
	// ...
	// ...
	// ..please tell me if you need to modify it

	// vertex attrib info, it will be a miracle if this works first time
	// i may have to change all the vertex attrib stuff at some point because (layout = n) doesnt work in older gl versions
	// but at the same time I DO NOT NEED OLDER GL VERSIONS
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); // normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord)); // tex
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colour)); // colour

	// all done!
	glBindVertexArray(0);

	Graphics::RenderLayers[1]->Drawables3D.push_back(this);
}

Mesh::~Mesh() {
	// delete all objects associated with this mesh
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw(glm::mat4 view, glm::mat4 projection) {
	glm::mat4 mdl = glm::mat4(1.0f);
	mdl = glm::scale(mdl, glm::vec3(1.0f));

	InternalShaders::Diffuse->Bind();
	glUniformMatrix4fv(glGetUniformLocation(InternalShaders::Diffuse->_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(InternalShaders::Diffuse->_program, "model"), 1, GL_FALSE, glm::value_ptr(mdl));
	glUniformMatrix4fv(glGetUniformLocation(InternalShaders::Diffuse->_program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}