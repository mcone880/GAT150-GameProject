#include "Game.h"
#include "Object/Player.h"

void Game::Initialize() {

	//create engine
	engine = std::make_unique<MAC::Engine>();
	engine->Startup();
	engine->Get<MAC::Renderer>()->Create("GAT150", 800, 600);

	//Scene
	scene = std::make_unique<MAC::Scene>();
	scene->engine = engine.get();

	MAC::SetFilePath("../Resources");

	//Add Audio From Files
	engine->Get<MAC::AudioSystem>()->AddAudio("explosion", "Audio/explosion.wav");
	engine->Get<MAC::AudioSystem>()->AddAudio("cute", "Audio/cute.mp3");
	musicChannel = engine->Get<MAC::AudioSystem>()->PlayAudio("cute", 1, 1, true);

	engine->Get<MAC::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<MAC::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<MAC::EventSystem>()->Subscribe("PlayerCollectPickup", std::bind(&Game::PlayerPickup, this, std::placeholders::_1));
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {

	engine->Update();

	stateTimer += engine->time.deltaTime;

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == MAC::InputSystem::eKeyState::Pressed) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 10;
		pointMult = 0;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateStartLevel(engine->time.deltaTime);
		state = eState::Game;
		break;
	case Game::eState::Game:
		/*if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::StartLevel2;
		}*/
		break;
	case Game::eState::StartLevel2:
		scene->RemoveAllActors();
		UpdateLevel2(engine->time.deltaTime);
		state = eState::Game2;
		break;
	case Game::eState::Game2:
		/*if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::YouWin;
		}*/
		break;
	case Game::eState::YouWin:

		break;
	case Game::eState::GameOver:

		break;
	default:
		break;
	}

	//Update

	if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == MAC::InputSystem::eKeyState::Pressed) {
		quit = true;
	}

	if (engine->Get<MAC::InputSystem>()->GetButtonState((int)MAC::InputSystem::eMouseButton::Left) == MAC::InputSystem::eKeyState::Pressed) {
		MAC::Vector2 position = engine->Get<MAC::InputSystem>()->GetMousePosition();
		//create Particles
		std::shared_ptr<MAC::Texture> clickTexture = engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/particle01.png", engine->Get<MAC::Renderer>());
		engine->Get<MAC::ParticleSystem>()->Create(position, 5, 1, clickTexture, 50);

		//PlayAudio
		engine->Get<MAC::AudioSystem>()->PlayAudio("explosion", 1, MAC::RandomRange(0.2f, 2.0f));
		musicChannel.SetPitch(MAC::RandomRange(0.2f, 2.0f));
	}
	scene->Update(engine->time.deltaTime);
}

