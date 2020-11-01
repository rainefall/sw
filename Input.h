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

		static SDL_Joystick* _joystick;
	public:
		static void Update();
	};
}

#endif