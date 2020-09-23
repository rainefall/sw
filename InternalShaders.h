#pragma once
#ifndef DEFAULTSHADERS_H
#define DEFAULTSHADERS_H
const char* DefaultSpriteShaderVert = R"(
in vec2 iPosition;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(iPosition, 0.0f, 1.0f);
	TexCoord = iPosition;
}
)";

const char* DefaultSpriteShaderFrag = R"(
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
#endif