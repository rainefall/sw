#include "Input.h"

namespace SouthwestEngine {
	void Input::Update() {
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