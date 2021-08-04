#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**) {

	MAC::Engine engine;
	engine.Startup();

	engine.Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	std::cout << MAC::GetFilePath() << std::endl;
	MAC::SetFilePath("../Resources");
	std::cout << MAC::GetFilePath() << std::endl;

	std::shared_ptr<MAC::Texture> texture = engine.Get<MAC::ResourceSystem>()->Get<MAC::Texture>("sf2.png", engine.Get<MAC::Renderer>());

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<MAC::Renderer>()->BeginFrame();

		MAC::Vector2 position{ 300,400 };
		engine.Get<MAC::Renderer>()->Draw(texture, position);

		engine.Get<MAC::Renderer>()->EndFrame();
		

		/*for (int i = 0; i < 2; i++) {

			SDL_Rect src{ 32,64,32,64 };
			SDL_Rect dest{ MAC::RandomIntRange(0,800),MAC::RandomIntRange(0,600), 64, 96};

			SDL_RenderCopy(renderer, texture, &src, &dest);
		}*/
		
	}
	
	
	SDL_Quit();
	return 0;
}