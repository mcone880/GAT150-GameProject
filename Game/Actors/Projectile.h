#pragma once
#include "../Engine/Object/Actor.h"

class MAC::Texture;

class Projectile : public MAC::Actor {
public:

	Projectile(const MAC::Transform& transform, std::shared_ptr<MAC::Texture> texture, float speed) : MAC::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 2 };
	float speed{ 300 };
};