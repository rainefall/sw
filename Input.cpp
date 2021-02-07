#include "Input.h"

using namespace SouthwestEngine;

SDL_Joystick* Input::p_joystick;
const Uint8* Input::p_SDL_Keyboard;
Uint8* Input::p_keyboard;
Uint8* Input::p_keyboardChange; // Do you need this one to be declared too?
								// Uncertain on if you plan to use it later,
								// so yeah take a declaration...!
int Input::p_arrSize;
int Input::p_mouseButtonState[3];
int Input::p_mouseX;
int Input::p_mouseY;

void Input::Initialize() {
	p_arrSize = 0;
	p_SDL_Keyboard = SDL_GetKeyboardState(&p_arrSize);
	p_keyboard = (Uint8*)malloc(p_arrSize);
	p_keyboardChange = (Uint8*)malloc(p_arrSize);
}

void Input::Update() {
	if (SDL_NumJoysticks() > 0) {
		if (p_joystick == nullptr) {
			p_joystick = SDL_JoystickOpen(0);
		}
		SDL_JoystickUpdate();
	}
	else {
		// close joystick object if joystick is disconnected. this might be unnecessary i dont know if SDL does this for you
		if (p_joystick != nullptr) {
			SDL_JoystickClose(p_joystick);
			p_joystick = nullptr;
		}
	}

	// mouse
	SDL_GetMouseState(&p_mouseX, &p_mouseY);

	// update keyboard state changes
	// i think keyboard input in general might want cleaning up a bit
	for (int i = 0; i < p_arrSize; i++) {
		if (p_keyboard[i] != p_SDL_Keyboard[i]) {
			p_keyboard[i] = p_SDL_Keyboard[i];
			p_keyboardChange[i] = 1 + p_keyboard[i];
		}
		else if (p_keyboardChange[i]) {
			p_keyboardChange[i] = 0;
		}
	}

	// update mouse state changes
	for (int i = 0; i < 3; i++) {
		if (p_mouseButtonState[i] > 1) {
			p_mouseButtonState[i] = 1;
		}
		else if (p_mouseButtonState[i] < 0) {
			p_mouseButtonState[i] = 0;
		}
	}

	// events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			Southwest::Running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			p_mouseButtonState[e.button.button] = 2;
		case SDL_MOUSEBUTTONUP:
			p_mouseButtonState[e.button.button] = -1;
		default:
			break;
		}
	}
}

bool Input::Key(SDL_Scancode key) {
	return (bool)p_SDL_Keyboard[key];
}

bool Input::KeyDown(SDL_Scancode key) {
	return p_keyboardChange[key] == 2;
}

bool Input::KeyUp(SDL_Scancode key) {
	return p_keyboardChange[key] == 1;
}

bool Input::Mouse(int button) {
	return p_mouseButtonState[button] > 0;
}

int Input::MouseX() {
	return p_mouseX;
}

int Input::MouseY() {
	return p_mouseY;
}