#include "Sprite.h"

namespace SouthwestEngine {
	Sprite::Sprite() {
		// default values
		X = 0;
		Y = 0;
		Z = 0.0f;
		OX = 0;
		OY = 0;
		Angle = 0.0f;
		ScaleX = 1.0f;
		ScaleY = 1.0f;
		// add to draw list
		Graphics::Drawables2D.push_back(this);
	}

	void Sprite::Draw() {
		SpriteRenderer::Draw(this);
	}
}