#include "Graphics.h"

namespace SouthwestEngine {
	// define static variables

	// SDL window pointer
	SDL_Window* Graphics::SDL_Window;
	// SDL OpenGL Context pointer
	SDL_GLContext Graphics::SDL_GLContext;
	// time passed since last frame
	Uint32 Graphics::DeltaTime;
	// list of render layers
	std::vector<RenderLayer*> Graphics::RenderLayers;
	// compositor, stacks the render layers together
	Compositor* Graphics::Compositor_;
	// ortho projection matrix for sprites
	glm::mat4 Graphics::OrthoProjection;
	// header for all shader source code, used for compatibility with older GL versions or GLES
	std::string Graphics::GLSLHeader;

	// temp debug code
	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	int Graphics::Initialize(const char* wintitle) {
		// SDL OpenGL setup
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);


		// create SDL window
		SDL_Window = SDL_CreateWindow(wintitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

		// projection for 2d drawing
		OrthoProjection = glm::ortho(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

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
#if _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
#endif
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		// create GLSL Header
		GLSLHeader = "#version "; // Every GLSL program gotta start with this!
		int gl_major, gl_minor;
		glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
		glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
		const int glVersion = gl_major * 100 + gl_minor * 10;
		if ((gl_major == 3 && gl_minor == 3) || gl_major > 3) {
			GLSLHeader += std::to_string(gl_major) + std::to_string(gl_minor) + "0 core\n"; // modern opengl, use gl version as glsl version
		}
		else {
			// old opengl, use glsl version number
			if (gl_major == 3) {
				if (gl_minor == 2) {
					GLSLHeader += "150 core\n";
				}
				else if (gl_minor == 1) {
					GLSLHeader += "140\n";
				}
				else if (gl_minor == 0) {
					GLSLHeader += "130\n";
				}
			}
			else if (gl_major == 2 || gl_major == 0) {
				if (gl_minor == 1 || gl_minor == 10) {
					GLSLHeader += "120\n";
				}
				else if (gl_minor == 0) {
					GLSLHeader += "110\n";
				}
				// backwards compatibility stuff
				// write shaders for GLSL 1.3+
				// they should work on 1.1 and 1.2 as long as you dont use anything new
				GLSLHeader +=
					"#define in varying\n\
					#define out varying\n\
					#define texture texture2D\n\
					#define aVertex gl_Vertex\n\
					#define aNormal gl_Normal\n\
					#define aTexCoord gl_MultiTexCoord0\n\
					#define oFragColor gl_FragColor\n";
			}
			else {
				std::cout << "Unsupported OpenGL version! (How did you get here????)\n";
			}
		}

		if (!GLEW_ARB_framebuffer_object) {
			std::cout << "This GPU does not support Framebuffer Objects!\n";
			return 1;
		}

		InternalShaders::CompileAll();

		// inititalize compositor
		Compositor_ = new Compositor();
		RenderLayers.push_back(new RenderLayer()); // 2D foreground
		RenderLayers.push_back(new RenderLayer()); // 3D

		// intialize sprite renderer
		SpriteRenderer::Initialize();

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

		// render layers
		for(unsigned int i = 0; i < RenderLayers.size(); i++)
		{
			// only redraw the render layer if something on there has changed
			if (RenderLayers[i]->Updated > 0)
				RenderLayers[i]->Draw();
		}

		// clear screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (unsigned int i = 0; i < RenderLayers.size(); i++) {
			Compositor_->DrawLayer(RenderLayers[i]);
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