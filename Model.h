#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "sw.h"

namespace SouthwestEngine {
	class Mesh;
	class Shader;

	// Provides an easy way to load a large number of meshes at once.
	// Note that you may want finer control over the mesh loading if you are planning on assigning custom shaders to individual meshes.
	class Model /*: AssetBase*/ {
	private:
		Model(std::vector<Mesh*> m);
		~Model();

		// process an ainode object, should only be called internaly so its private
		static void processAiNode(std::vector<Mesh*>* m, aiNode* n, const aiScene* scene);

		// process an aiMesh object, should only be called internally so its private
		static Mesh* processAiMesh(aiMesh* m, const aiScene* scene);

		glm::mat4 _modelMatrix;
		glm::vec3 _position;
		glm::vec3 _rotation;
	public:
		// Load a model from archive storage
		static Model* Load(const char* path);

		// Load a model from a location in memory
		static Model* LoadFromMemory(void* buf, int len);

		// Load a model from a file. Not recommended for production use.
		static Model* LoadFromFile(const char* path);

		// Move the model
		void Translate(float x, float y, float z);

		// Rotate the model (euler angles)
		void Rotate(float x, float y, float z);

		// Get the model's world X coordinate
		float GetX();

		// Get the model's world Y coordinate
		float GetY();

		// Get the model's world Z coordinate
		float GetZ();

		// Set the model's world X coordinate
		void SetX(float x);

		// Set the model's world Y coordinate
		void SetY(float y);

		// Set the model's world Z coordinate
		void SetZ(float z);

		// Manually set the model matrix
		void SetMatrix(glm::mat4 matrix);

		std::vector<Mesh*> Meshes;

		Shader* Shader;

		void Draw();
	};
}
#endif