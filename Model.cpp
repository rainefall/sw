#include "Model.h"

using namespace SouthwestEngine;

Model::Model(std::vector<Mesh*> m) {
	Meshes = m;
	Graphics::RenderLayers[1]->Drawables3D.push_back(this);
}

void Model ::Draw() {
	for (unsigned int i = 0; i < Meshes.size(); i++) {
		Meshes[i]->Draw();
	}
}

Model* Model::FromFile(const char* path) {
	Assimp::Importer importer;

	// assimp import scene
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_FlipUVs |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph);

	// if scene import failed, tell me why
	if (!scene) {
		printf("ERROR::ASSIMP - %s\n", importer.GetErrorString());
		return nullptr;
	}
	else {
		std::vector<Mesh*> m;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			m.push_back(processAiMesh(scene->mMeshes[i], scene));
		}

		return new Model(m);
	}
}

Mesh* Model::processAiMesh(aiMesh* m, const aiScene* scene) {
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;

	for (unsigned int i = 0; i < m->mNumVertices; i++) {
		Vertex vert;
		// vertex position
		vert.Position[0] = m->mVertices->x;
		vert.Position[1] = m->mVertices->y;
		vert.Position[2] = m->mVertices->z;
		// vertex normals
		vert.Normal[0] = m->mNormals->x;
		vert.Normal[1] = m->mNormals->y;
		vert.Normal[2] = m->mNormals->z;
		// texcoords
		// check if we have texture coordinates
		if (m->mTextureCoords[0]) {
			vert.TexCoord[0] = m->mTextureCoords[0]->x;
			vert.TexCoord[1] = m->mTextureCoords[0]->y;
		}
		// vertex colour
		// check that there are colours
		if (m->mColors[0]) {
			// there is only one colour
			// sorry brom?
			vert.Colour[0] = m->mColors[0]->r;
			vert.Colour[1] = m->mColors[0]->g;
			vert.Colour[2] = m->mColors[0]->b;
			vert.Colour[3] = m->mColors[0]->a;
		}
		// done!
		verts.push_back(vert);
	}

	for (unsigned int i = 0; i < m->mNumFaces; i++) {
		aiFace face = m->mFaces[i];
		// shouldnt be more than 3 indices to a face because triangulate but just in case
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			inds.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(verts, inds);
}