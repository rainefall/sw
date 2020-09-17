#include "SpriteRenderer.h"


namespace SouthwestEngine {
	unsigned int SpriteRenderer::VBO, SpriteRenderer::EBO, SpriteRenderer::VAO; // opengl object
	Shader* SpriteRenderer::DefaultShader; // default shader program

	void SpriteRenderer::Initialize() {
		DefaultShader = Shader::FromFile("Content/Shaders/Sprite.shd");
		DefaultShader->Bind();
		glUniformMatrix4fv(glGetUniformLocation((GLuint)DefaultShader, "projection"), 1, GL_FALSE, glm::value_ptr(Graphics::OrthoProjection));

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
		glm::mat4 mat = glm::mat4(1.0f);
		//mat = glm::translate(mat, glm::vec3(X, Y, Z)); // Z or [1/timecreated]
		mat = glm::scale(mat, glm::vec3(200, 249, 1));

		spr->Texture->Bind();
		if (spr->Shader != nullptr) {
			spr->Shader->Bind();
		}

		DefaultShader->Bind();
		glUniformMatrix4fv(glGetUniformLocation((GLuint)DefaultShader,"model"), 1, GL_FALSE, glm::value_ptr(mat));
			


		// bind & draw sprite
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		if (spr->Shader != nullptr)
			DefaultShader->Bind();// bind default shader again
	}
}