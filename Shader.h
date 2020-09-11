#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "sw.h"

namespace SouthwestEngine {
	class Shader {
	private:
		Shader(const char* vert, const char* frag, std::vector<const char*> uniforms );
	public:
		// Create shader from .shader file
		static Shader FromFile(const char* path);

		// Bind this shader as the currently active shader
		void Bind();

		// Map of shader uniforms
		// <Human Readable Name, Internal Uniform ID>
		std::map<const char*, unsigned int> Uniforms;

	};
}

#endif