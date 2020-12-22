#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "sw.h"

namespace SouthwestEngine {

	class Material : AssetBase {
	private:
		// create material from json string
		Material(const char* string);
		// create blank material
		Material();
	public:
		union MaterialProperty {
			const char* path;
			int i;
			long l;
			float f;
			double d;
		};

		static Material Load(const char* path);
		static Material LoadFromMemory(void* buf, int len);
		static Material LoadFromFile(const char* path);

		std::map<const char*, MaterialProperty> Properties;

		Shader* Shader;
	};
}

#endif