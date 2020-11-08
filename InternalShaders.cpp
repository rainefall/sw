// this method of handling the internal shaders is awful and ideally i should rework it
// possibly by just including the shaders in json
// please help me

#include "InternalShaders.h"

using namespace SouthwestEngine;

bool InternalShaders::compiled;
void InternalShaders::CompileAll() {
	Diffuse = new Shader(Default3DVert, DiffuseSrc,
		std::map<const char*, const char*>({
				std::pair<const char*, const char*>("Camera Projection", "projection"),
				std::pair<const char*, const char*>("Camera Transform", "view"),
				std::pair<const char*, const char*>("Transform", "model")
			}));
	Diffuse->Bind();
	glUniformMatrix4fv(glGetUniformLocation(Diffuse->_program, "projection"), 1, GL_FALSE, glm::value_ptr(Graphics::OrthoProjection));
	compiled = true;
}

const char* InternalShaders::SpriteShaderVert = R"(
in vec2 iPosition;

out vec2 fTexCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(iPosition, 0.0f, 1.0f);
	fTexCoord = iPosition;
}
)";

const char* InternalShaders::SpriteShaderFrag = R"(
in vec2 fTexCoord;

out vec4 oFragCol;

uniform sampler2D tex;

void main() {
	oFragCol = texture(tex, fTexCoord);
	if (oFragCol.a == 0) {
		discard;
	}
}
)";

const char* InternalShaders::RenderLayerShaderVert = R"(
in vec2 iPosition;
in vec2 iTexCoord;
out vec2 fTexCoord;

uniform float depth;

void main() {
	gl_Position = vec4(iPosition, depth, 1.0f);
	fTexCoord = iTexCoord;
}
)";

const char* InternalShaders::RenderLayerShaderFrag = R"(
in vec2 fTexCoord;

out vec4 oFragCol;

uniform sampler2D tex;

void main() {
	oFragCol = texture(tex, fTexCoord);
	if (oFragCol.a == 0) {
		discard;
	}
}
)";

const char* InternalShaders::Default3DVert = R"(
in vec3 iPosition;
in vec3 iNormal;
in vec2 iTexCoord;
in vec4 iVertexColour;

out vec3 fNormal;
out vec2 fTexCoord;
out vec4 fVertexColour;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = projection * view * model * vec4(iPosition, 1.0);
	fNormal = iNormal;
	fTexCoord = iTexCoord;
	fVertexColour = iVertexColour;
}
)";

Shader* InternalShaders::Diffuse;
const char* InternalShaders::DiffuseSrc = R"(
in vec3 fNormal;
in vec2 fTexCoord;
in vec4 fVertexColour;

out vec4 oFragCol;

void main() {
	oFragCol = vec4(1.0);
}
)";