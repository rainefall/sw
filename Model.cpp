#include "Model.h"

using namespace SouthwestEngine;

Model::Model(std::vector<Mesh*> m) {
	Meshes = m;
}

Model::~Model() {
	for (unsigned int i = 0; i < Meshes.size(); i++) {
		delete Meshes[i];
	}
}

void Model::Draw() {
	for (unsigned int i = 0; i < Meshes.size(); i++) {
		//Meshes[i]->Draw();
	}
}

Model* Model::Load(const char* path) {
	// get file and length from archive
	void* buf = malloc(0);
	int len = 0;
	// to do, implement that lol

	return Model::LoadFromMemory(buf, len);
}

Model* Model::LoadFromMemory(void* buf, int len) {
	Assimp::Importer importer;
	// assimp import scene
	const aiScene* scene = importer.ReadFileFromMemory(buf, len,
		//aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		//aiProcess_SortByPType |
		aiProcess_FlipUVs //|
		//aiProcess_OptimizeMeshes |
		//aiProcess_OptimizeGraph
	);

	// if scene import failed, tell me why
	if (!scene) {
		printf("ERROR::ASSIMP - %s\n", importer.GetErrorString());
		return nullptr;
	}
	else {
		std::vector<Mesh*> m;
		processAiNode(&m, scene->mRootNode, scene);
		return new Model(m);
	}
}

Model* Model::LoadFromFile(const char* path) {
#ifndef _DEBUG
	std::cout << "WARNING::LOAD_FROM_FILE: Game is attempting to load 3D model at " << path << ". For security reasons, don't do this." << std::endl;
#endif

	Assimp::Importer importer;

	// assimp import scene
	const aiScene* scene = importer.ReadFile(path,
		//aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		//aiProcess_SortByPType |
		aiProcess_FlipUVs //|
		//aiProcess_OptimizeMeshes |
		//aiProcess_OptimizeGraph
	);

	// if scene import failed, tell me why
	if (!scene) {
		printf("ERROR::ASSIMP - %s\n", importer.GetErrorString());
		return nullptr;
	}
	else {
		std::vector<Mesh*> m;
		processAiNode(&m, scene->mRootNode, scene);
		return new Model(m);
	}
}

void Model::processAiNode(std::vector<Mesh*>* m, aiNode* n, const aiScene* scene) {
	// process meshes
	for (unsigned int i = 0; i < n->mNumMeshes; i++) {
		m->push_back(processAiMesh(scene->mMeshes[n->mMeshes[i]], scene));
	}

	// process child nodes
	for (unsigned int i = 0; i < n->mNumChildren; i++) {
		processAiNode(m, n->mChildren[i], scene);
	}
}

Mesh* Model::processAiMesh(aiMesh* m, const aiScene* scene) {
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;

	for (unsigned int i = 0; i < m->mNumVertices; i++) {
		Vertex vert;
		// vertex position
		vert.Position[0] = m->mVertices[i].x;
		vert.Position[1] = m->mVertices[i].y;
		vert.Position[2] = m->mVertices[i].z;

		// vertex normals
		vert.Normal[0] = m->mNormals[i].x;
		vert.Normal[1] = m->mNormals[i].y;
		vert.Normal[2] = m->mNormals[i].z;

		// texcoords
		// check if we have texture coordinates
		if (m->mTextureCoords[0]) {
			vert.TexCoord[0] = m->mTextureCoords[0][i].x;
			vert.TexCoord[1] = m->mTextureCoords[0][i].y;
		}
		else {
			vert.TexCoord[0] = 0.0f;
			vert.TexCoord[1] = 0.0f;
		}

		// vertex colour
		// check that there are colours
		if (m->mColors[0]) {
			// there is only one colour
			// sorry brom?
			vert.Colour[0] = m->mColors[0][i].r;
			vert.Colour[1] = m->mColors[0][i].g;
			vert.Colour[2] = m->mColors[0][i].b;
			vert.Colour[3] = m->mColors[0][i].a;
		}
		else {
			// default colour white
			vert.Colour[0] = 1.0f;
			vert.Colour[1] = 1.0f;
			vert.Colour[2] = 1.0f;
			vert.Colour[3] = 1.0f;
		}

		// done!
		verts.push_back(vert);
	}

	for (unsigned int i = 0; i < m->mNumFaces; i++) {
		aiFace face = m->mFaces[i];
		// shouldnt be more than 3 indices to a face because triangulate
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			inds.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(verts, inds);
}