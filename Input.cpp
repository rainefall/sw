#include "Input.h"

using namespace SouthwestEngine;

SDL_Joystick* Input::_joystick;
const Uint8* Input::__SDL_Keyboard;
const Uint8* Input::__keyboard;
const Uint8* Input::__keyboardChange; // Do you need this one to be declared too?
									  // Uncertain on if you plan to use it later,
									  // so yeah take a declaration...!

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

	__SDL_Keyboard = SDL_GetKeyboardState(nullptr);

}

bool Input::Key(SDL_Scancode key) {
	return (bool)__SDL_Keyboard[key];
}