#include "Compositor.h"

using namespace SouthwestEngine;

Compositor::Compositor() {
	// i dont know why
	// i dont want to know why
	// but i have to put these here otherwise i get multpluy defined symbol errors despite the fact that i am not defining them multiple times
	// god
	const char* DefaultRLShaderVert = R"(
	in vec2 iPosition;
	in vec2 iTexCoord;
	out vec2 TexCoord;

	uniform float depth;

	void main() {
		gl_Position = vec4(iPosition, depth, 1.0f);
		TexCoord = iTexCoord;
	}
	)";

		const char* DefaultRLShaderFrag = R"(
	in vec2 TexCoord;

	out vec4 oFragCol;

	uniform sampler2D tex;

	void main() {
		oFragCol = texture(tex, TexCoord);
		if (oFragCol.a == 0) {
			discard;
		}
	}
	)";

	// a very ugly line of code, but good luck convincing me to change it
	DefaultShader = new Shader(DefaultRLShaderVert, DefaultRLShaderFrag, std::map<const char*, const char*>({ std::pair<const char*, const char*>("Texture", "tex") }));
	glUniform1i(glGetUniformLocation(DefaultShader->_program, "tex"), 0);

	// create screen quad
	// opengl objects
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// screen quad VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Compositor::DrawLayer(RenderLayer* layer) {
	// bind shader
	if (layer->Shader != nullptr) {
		layer->Shader->Bind();
	}
	else {
		DefaultShader->Bind();
	}
	// bind texture and RBO
	layer->Bind();
	// draw screen quad
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}