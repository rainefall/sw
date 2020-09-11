#pragma once
#ifndef SW_H
#define SW_H

// stl
#include <iostream>
#include <map>
#include <vector>
#include <string>
// c stl
#include <stdio.h>
#include <stdlib.h> 
// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// rapidjson
#include <rapidjson/document.h>

// engine stuff
#include "FileUtils.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Graphics.h"

namespace SouthwestEngine {
	class Southwest {
	private:
		// static class, don't instance
		Southwest(); 
	public:
		// Should the game be running?
		// Ideally you should use this in your main loop to make it, uh, loop
		static bool Running;

		// Initialize engine
		// Returns 0 on success, 1 on failure
		static int Initialize();

		// Shutdown engine
		static void Stop();
	};
}

#endif