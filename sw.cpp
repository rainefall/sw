#include "sw.h"


namespace SouthwestEngine {
	bool Southwest::Running;
	char* Southwest::_prefPath;

	int Southwest::Initialize(const char* title, const char* org) {
		// i'd be lying if i said 90% of the boilerplate code here wasn't directly ripped from the old C++ SF engine
		// which was ripped from my old game engine for monster ranger

		if (org == nullptr)
			org = "Tobesoft";

		// absolute favourite part about SDL
		// SDL_Init returns 0 on success
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return 1;
		}
		// IMG_Init does not
		if (IMG_Init(IMG_INIT_PNG) == 0) {
			SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
			return 1;
		}
		// Astounding work.

		// initialize graphics engine
		if (Graphics::Initialize(title) != 0) {
			SDL_Log("Unable to initialize Graphics engine");
			return 1;
		}

		// initialize input engine
		Input::Initialize();
		
		// initialize audio engine
		AudioSystem::Initialize();

		// get platform specific pref path
		// thank you SDL for making this easier
		_prefPath = SDL_GetPrefPath(org, title);

		// we can run the game(!!)
		Running = true;

		return 0;
	}

	void Southwest::Stop() {
		Director::Pop();

		// stop audio engine
		AudioSystem::Stop();
		// stop graphics engine
		Graphics::Stop();

		// Shutdown SDL2
		IMG_Quit();
		SDL_Quit();

		// bye!!
	}

	char* Southwest::GetPrefPath() {
		return _prefPath;
	}
}