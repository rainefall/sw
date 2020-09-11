#include "Shader.h"

namespace SouthwestEngine {

	Shader::Shader(const char* vert, const char* frag, std::vector<const char*> uniforms) {

	}

	void Bind() {

	}

	Shader Shader::FromFile(const char* path) {
		// parse json
		rapidjson::Document doc;
		doc.Parse(FileUtils::ReadEntireFile(path));

		// check that the json is valid
		assert(doc.IsObject());
		assert(doc.HasMember("VertexPath"));
		assert(doc.HasMember("FragmentPath"));
		assert(doc.HasMember("Uniforms"));
		assert(doc["VertexPath"].IsString());
		assert(doc["FragmentPath"].IsString());
		assert(doc["Uniforms"].IsArray());
		// all good, probably

		// this is slightly annoying and it may not be the best way to get the strings out of the array
		// it will have to do for now.
		std::vector<const char*> uniforms;
		for (int i = 0; i < doc["Uniforms"].GetArray().Capacity(); i++) {
			uniforms.push_back(doc["Uniforms"].GetArray()[0].GetString());
		}
			

		return Shader(doc["VertexPath"].GetString(), doc["VertexPath"].GetString(), uniforms);
	}
}