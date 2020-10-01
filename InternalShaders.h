#pragma once
#ifndef DEFAULTSHADERS_H
#define DEFAULTSHADERS_H
#include "sw.h"

namespace SouthwestEngine {
	class Shader;

	class InternalShaders {
	private:
		InternalShaders();
		static bool compiled;
	public:
		static void CompileAll();

		static const char* SpriteShaderVert;
		static const char* SpriteShaderFrag;

		static const char* RenderLayerShaderVert;
		static const char* RenderLayerShaderFrag;

		// Standard 3D vertex shader with perspective projection, view & model matrices
		static const char* Default3DVert;
		// Default shading model, diffuse
		static const char* DiffuseSrc;
		// Default shading model, phong (diffuse + specular)
		static const char* PhongSrc;

		// Default diffuse shader
		static Shader* Diffuse;
	};
}
#endif