#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**) {

	MAC::Engine engine;
	engine.Startup();
	engine.Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	MAC::Scene scene;
	scene.engine = &engine;

	MAC::SetFilePath("../Resources");

	std::shared_ptr<MAC::Texture> texture = engine.Get<MAC::ResourceSystem>()->Get<MAC::Texture>("sf2.png", engine.Get<MAC::Renderer>());

	for (size_t i = 0; i < 10; i++) {
		MAC::Transform transform{{ MAC::RandomRange(0,800), MAC::RandomRange(0,300) }, MAC::RandomRange(0,360), 1.0f};
		std::unique_ptr<MAC::Actor> actor = std::make_unique<MAC::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}


	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 5.0f;

	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		//Update
		engine.Update();
		quit = (engine.Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == MAC::InputSystem::eKeyState::Pressed);
		scene.Update(engine.time.deltaTime);

		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = 0.1f;

		engine.Get<MAC::Renderer>()->BeginFrame();

		//Draw
		scene.Draw(engine.Get<MAC::Renderer>());
		//MAC::Vector2 position{ 300,400 };
		//engine.Get<MAC::Renderer>()->Draw(texture, position, 45.0f, MAC::Vector2{ 2,2 });

		engine.Get<MAC::Renderer>()->EndFrame();

	}
	
	
	SDL_Quit();
	return 0;
}