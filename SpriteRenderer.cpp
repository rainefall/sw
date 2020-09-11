#include "SpriteRenderer.h"


namespace SouthwestEngine {
	SpriteRenderer::SpriteRenderer() {

	}

	void SpriteRenderer::Draw(Sprite spr) {
		spr.Texture->Bind();
		if (spr.Shader != nullptr)
			spr.Shader->Bind();

		// draw sprite

		if (spr.Shader != nullptr)
			// bind default shader again
	}
}