void Game::Draw() {
	engine->Get<MAC::Renderer>()->BeginFrame();

	int size = 32;
	std::shared_ptr<MAC::Font> font = engine->Get<MAC::ResourceSystem>()->Get<MAC::Font>("Fonts/ZeldaFont.otf", &size);
	textTexture = std::make_shared<MAC::Texture>(engine->Get<MAC::Renderer>());
	engine->Get<MAC::ResourceSystem>()->Add("textTexture", textTexture);

	switch (state)
	{
	case Game::eState::Title:
	{
		MAC::Transform t;

		t.position = { 400, 300 };
		textTexture->Create(font->CreateSurface("Vectrex", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 400, 400 };
		textTexture->Create(font->CreateSurface("Press Space To Start", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);
	}
		break;
	case Game::eState::StartGame:

		break;
	case Game::eState::StartLevel:
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			scene->RemoveAllActors();
			state = eState::StartGame;
		}
		break;
	case Game::eState::Game:
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			scene->RemoveAllActors();
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartLevel2:
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			scene->RemoveAllActors();
			state = eState::StartGame;
		}
		break;
	case Game::eState::Game2:
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			scene->RemoveAllActors();
			state = eState::StartGame;
		}
		break;
	case Game::eState::YouWin:
	{
		MAC::Transform t;

		t.position = { 320, 100 };
		textTexture->Create(font->CreateSurface("You Win!", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 320, 150 };
		textTexture->Create(font->CreateSurface("Your Score:", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 325, 200 };
		textTexture->Create(font->CreateSurface(std::to_string(score).c_str(), MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		scene->RemoveAllActors();

		t.position = { 320, 300 };
		textTexture->Create(font->CreateSurface("Press R To Restart", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 400, 400 };
		textTexture->Create(font->CreateSurface("Press ESC To Quit", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);
	}
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::GameOver:
	{
		MAC::Transform t;

		t.position = { 320, 400 };
		textTexture->Create(font->CreateSurface("GAME OVER", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		scene->RemoveAllActors();

		t.position = { 400, 400 };
		textTexture->Create(font->CreateSurface("Press Space To Start", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 320, 300 };
		textTexture->Create(font->CreateSurface("Press R To Restart", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		t.position = { 400, 400 };
		textTexture->Create(font->CreateSurface("Press ESC To Quit", MAC::Color{ 1, 1, 1 }));
		engine->Get<MAC::Renderer>()->Draw(textTexture, t);
	}
		if (engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == MAC::InputSystem::eKeyState::Pressed) {
			state = eState::StartGame;
		}
		break;
	default:
		break;
	}

	{
	MAC::Transform t;

	t.position = { 30, 20 };
	textTexture->Create(font->CreateSurface(std::to_string(score).c_str(), MAC::Color{ 1, 1, 1 }));
	engine->Get<MAC::Renderer>()->Draw(textTexture, t);

	t.position = { 750, 20 };
	textTexture->Create(font->CreateSurface(std::to_string(lives).c_str(), MAC::Color{ 1, 1, 1 }));
	engine->Get<MAC::Renderer>()->Draw(textTexture, t);
	}

	if (isPointMult) {
		{
			MAC::Transform t;

			t.position = { 30, 50 };
			textTexture->Create(font->CreateSurface(std::to_string(pointMult).c_str(), MAC::Color{ 1, 1, 1 }));
			engine->Get<MAC::Renderer>()->Draw(textTexture, t);

		}
	}

	//Quit Automatically - if (engine.time.time >= quitTime) quit = true;
	//Slow Time - engine.time.timeScale = 0.1f;

	//Draw
	engine->Draw(engine->Get<MAC::Renderer>());
	scene->Draw(engine->Get<MAC::Renderer>());


	//MAC::Vector2 position{ 300,400 };
	//engine.Get<MAC::Renderer>()->Draw(texture, position, 45.0f, MAC::Vector2{ 2,2 });

	engine->Get<MAC::Renderer>()->EndFrame();
}

void Game::UpdateStartLevel(float dt) {

	std::shared_ptr<MAC::Texture> texture = engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Ship.png", engine->Get<MAC::Renderer>());
	scene->AddActor(std::make_unique<Player>(MAC::Transform{ MAC::Vector2{400.0f,300.0f}, 0.0f, 1.5f }, texture, 300.0f));

	//for (size_t i = 0; i < 2; i++) {
		//scene->AddActor(std::make_unique<Enemy>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Enemy.txt"), 300.0f, true));
	//}
	//scene->AddActor(std::make_unique<Enemy>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Enemy.txt"), 300.0f, false));
	//scene->AddActor(std::make_unique<Pickup>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Pickup.txt")));*/
}

void Game::UpdateLevel2(float dt) {

	/*scene->AddActor(std::make_unique<Player>(MAC::Transform{ MAC::Vector2{400.0f,300.0f}, 0.0f, 3.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("shape.txt"), 300.0f));

	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Enemy>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Enemy.txt"), 300.0f, true));
	}
	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Enemy>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Enemy.txt"), 300.0f, false));
	}
	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Pickup>(MAC::Transform{ MAC::Vector2{MAC::RandomRange(0.0f,800.0f),MAC::RandomRange(0.0f,600.0f)}, MAC::RandomRange(0.0f,MAC::TwoPi), 2.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("Pickup.txt")));
	}*/
}

void Game::OnAddPoints(const MAC::Event& event) {
	if (pointMult > 0) {
		score += (std::get<int>(event.data) * pointMult);
	}
	else {
		score += (std::get<int>(event.data));
	}
}

void Game::OnPlayerDead(const MAC::Event& event) {
	/*lives--;
	if (lives <= 0) {
		std::cout << std::get<std::string>(event.data) << std::endl;
		state = eState::GameOver;
	}
	scene->AddActor(std::make_unique<Player>(MAC::Transform{ MAC::Vector2{400.0f,300.0f}, 0.0f, 3.0f }, engine->Get<MAC::ResourceSystem>()->Get<MAC::Shape>("shape.txt"), 300.0f));*/
}

void Game::PlayerPickup(const MAC::Event& event) {
	pointMult += 3;
	isPointMult = true;
}
