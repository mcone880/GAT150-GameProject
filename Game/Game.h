#pragma once
#include "Engine.h"


class Game {

public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		StartLevel2,
		Game2,
		YouWin,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();
	void Update();
	void Draw();
	
	bool IsQuit() { return quit; }

private:
	void OnAddPoints(const MAC::Event& event);
	void OnPlayerDead(const MAC::Event& event);
	void PlayerPickup(const MAC::Event& event);
	void UpdateStartLevel(float dt);
	void UpdateLevel2(float dt);


public:
	std::unique_ptr<MAC::Engine> engine;
	std::unique_ptr<MAC::Scene> scene;

private:
	bool quit{ false };
	eState state = eState::Title;
	float stateTimer{ 0.0f };

	bool isPointMult{ false };
	size_t pointMult{ 0 };
	size_t score{ 0 };
	size_t lives{ 0 };

	MAC::AudioChannel musicChannel;
	std::shared_ptr<MAC::Texture> textTexture;
};