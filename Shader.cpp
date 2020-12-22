#include "Shader.h"

namespace SouthwestEngine {

	Shader::Shader(const char* vert, const char* frag, std::map<const char*, const char*> uniforms) {
		// create source code array with GLSL headers
		const GLchar* src[] = { Graphics::GLSLHeader.c_str(), vert };

		// compile shader
		unsigned int vertexShader, fragmentShader;

		// vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 2, src, NULL);
		glCompileShader(vertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		src[1] = frag;
		glShaderSource(fragmentShader, 2, src, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(program);

		for (auto& u : uniforms) {
			Uniforms.insert(std::pair<const char*, GLint>(u.first, glGetUniformLocation(program,u.second)));
		}
	}

	/*
	GLint Shader::Uniform(const char* u) {
		return glGetUniformLocation(program, Uniforms[u]);
	}
	*/

	void Shader::Bind() {
		glUseProgram(program);
	}

	Shader* Shader::FromFile(const char* path) {
		// parse json
		rapidjson::Document doc;
		doc.Parse(FileUtils::Slurp(path).c_str());

		// you should check that the json is valid

		// this is slightly annoying and it may not be the best way to get the strings out of the array
		// it will have to do for now.
		std::map<const char*, const char*> uniforms;
		for (auto& m : doc["Uniforms"].GetObject()) {
			uniforms.insert(std::pair<const char*, const char*>(m.name.GetString(), m.value.GetString()));
		}

		return new Shader(FileUtils::Slurp(doc["VertexPath"].GetString()).c_str(), FileUtils::Slurp(doc["FragmentPath"].GetString()).c_str(), uniforms);
	}
}
	