#include "Sprite.h"

namespace SouthwestEngine {
	Sprite::Sprite() {
		X = 0;
		Y = 0;
		Z = 0.0f;
		Graphics::Drawables2D.push_back(this);
	}

	void Sprite::Draw() {
		SpriteRenderer::Draw(this);
	}
}