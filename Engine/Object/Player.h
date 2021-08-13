#pragma once
#include "Actor.h"

class MAC::Texture;

class Player : public MAC::Actor {

public:

	Player(const MAC::Transform& transform, std::shared_ptr<MAC::Texture> texture, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:

	float invincibilityTimer{ 2 };
	bool invincible = false;
	float fireTimer{ 0 };
	float fireRate{ 0.5f };
	float speed{ 1600 };
	MAC::Vector2 velocity;
};