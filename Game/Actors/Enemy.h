#pragma once
#include "../Engine/Object/Actor.h"

class MAC::Texture;

class Enemy : public MAC::Actor {
public:

	Enemy(const MAC::Transform& transform, std::shared_ptr<MAC::Texture> texture, float speed, bool canFire) : MAC::Actor{ transform, texture }, speed{ speed }, canFire{canFire} {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	bool canFire = true;
	float speed{ 300 };
	float fireTimer{ 0 };
	float fireRate{ 1 };
};