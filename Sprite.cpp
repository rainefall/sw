#include "Sprite.h"

namespace SouthwestEngine {
	Sprite::Sprite(RenderLayer* layer) {
		// default values
		_renderLayer = layer;
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
		// add to draw list
		_renderLayer->Drawables2D.push_back(this);
	}

	Sprite::Sprite() {
		// default values
		_renderLayer = Graphics::RenderLayers[RENDERLAYER_2D_FOREGROUND];
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
		// add to draw list
		_renderLayer->Drawables2D.push_back(this);
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