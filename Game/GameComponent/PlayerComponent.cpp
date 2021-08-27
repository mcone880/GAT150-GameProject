#include "PlayerComponent.h"
#include "Engine.h"

using namespace MAC;

void PlayerComponent::Create() {
	owner->scene->engine->Get<EventSystem>()->Subscribe("Collision_Enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("Collision_Exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "Audio/hurt.wav");
}

void PlayerComponent::Update() {
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held) {
		force.x -= speed;
	}
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held) {
		force.x += speed;
	}
	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed) {
		force.y -= 200;
	}

	PhysicsComponent* physicsComponent =  owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);
	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);
	if (physicsComponent->velocity.x > 0) spriteAnimationComponent->StartSequence("WalkRight");
	else if (physicsComponent->velocity.x < 0) spriteAnimationComponent->StartSequence("WalkLeft");
	else spriteAnimationComponent->StartSequence("Idle");
}

void PlayerComponent::OnCollisionEnter(const Event& event) {
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (IString_Compare(actor->tag, "ground")) {
		contacts.push_back(actor);
	}
	if (IString_Compare(actor->tag, "enemy")) {
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
	}
}

void PlayerComponent::OnCollisionExit(const Event& event) {
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (IString_Compare(actor->tag, "ground")) {
		contacts.remove(actor);
	}
}

bool PlayerComponent::Write(const rapidjson::Value& value) const {
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value) {
	JSON_READ(value, speed);
	return true;
}