#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
//#include "Enemy.h"
#include <memory>

Player::Player(const MAC::Transform& transform, std::shared_ptr<MAC::Texture> texture, float speed) : MAC::Actor{ transform, texture }, speed{ speed } {}

void Player::Initialize() {
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = MAC::Vector2{ 20,0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = MAC::Vector2{ 0,5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = MAC::Vector2{ 0,-5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = MAC::Vector2{ -20,0 };
	AddChild(std::move(locator));
}

void Player::Update(float dt) {

	Actor::Update(dt);

	invincibilityTimer -= dt;
	invincible = (invincibilityTimer <= 0);

	//movement
	float thrust = 0;
	if (scene->engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == MAC::InputSystem::eKeyState::Held) transform.rotation -= 5 * dt;
	if (scene->engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == MAC::InputSystem::eKeyState::Held) transform.rotation += 5 * dt;
	if (scene->engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == MAC::InputSystem::eKeyState::Held) thrust = speed;

	//acceleration
	MAC::Vector2 acceleration;
	acceleration += MAC::Vector2::Rotate(MAC::Vector2::right, transform.rotation) * thrust;

	//gravity
	//MAC::Vector2 gravity = (MAC::Vector2{ 400,300 } - transform.position).Normalized() * 100; //Center Gravity
	//MAC::Vector2 gravity = (MAC::Vector2::down - transform.position).Normalized() * 100; //Down Gravity
	//acceleration += gravity;

	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.99f; //damping

	transform.position.x = MAC::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = MAC::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && scene->engine->Get<MAC::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == MAC::InputSystem::eKeyState::Pressed) {

		fireTimer = fireRate;

		MAC::Transform t = children[0]->transform;
		t.scale = 2;

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/Laser.png", scene->engine->Get<MAC::Renderer>()), 500.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
	}

	std::shared_ptr<MAC::Texture> engineTexture = scene->engine->Get<MAC::ResourceSystem>()->Get<MAC::Texture>("Images/particle01.png", scene->engine->Get<MAC::Renderer>());
	std::vector<MAC::Color> colors = { MAC::Color::blue, MAC::Color::white, MAC::Color::red };
	scene->engine->Get<MAC::ParticleSystem>()->Create(children[3]->transform.position, 50, 0.5f, engineTexture, 50, children[3]->transform.rotation, MAC::DegToRad(30));
}

void Player::OnCollision(Actor* actor) {
	return;
	if (invincible) {
		return;
	}

	/*if (dynamic_cast<Enemy*>(actor)) {
		destroy = true;
		scene->engine->Get<MAC::ParticleSystem>()->Create(transform.position, 200, 1, MAC::Color::red, 50);
		scene->engine->Get<MAC::AudioSystem>()->PlayAudio("explosion");

		MAC::Event event;
		event.name = "PlayerDead";
		event.data = std::string("Ya got slapped");
		scene->engine->Get<MAC::EventSystem>()->Notify(event);
		invincibilityTimer = 2;
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy") {
		
		actor->destroy = true;
		scene->engine->Get<MAC::ParticleSystem>()->Create(transform.position, 200, 1, MAC::Color::red, 50);
		scene->engine->Get<MAC::AudioSystem>()->PlayAudio("explosion");

		MAC::Event event;
		event.name = "PlayerDead";
		event.data = std::string("Ya got slapped");
		scene->engine->Get<MAC::EventSystem>()->Notify(event);
		invincibilityTimer = 2;
	}
	*/
}
