#pragma once
#ifndef RENDERLAYER_H
#define RENDERLAYER_H

namespace SouthwestEngine {
	class RenderLayer {
	private:
		unsigned int FBO, _tex;
	public:
		RenderLayer();
		~RenderLayer();

		// bind this render layer as the currently active framebuffer
		void Bind();
	};
}

#endif