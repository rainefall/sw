#include "Texture.h"

namespace SouthwestEngine {

	Texture::Texture(SDL_Surface* surface) {
		// create texture object
		glActiveTexture(0);
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		// set the texture wrapping/filtering options
		// they most likely wont need to be any different from this cause that nintendo DS aesthetic demands it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load surface data into gl texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture* Texture::FromFile(const char* path) {
		SDL_Surface* surface = IMG_Load(path);
		return new Texture(surface);
	}

	void Texture::Bind() {
		// Bind this texture to opengl texture 0
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}