#include "Director.h"

using namespace SouthwestEngine;

std::stack<Scene*> Director::__sceneStack;

Director::Director() {

}

void Director::Push(Scene* scene) {
	// call current scene's on exit function if applicable
	if (!__sceneStack.empty()) {
		__sceneStack.top()->OnExit();
	}
	__sceneStack.push(scene);
	__sceneStack.top()->OnStart();
	__sceneStack.top()->OnEnter();
}

void Director::Pop() {
	__sceneStack.top()->OnExit();
	__sceneStack.top()->OnStop();
	delete __sceneStack.top();
	__sceneStack.pop();
	// call current scene's on enter function if applicable
	if (!__sceneStack.empty()) {
		__sceneStack.top()->OnEnter();
	}
}

void Director::Update() {
	if (!__sceneStack.empty()) {
		__sceneStack.top()->Update();
	}
}