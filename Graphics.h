#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "sw.h"

namespace SouthwestEngine {
	class RenderLayer;
	class Compositor;

	class Graphics {
	private:
		Graphics(); // instance this class and i will start crying
	public:
		static SDL_Window* SDLWindow;

		static Ogre::Root* OgreRoot;
		static Ogre::RenderWindow* RenderWindow;

		// initalize graphics
		// return 0 on success, 1 on failure
		static int Initialize(const char* wintitle);

		// draw the next frame
		static void Update();

		// stop graphics engine
		static void Stop();
	};
}

#endif