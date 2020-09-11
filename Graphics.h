#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "sw.h"

namespace SouthwestEngine {
	class Sprite; // don't ask

	class Graphics {
	private:
		Graphics(); // instance this class and i will start crying
	public:
		// SDL window pointer
		static SDL_Window* SDL_Window;
		// SDL OpenGLContext pointer
		static SDL_GLContext SDL_GLContext;

		// Time passed since previous frame in milliseconds
		// Use this to make sure the game speed is not tied to the frame rate
		static Uint32 DeltaTime;

		// initalize graphics
		// return 0 on success, 1 on failure
		static int Initialize();

		// draw the next frame
		static void Update();

		// stop graphics engine
		static void Stop();


		// Sprite renderer, renders the sprites
		static SpriteRenderer SpriteRenderer;

		// vector containing all the sprites that currently exist
		static std::vector<Sprite> Sprites;
	};
}

#endif