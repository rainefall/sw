#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "sw.h"

namespace SouthwestEngine {
	class Shader {
	private:
		Shader(const char* vert, const char* frag, std::map<const char*, const char*> uniforms );
	public:
		// opengl id of this shader
		unsigned int _program;

		// will likely remove this later i just kinda want to see if it works
		operator GLuint() { return _program; }

		// Create shader from .shd file
		static Shader* FromFile(const char* path);

		// Bind this shader as the currently active shader
		void Bind();

		// Map of shader uniforms
		// <Human Readable Name, Internal Uniform name>
		std::map<const char*, const char*> Uniforms;
		
		// get Uniform ID
		int Uniform(const char* u);

	};
}

#endif