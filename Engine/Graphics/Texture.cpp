#include "Texture.h"
#include "SDL_Image.h"
#include "Graphics/Renderer.h"
#include <iostream>

namespace MAC {

	bool Texture::Load(const std::string& name, void* data)
	{
		renderer = static_cast<Renderer*>(data)->renderer;

		//load surface
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (!surface) {
			std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return false;
		}

		//create texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) {
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return false;
	}
}