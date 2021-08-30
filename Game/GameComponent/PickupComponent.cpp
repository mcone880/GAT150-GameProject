#include "PickupComponent.h"
#include "Engine.h"

using namespace MAC;

PickupComponent::~PickupComponent() {
		owner->scene->engine->Get<EventSystem>()->Unsubscribe("Collision_Enter", owner);
}

void PickupComponent::Create() {
	owner->scene->engine->Get<EventSystem>()->Subscribe("Collision_Enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "Audio/coin.wav");
}

void PickupComponent::Update() {

}

void PickupComponent::OnCollisionEnter(const MAC::Event& event) {
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (IString_Compare(actor->tag, "player")) {
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		owner->destroy = true;
	}
}

bool PickupComponent::Write(const rapidjson::Value& value) const {
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value) {
	return true;
}
