#include "Pickup.h"
#include "Player.h"
#include "Engine.h"
#include <memory>

void Pickup::OnCollision(Actor* actor) {
	if (dynamic_cast<Player*>(actor)) {
		destroy = true;
		std::shared_ptr<MAC::Texture> getPickUpTexture = scene->engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Twinkle.png", scene->engine->Get<MAC::Renderer>());
		scene->engine->Get<MAC::ParticleSystem>()->Create(transform.position, 10, 0.5f, getPickUpTexture, 50);
		scene->engine->Get<MAC::AudioSystem>()->PlayAudio("explosion");

		MAC::Event event;
		event.name = "PlayerCollectPickup";
		event.data = "Ya got a pickup";
		scene->engine->Get<MAC::EventSystem>()->Notify(event);
	}
}
