#include "Sprite.h"

namespace SouthwestEngine {
	Sprite::Sprite() {
		Graphics::Drawables2D.push_back(this);
	}

	void Sprite::Draw() {
		SpriteRenderer::Draw(this);
	}
}