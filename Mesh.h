#pragma once
#ifndef MESH_H
#define MESH_H
#include "sw.h"

namespace SouthwestEngine {
	struct Vertex {
		float Position[3];
		float Normal[3];
		float TexCoord[2];
		float Colour[4];
	};

	class Mesh {
	private:
		unsigned int VAO, VBO, EBO;
	public:
		// create new mesh
		Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind);

		// draw this mesh to the screen
		void Draw();

		// vector of vertices in this mesh
		std::vector<Vertex> Vertices;
	
		// vector of indices in this mesh
		std::vector<unsigned int> Indices;
	};
}
#endif