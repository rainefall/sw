#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "sw.h"

namespace SouthwestEngine {
	class Mesh;
	class Shader;

	class Model {
	private:
		Model(std::vector<Mesh*> m);

		// process an aiMesh object, should only be called internally so its private
		static Mesh* processAiMesh(aiMesh* m, const aiScene* scene);
	public:
		// load a model from a file
		static Model* FromFile(const char* path);

		std::vector<Mesh*> Meshes;

		Shader* Shader;

		void Draw();
	};
}
#endif