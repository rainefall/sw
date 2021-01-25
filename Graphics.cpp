#include "Graphics.h"
#include "SDL2/SDL_syswm.h"

namespace SouthwestEngine {
	// define static variables
	// ogre root node
	Ogre::Root* Graphics::OgreRoot;
	SDL_Window* Graphics::SDLWindow;
	Ogre::RenderWindow* Graphics::RenderWindow;
	float Graphics::_deltaTime;
	float Graphics::_lastTick;

	int Graphics::Initialize(const std::string wintitle) {
		SDLWindow = SDL_CreateWindow(wintitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_RESIZABLE);

		SDL_SysWMinfo wmInfo;
		SDL_GetVersion(&wmInfo.version);

		if (!SDL_GetWindowWMInfo(SDLWindow, &wmInfo))
		{
			Ogre::LogManager::getSingleton().logMessage(Ogre::String("Couldn't get WM info"));
		}

		Ogre::String winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.win.window);
		Ogre::NameValuePairList params;
		params["externalWindowHandle"] = winHandle;

		OgreRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "ogre.log");
		if (!OgreRoot->showConfigDialog(nullptr))
			return 1;

		OgreRoot->initialise(false);

		// create main window
		RenderWindow = OgreRoot->createRenderWindow(wintitle, 960, 540, false, &params);

		_lastTick = SDL_GetTicks();
		return 0;
	}

	void Graphics::Update() {
		OgreRoot->renderOneFrame();
		_deltaTime = SDL_GetTicks() - _lastTick;
		_lastTick = SDL_GetTicks();
	}

	void Graphics::Stop() {
		RenderWindow->destroy();
		OgreRoot->shutdown();
		// destroy sdl window
		SDL_DestroyWindow(SDLWindow);
	}

	float Graphics::DeltaTime() {
		return _deltaTime;
	}
}