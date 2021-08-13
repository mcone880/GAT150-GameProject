#include "Texture.h"
#include "SDL_Image.h"
#include "Graphics/Renderer.h"
#include <iostream>
#include <cassert>

namespace MAC {

	Texture::Texture(Renderer* renderer) {
		assert(renderer);
		this->renderer = renderer->renderer;
	}


	bool Texture::Create(SDL_Surface* surface) {
		assert(surface);
		//create texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) {
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return false;
	}

	bool Texture::Load(const std::string& name, void* data)
	{
		assert(data);
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

	Vector2 Texture::GetSize() const
	{
		SDL_Point point;
		SDL_QueryTexture(texture, nullptr, nullptr, &point.x, &point.y);

		return Vector2{ point.x, point.y };
	}
}