#include "sw.h"


namespace SouthwestEngine {
	bool Southwest::Running;
	char* Southwest::_prefPath;

	int Southwest::Initialize(const std::string title = "Southwest Engine", const std::string org = "Tobesoft") {	
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return 1;
		}

		// initialize graphics engine
		if (Graphics::Initialize(title))
			return 1;

		// initialize input engine
		Input::Initialize();
		
		// initialize audio engine
		AudioSystem::Initialize();

		// get platform specific pref path
		// thank you SDL for making this easier
		//_prefPath = SDL_GetPrefPath(org, title);

		// we can run the game(!!)
		Running = true;

		return 0;
	}

	void Southwest::Stop() {
		// stop audio engine
		AudioSystem::Stop();
		// stop graphics engine
		Graphics::Stop();

		// Shutdown SDL2
		SDL_Quit();

		// bye!!
	}

	char* Southwest::GetPrefPath() {
		return _prefPath;
	}
}