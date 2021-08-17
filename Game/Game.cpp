#include "Game.h"

void Game::Initialize() {

	//create engine
	engine = std::make_unique<MAC::Engine>();
	engine->Startup();
	engine->Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	//Scene
	scene = std::make_unique<MAC::Scene>();
	scene->engine = engine.get();

	MAC::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	MAC::SetFilePath("../Resources");

	//Actors
	std::unique_ptr<MAC::Actor> actor = std::make_unique<MAC::Actor>(MAC::Transform{ MAC::Vector2{400,300} });
	{
		std::unique_ptr<MAC::SpriteComponent> component = std::make_unique<MAC::SpriteComponent>();
		component->texture = engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/sf2.png", engine->Get<MAC::Renderer>());
		actor->AddComponent(std::move(component));
	}
	{
		std::unique_ptr<MAC::PhysicsComponent> component = std::make_unique<MAC::PhysicsComponent>();
		component->ApplyForce(MAC::Vector2::right * 200);
		actor->AddComponent(std::move(component));
	}
	scene->AddActor(std::move(actor));
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {

	engine->Update();

	if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == MAC::InputSystem::eKeyState::Pressed) {
		quit = true;
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw() {
	engine->Get<MAC::Renderer>()->BeginFrame();

	//Draw
	engine->Draw(engine->Get<MAC::Renderer>());
	scene->Draw(engine->Get<MAC::Renderer>());

	engine->Get<MAC::Renderer>()->EndFrame();
}
