#pragma once
#ifndef SW_H
#define SW_H

// stl
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

// Utils
#include "FileUtils.h"
// Graphics: Common
#include "InternalShaders.h"
#include "Shader.h"
#include "Texture.h"
// Graphics: 3D
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
// Graphics: 2D
#include "Drawable2D.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
// Graphics: Layers
#include "RenderLayer.h"
#include "Compositor.h"
// Core
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
		static int Initialize(const char* wintitle);

		// Shutdown engine
		static void Stop();
	};
}

#endif