#pragma once
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "sw.h"

namespace SouthwestEngine {
	class Scene; // defined here because c++

	class Director {
	private:
		Director();
		// scene stack
		static std::stack<Scene*> __sceneStack;
	public:
		// Push a scene to the top of the stack, this automatically calls the scene's OnStart and OnEnter functions
		static void Push(Scene* scene);
		// Remove the scene at the top of the stack
		static void Pop();
		// Call the update function from the scene at the top of the stack
		static void Update();
	};
}

#endif