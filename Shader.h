#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "sw.h"

namespace SouthwestEngine {
	class Shader {
	public:
		Shader(const char* vert, const char* frag, std::map<const char*, const char*> uniforms);

		// opengl id of this shader
		unsigned int _program;

		// will likely remove this later i just kinda want to see if it works
		operator GLuint() { return _program; }

		// Create shader from .shd file
		static Shader* FromFile(const char* path);

		// Bind this shader as the currently active shader
		void Bind();

		// Map of shader uniforms
		// <Human Readable Name, Internal Uniform ID>
		std::map<const char*, GLint> Uniforms;
		
		// get Uniform ID
		GLint Uniform(const char* u);

	};
}

#endif