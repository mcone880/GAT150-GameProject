#pragma once
#include "../Engine/Object/Actor.h"

class MAC::Texture;

class Pickup : public MAC::Actor {
public:

	Pickup(const MAC::Transform& transform, std::shared_ptr<MAC::Texture> texture) : MAC::Actor{ transform, texture } {}

	void OnCollision(Actor* actor) override;
};


