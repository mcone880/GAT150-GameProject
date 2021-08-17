#pragma once
#include "Engine.h"


class Game {

public:
	void Initialize();
	void Shutdown();
	void Update();
	void Draw();
	
	bool IsQuit() { return quit; }
public:
	std::unique_ptr<MAC::Engine> engine;
	std::unique_ptr<MAC::Scene> scene;

private:
	bool quit{ false };
	
};