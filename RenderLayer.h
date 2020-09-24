#pragma once
#ifndef RENDERLAYER_H
#define RENDERLAYER_H

#include "sw.h"

namespace SouthwestEngine {
	class RenderLayer {
	private:
		unsigned int FBO, _tex, RBO;
	public:
		RenderLayer();
		~RenderLayer();

		// 0 if layer has not changed, 1 if layer has changed, set to 2 to force update every frame
		unsigned int Updated;

		// shader used to draw this layer to the screen
		Shader* Shader;

		// list of drawable 2D objects in this render layer
		std::vector<Drawable2D*> Drawables2D;

		// list of drawable 3D objects in this render layer
		//std::vector<Drawable3D*> Drawables3D;

		// bind this render layer and draw its contents to the FBO
		void Draw();

		// bind this render layer's textures
		void Bind();
	};
}

#endif