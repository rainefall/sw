#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "sw.h"

namespace SouthwestEngine {
	class Input {
	private:
		// There is no need
		// to instance this class
		Input();

		static SDL_Joystick* p_joystick;

		static const Uint8* p_SDL_Keyboard;
		static Uint8* p_keyboard;
		static Uint8* p_keyboardChange;

		static int p_mouseButtonState[3];

		static int p_mouseX, p_mouseY;

		static int p_arrSize;
	public:
		static void Initialize();
		static void Update();

		// keyboard input
		static bool KeyDown(SDL_Scancode key);
		static bool KeyUp(SDL_Scancode key);
		static bool Key(SDL_Scancode key);

		// mouse input
		static bool MouseDown(int button);
		static bool MouseUp(int button);
		static bool Mouse(int button);
		// mouse position
		static int MouseX();
		static int MouseY();
	};
}

#endif