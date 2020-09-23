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

		static Shader Shader;

		// bind this render layer as the currently active framebuffer
		void Bind();
	};
}

#endif