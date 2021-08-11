#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cassert>

int main(int, char**) {
	
	MAC::Engine engine;
	engine.Startup();
	engine.Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	MAC::Scene scene;
	scene.engine = &engine;

	MAC::SetFilePath("../Resources");

	engine.Get<MAC::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine.Get<MAC::AudioSystem>()->AddAudio("cute", "audio/cute.mp3");
	MAC::AudioChannel channel = engine.Get<MAC::AudioSystem>()->PlayAudio("cUte", 1, 1, true);

	std::shared_ptr<MAC::Texture> texture = engine.Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/sf2.png", engine.Get<MAC::Renderer>());

	for (size_t i = 0; i < 1; i++) {
		MAC::Transform transform{{ MAC::RandomRange(0,800), MAC::RandomRange(0,300) }, MAC::RandomRange(0,360), 1.0f};
		std::unique_ptr<MAC::Actor> actor = std::make_unique<MAC::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}


	bool quit = false;
	SDL_Event event;
	//Quit Automatically - float quitTime = engine.time.time + 5.0f;

	//Font Time Baby
	// get font from resource system
	int size = 64;
	std::shared_ptr<MAC::Font> font = engine.Get<MAC::ResourceSystem>()->Get<MAC::Font>("Fonts/ZeldaFont.otf", &size);

	// create font texture
	std::shared_ptr<MAC::Texture> textTexture = std::make_shared<MAC::Texture>(engine.Get<MAC::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("hello world", MAC::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine.Get<MAC::ResourceSystem>()->Add("textTexture", textTexture);



	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		//Update
		engine.Update();
		scene.Update(engine.time.deltaTime);


		if (engine.Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == MAC::InputSystem::eKeyState::Pressed) {
			quit = true;
		}

		if (engine.Get<MAC::InputSystem>()->GetButtonState((int)MAC::InputSystem::eMouseButton::Left) == MAC::InputSystem::eKeyState::Pressed) {
			MAC::Vector2 position = engine.Get<MAC::InputSystem>()->GetMousePosition();
			//create Particles
			std::shared_ptr<MAC::Texture> clickTexture = engine.Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/particle01.png", engine.Get<MAC::Renderer>());
			engine.Get<MAC::ParticleSystem>()->Create(position, 5, 1, clickTexture, 50);

			//PlayAudio
			engine.Get<MAC::AudioSystem>()->PlayAudio("explosion", 1, MAC::RandomRange(0.2f,2.0f));
			channel.SetPitch(MAC::RandomRange(0.2f, 2.0f));
			//std::cout << position.x << " " << position.y << std::endl;
		}

		//Quit Automatically - if (engine.time.time >= quitTime) quit = true;
		//Slow Time - engine.time.timeScale = 0.1f;

		engine.Get<MAC::Renderer>()->BeginFrame();

		//Draw
		engine.Draw(engine.Get<MAC::Renderer>());
		scene.Draw(engine.Get<MAC::Renderer>());


		MAC::Transform t;
		t.position = { 30, 30 };

		engine.Get<MAC::Renderer>()->Draw(textTexture, t);
		//MAC::Vector2 position{ 300,400 };
		//engine.Get<MAC::Renderer>()->Draw(texture, position, 45.0f, MAC::Vector2{ 2,2 });

		engine.Get<MAC::Renderer>()->EndFrame();

	}
	
	SDL_Quit();
	return 0;
}