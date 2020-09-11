#include "Graphics.h"

namespace SouthwestEngine {
	// define static variables
	SDL_Window* Graphics::SDL_Window;
	SDL_GLContext Graphics::SDL_GLContext;
	Uint32 Graphics::DeltaTime;

	int Graphics::Initialize() {
		// SDL OpenGL setup
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// create SDL window
		SDL_Window = SDL_CreateWindow("Southwest Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
		if (!SDL_Window) {
			SDL_Log("Unable to create SDL Window: %s", SDL_GetError());
			return 1;
		}

		// create SDL OpenGLContext
		SDL_GLContext = SDL_GL_CreateContext(SDL_Window);
		if (!SDL_GLContext) {
			SDL_Log("Unable to create SDL OpenGLContext: %s", SDL_GetError());
			return 1;
		}

		// it took me far to long to realise that you're supposed to call this function AFTER creating an opengl context
		// smoothbrain
		if (SDL_GL_SetSwapInterval(1) != 0) // vsync
			SDL_Log("Changing the OpenGL Swap Interval is not supported! This may mean vsync is not supported.");

		// init glew
		glewExperimental = GL_TRUE;
		glewInit();

		// gonna have to change a lot of this i imagine
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_MULTISAMPLE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		// we can show the window now(!!!)
		SDL_ShowWindow(SDL_Window);
		// update the window so that it isnt white
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(SDL_Window);
		DeltaTime = 0;

		// success!
		return 0;
	}

	void Graphics::Update() {
		Uint32 start = SDL_GetTicks();

		// clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// to do: render things!
		for(unsigned int i = 0; i < Sprites.size(); i++)
		{
			SpriteRenderer.Draw(Sprites[i]);
		}

		// present frame
		SDL_GL_SwapWindow(SDL_Window);

		// calculate delta time
		DeltaTime = SDL_GetTicks() - start;
	}

	void Graphics::Stop() {
		// Delete OpenGL context
		SDL_GL_DeleteContext(SDL_GLContext);

		// Destroy SDL Window
		SDL_DestroyWindow(SDL_Window);
	}
}