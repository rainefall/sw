#pragma once
#ifndef RENDERLAYER_H
#define RENDERLAYER_H

#define RENDERLAYER_2D_BACKGROUND 0
#define RENDERLAYER_3D 1
#define RENDERLAYER_2D_FOREGROUND 2

#include "sw.h"

namespace SouthwestEngine {
	class Mesh;
	class Camera;
	class Drawable2D;

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
		std::vector<Mesh*> Drawables3D;
		// 3D camera used for drawing 3D objects in this render layer
		Camera* Camera;

		// bind this render layer and draw its contents to the FBO
		void Draw();

		// bind this render layer's textures
		void Bind();
	};
}

#endif