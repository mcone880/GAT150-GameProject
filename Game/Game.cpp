#include "Game.h"
#include "GameComponent/PlayerComponent.h"

void Game::Initialize() {

	//create engine
	engine = std::make_unique<MAC::Engine>();
	engine->Startup();
	engine->Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	//Register Classes
	REGISTER_CLASS(PlayerComponent);

	//Scene
	scene = std::make_unique<MAC::Scene>();
	scene->engine = engine.get();

	MAC::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	MAC::SetFilePath("../Resources");

	rapidjson::Document document;
	bool success = MAC::json::Load("Text/scene.txt", document);
	assert(success);
	scene->Read(document);

	//Actors
	//std::unique_ptr<MAC::Actor> actor = std::make_unique<MAC::Actor>(MAC::Transform{ MAC::Vector2{400,300} });
	//{
	//	auto component = MAC::ObjectFactory::Instance().Create<MAC::SpriteAnimationComponent>("SpriteAnimationComponent");

	//	component->texture = engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Link.png", engine->Get<MAC::Renderer>());
	//	//MAC::SpriteComponent* component = actor->AddComponent<MAC::SpriteComponent>();
	//}
	//{
	//	MAC::PhysicsComponent* component = actor->AddComponent<MAC::PhysicsComponent>();
	//	//component->ApplyForce(MAC::Vector2::right * 200);
	//}

	//std::unique_ptr<MAC::Actor> actor = std::make_unique <MAC::Actor>(MAC::Transform{ MAC::Vector2{400, 300}, 0, 3 });
	//{
	//	auto component = MAC::ObjectFactory::Instance().Create<MAC::SpriteAnimationComponent>("SpriteAnimationComponent");
	//	component->texture = engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Link.png", engine->Get<MAC::Renderer>());

	//	//MAC::SpriteAnimationComponent* component = actor->AddComponent<MAC::SpriteAnimationComponent>();
	//	component->fps = 60;
	//	component->numFramesX = 12;
	//	component->numFramesY = 8;
	//	actor->AddComponent(std::move(component));
	//}
	//scene->AddActor(std::move(actor));

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
