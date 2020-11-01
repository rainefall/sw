#include "Input.h"

namespace SouthwestEngine {
	void Input::Update() {
		if (SDL_NumJoysticks() > 0) {
			if (_joystick == nullptr) {
				_joystick = SDL_JoystickOpen(0);
			}
			SDL_JoystickUpdate();
		}
		else {
			// close joystick object if joystick is disconnected. this might be unnecessary i dont know if SDL does this for you
			if (_joystick != nullptr) {
				SDL_JoystickClose(_joystick);
				_joystick = nullptr;
			}
		}

		// events
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				Southwest::Running = false;
				break;
			default:
				break;
			}
		}
	}
}