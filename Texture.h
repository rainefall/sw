#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "sw.h"

namespace SouthwestEngine {
	class Texture {
	private:
		Texture(SDL_Surface* surface);

		// Texture's OpenGL ID
		unsigned int ID;
	public:
		// Bind this texture as the current active opengl texture
		void Bind();

		// Load a texture from a file
		static Texture FromFile(const char* path);

		// Create a texture from a bitmap object stored in RAM
		// but i haven't made bitmaps yet!!!!!!!!!!!!!!!!!!!!!!!!
		//static Texture FromBitmap(Bitmap bmp);
	};
}

#endif