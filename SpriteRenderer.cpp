#include "SpriteRenderer.h"

namespace SouthwestEngine {
	unsigned int SpriteRenderer::VBO, SpriteRenderer::EBO, SpriteRenderer::VAO; // opengl object
	Shader* SpriteRenderer::DefaultShader; // default shader program

	void SpriteRenderer::Initialize() {
		// create default shader
		DefaultShader = new Shader(
			InternalShaders::SpriteShaderVert, InternalShaders::SpriteShaderFrag, 
			std::map<const char*, const char*>({
				std::pair<const char*, const char*>("Projection Matrix", "projection"),
				std::pair<const char*, const char*>("Transform", "model"),
				std::pair<const char*, const char*>("Texture", "tex"),
			}));
		// set ortho matrix on default shader
		DefaultShader->Bind();
		glUniformMatrix4fv(glGetUniformLocation(DefaultShader->_program,"projection"), 1, GL_FALSE, glm::value_ptr(Graphics::OrthoProjection));
		glUniform1i(glGetUniformLocation(DefaultShader->_program, "tex"), 0);

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

		// generate objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// bind vertex array object
		glBindVertexArray(VAO);

		// generate vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// generate element buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// vertex attrib
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // vert
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void SpriteRenderer::Draw(Sprite* spr) {
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

		spr->Texture->Bind();

		if (spr->Shader != nullptr) {
			spr->Shader->Bind();
		}
		else {
			DefaultShader->Bind();
		}
		
		glUniformMatrix4fv(glGetUniformLocation(DefaultShader->_program,"model"), 1, GL_FALSE, glm::value_ptr(mat));

		// bind & draw sprite
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}