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
		Texture = nullptr;
		__disposed = false;
	}

	void Sprite::Draw() {
		SpriteRenderer::Draw(this);
	}

	void Sprite::Dispose() {
		if (!__disposed)
			__disposed = true;
	}

	bool Sprite::Disposed() {
		return __disposed;
	}
}