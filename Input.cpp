#include "Input.h"

using namespace SouthwestEngine;

SDL_Joystick* Input::_joystick;
const Uint8* Input::__SDL_Keyboard;
Uint8* Input::__keyboard;
Uint8* Input::__keyboardChange; // Do you need this one to be declared too?
									  // Uncertain on if you plan to use it later,
									  // so yeah take a declaration...!
int Input::__arrSize;

void Input::Initialize() {
	__arrSize = 0;
	__SDL_Keyboard = SDL_GetKeyboardState(&__arrSize);
	__keyboard = (Uint8*)malloc(__arrSize);
	__keyboardChange = (Uint8*)malloc(__arrSize);
}

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

	for (int i = 0; i < __arrSize; i++) {
		if (__keyboard[i] != __SDL_Keyboard[i]) {
			__keyboard[i] = __SDL_Keyboard[i];
			__keyboardChange[i] = 1 + __keyboard[i];
		}
		else if (__keyboardChange[i]) {
			__keyboardChange[i] = 0;
		}
	}
}

bool Input::Key(SDL_Scancode key) {
	return (bool)__SDL_Keyboard[key];
}

bool Input::KeyDown(SDL_Scancode key) {
	return __keyboardChange[key] == 2;
}

bool Input::KeyUp(SDL_Scancode key) {
	return __keyboardChange[key] == 1;
}