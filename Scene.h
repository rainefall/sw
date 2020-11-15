#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "sw.h"

namespace SouthwestEngine {
	class Camera;

	class Scene {
	protected:
		// Active 3D camera
		Camera* MainCamera;
	public:
		// Procedure called when the scene is created (pushed to the stack)
		virtual void OnStart() {};
		// Procedure called when the scene is moved to the top of the stack, either by being pushed there or by the scene above it being popped
		virtual void OnEnter() {};
		// Procedure called every frame
		virtual void Update() {};
		// Procedure called when the scene is no longer the top of the stack
		virtual void OnExit() {};
		// Procedure called when the scene is popped from the stack
		virtual void OnStop() {};

		Camera* GetMainCamera();
		void SetMainCamera(Camera* c);
	};
}

#endif