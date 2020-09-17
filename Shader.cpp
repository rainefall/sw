#include "Shader.h"

namespace SouthwestEngine {

	Shader::Shader(const char* vert, const char* frag, std::map<const char*, const char*> uniforms) {
		Uniforms = uniforms;

		std::string vertsource = FileUtils::Slurp(vert);
		std::string fragsource = FileUtils::Slurp(frag);

		const GLchar* src[] = { Graphics::GLSLHeader.c_str(), vertsource.c_str() };


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
		src[1] = fragsource.c_str();
		glShaderSource(fragmentShader, 2, src, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		_program = glCreateProgram();
		glAttachShader(_program, vertexShader);
		glAttachShader(_program, fragmentShader);
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(_program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	int Shader::Uniform(const char* u) {
		return glGetUniformLocation(_program, Uniforms[u]);
	}

	void Shader::Bind() {
		glUseProgram(_program);
	}

	Shader* Shader::FromFile(const char* path) {
		// parse json
		rapidjson::Document doc;
		doc.Parse(FileUtils::Slurp(path).c_str());


		// check that the json is valid
		//assert(doc.IsObject());
		assert(doc.HasMember("VertexPath"));
		assert(doc.HasMember("FragmentPath"));
		assert(doc.HasMember("Uniforms"));
		assert(doc["VertexPath"].IsString());
		assert(doc["FragmentPath"].IsString());
		assert(doc["Uniforms"].IsObject());
		// all good, probably

		// this is slightly annoying and it may not be the best way to get the strings out of the array
		// it will have to do for now.
		std::map<const char*, const char*> uniforms;
		for (auto& m : doc["Uniforms"].GetObject()) {
			uniforms[m.name.GetString()] = m.value.GetString();
		}


		return new Shader(doc["VertexPath"].GetString(), doc["FragmentPath"].GetString(), uniforms);
	}
}
	