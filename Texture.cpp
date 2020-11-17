#include "Texture.h"

namespace SouthwestEngine {

	Texture::Texture(SDL_Surface* surface) {
		Width = surface->w;
		Height = surface->h;

		// create texture object
		glActiveTexture(GL_TEXTURE0);
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

	Texture* Texture::Load(const char* path) {
		// get file and length from archive
		void* buf = malloc(0);
		int len = 0;
		// to do, implement that lol
		
		return Texture::LoadFromMemory(buf, len);
	}

	Texture* Texture::LoadFromMemory(void* buf, int len) {
		SDL_RWops* rw = SDL_RWFromMem(buf, len);
		SDL_Surface* surface = IMG_Load_RW(rw, 1);
		return new Texture(surface);
	}

	Texture* Texture::LoadFromFile(const char* path) {
		SDL_Surface* surface = IMG_Load(path);
		return new Texture(surface);
	}

	void Texture::Bind() {
		// Bind this texture to opengl texture 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}