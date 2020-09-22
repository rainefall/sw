#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "sw.h"

namespace SouthwestEngine {
	class Texture;

	// structure holding all the data describing a sprite
	class Sprite : public virtual Drawable2D {
	public:
		// create a new sprite object
		Sprite();

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

		// Draw sprite (aka pass this sprite to the SpriteRenderer instance)
		void Draw() override;
	};
}

#endif
