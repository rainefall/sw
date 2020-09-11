#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "sw.h"

namespace SouthwestEngine {
	class Sprite {
	public:
		Sprite();

		// the texture to be applied to this sprite
		Texture* Texture;

		// assign a custom shader
		Shader* Shader;
	};
}

#endif
