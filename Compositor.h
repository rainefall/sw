#pragma once
#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include "sw.h"

namespace SouthwestEngine {
	class RenderLayer;

	class Compositor {
		unsigned int VBO, VAO;
	public:
		// Intended for internal use only.
		Compositor();

		// Default shader used to draw layers to the screen
		Shader* DefaultShader;

		// Draw a render layer
		void DrawLayer(RenderLayer* layer);
	};
}

#endif