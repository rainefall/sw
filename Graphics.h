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

		// delta time values
		static float _deltaTime;
		static float _lastTick;
	public:
		static SDL_Window* SDLWindow;

		static Ogre::Root* OgreRoot;
		static Ogre::RenderWindow* RenderWindow;

		// time taken for last frame, in milliseconds
		static float DeltaTime();

		// initalize graphics
		// return 0 on success, 1 on failure
		static int Initialize(const std::string wintitle);

		// draw the next frame
		static void Update();

		// stop graphics engine
		static void Stop();
	};
}

#endif