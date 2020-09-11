#pragma once
#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "sw.h"

namespace SouthwestEngine {
	class Sprite;

	class SpriteRenderer {
	public:
		SpriteRenderer();

		// Draw a sprite
		void Draw(Sprite spr);


		// vertex buffer object
		unsigned int VBO;
		// vertex array object
		unsigned int VAO;
	};
}

#endif