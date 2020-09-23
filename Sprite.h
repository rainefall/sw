#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "sw.h"

namespace SouthwestEngine {
	class Texture;
	class RenderLayer;

	// structure holding all the data describing a sprite
	class Sprite : public virtual Drawable2D {
	private:
		RenderLayer* _renderLayer;
	public:
		// create a new sprite object
		Sprite();

		// create a new sprite object, specifying a render layer to target
		Sprite(RenderLayer* layer);

		// the texture to be applied to this sprite
		Texture* Texture;

		// sprite X position
		int X;
		// sprite Y position
		int Y;
		// sprite Z position
		float Z;

		// sprite origin x
		int OX;
		// sprite origin y
		int OY;

		// X scale
		float ScaleX;
		// Y scale
		float ScaleY;

		// angle of rotation
		float Angle;

		// returns the render layer this sprite is bound to
		RenderLayer* GetRenderLayer();

		// Draw sprite (aka pass this sprite to the SpriteRenderer instance)
		void Draw() override;
	};
}

#endif
