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
	glVertexAttribPointer(0, 12, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // vert
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 12, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3*sizeof(float))); // vert
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 12, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(6 * sizeof(float))); // vert
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 12, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(8 * sizeof(float))); // vert
	glEnableVertexAttribArray(3);

	// all done!
	glBindVertexArray(0);

	for (unsigned int i = 0; i < Vertices.size(); i++) {
		std::cout << Vertices[i].Position[0] << std::endl;
	}
}

void Mesh::Draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);
}