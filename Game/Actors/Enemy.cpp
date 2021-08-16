#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt) {

	Actor::Update(dt);

	if (scene->GetActor<Player>()) {
		MAC::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		MAC::Vector2 forward = MAC::Vector2::Rotate(MAC::Vector2::right, transform.rotation);

		float turnAngle = MAC::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);
		//transform.rotation = MAC::Lerp(transform.rotation, transform.rotation + turnAngle, dt * 2)

		float angle = MAC::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		if (canFire) {
			if (fireTimer <= 0 && angle <= MAC::DegToRad(10)) {

				fireTimer = fireRate;

				MAC::Transform t = transform;
				t.scale = 0.5f;

				std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Laser.png", scene->engine->Get<MAC::Renderer>()), 500.0f);
				projectile->tag = "Enemy";
				scene->AddActor(std::move(projectile));
			}
		}
	}

	transform.position += MAC::Vector2::Rotate(MAC::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = MAC::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = MAC::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor) {
	std::shared_ptr<MAC::Texture> deathTexture = scene->engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/particle01.png", scene->engine->Get<MAC::Renderer>());
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		destroy = true;
		actor->destroy = true;
		scene->engine->Get<MAC::ParticleSystem>()->Create(transform.position, 200, 1,deathTexture, 50);
		scene->engine->Get<MAC::AudioSystem>()->PlayAudio("explosion");

		MAC::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<MAC::EventSystem>()->Notify(event);
	}
}
