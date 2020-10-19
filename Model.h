#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "sw.h"

namespace SouthwestEngine {
	class Mesh;
	class Shader;

	// Provides an easy way to load a large number of meshes at once.
	// Note that you may want finer control over the mesh loading if you are planning on assigning custom shaders to individual meshes.
	class Model {
	private:
		Model(std::vector<Mesh*> m);
		~Model();

		// process an aiMesh object, should only be called internally so its private
		static Mesh* processAiMesh(aiMesh* m, const aiScene* scene);
	public:
		// Load a model from a file. Not recommended for production use.
		static Model* FromFile(const char* path);

		std::vector<Mesh*> Meshes;

		Shader* Shader;

		void Draw();
	};
}
#endif