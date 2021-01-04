#include "SpriteRenderer.h"

namespace SouthwestEngine {
	void SpriteRenderer::Initialize() {
		// opengl objects
		float vertices[] = {
				1.0f, 0.0f, // top right
				1.0f, 1.0f, // bottom right
				0.0f, 1.0f, // bottom left
				0.0f, 0.0f  // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
	}

	void SpriteRenderer::Draw(Sprite* spr) {
		/*
		// transformation matrix
		glm::mat4 mat = glm::mat4(1.f);
		// translate
		mat = glm::translate(mat, glm::vec3(spr->X-spr->OX * spr->ScaleX, spr->Y-spr->OY * spr->ScaleY, spr->Z)); // Z or [1/timecreated]
		// rotation about (OX,OY)
		mat = glm::translate(mat, glm::vec3(spr->OX * spr->ScaleX, spr->OY * spr->ScaleY, 0.f));
		mat = glm::rotate(mat, spr->Angle, glm::vec3(0.f, 0.f, 1.f));
		mat = glm::translate(mat, glm::vec3(-spr->OX * spr->ScaleX, -spr->OY * spr->ScaleY, 0.f));
		// scale
		mat = glm::scale(mat, glm::vec3((float)spr->Texture->GetWidth() * spr->ScaleX, (float)spr->Texture->GetHeight() * spr->ScaleY, 1));
		*/
	}
}