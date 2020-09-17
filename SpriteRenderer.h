#pragma once
#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "sw.h"

namespace SouthwestEngine {
	class Sprite;

	class SpriteRenderer {
	private:
		SpriteRenderer();
	public:
		static void Initialize();

		// Draw a sprite
		static void Draw(Sprite* spr);

		// default sprite shader
		static Shader* DefaultShader;

		// vertex buffer object
		static unsigned int VBO;
		// vertex array object
		static unsigned int VAO;
		// element buffer object
		static unsigned int EBO;
	};
}

#endif