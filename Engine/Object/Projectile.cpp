#include "Projectile.h"
#include "Engine.h"

void Projectile::Update(float dt) {

	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += MAC::Vector2::Rotate(MAC::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = MAC::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = MAC::Wrap(transform.position.y, 0.0f, 600.0f);

	//std::vector<MAC::Color> colors{ MAC::Color::white, MAC::Color::red, MAC::Color::green, MAC::Color::blue, MAC::Color::purple, MAC::Color::cyan, MAC::Color::orange, MAC::Color::yellow };
	//scene->engine->Get<MAC::ParticleSystem>()->Create(transform.position, 50, 0.5f, colors[MAC::RandomIntRange(0, colors.size())], 10);
}