#include "Rocket.h"

#include <iostream>

Rocket::Rocket(const float x, const float y, const float velocity) :
	m_velocity(velocity), frameCount(2), m_elapsedTime(0.0f), m_animDuration(0.5f)
{
	bool loaded = texture.loadFromFile("Assets/sprites/laser-bolts.png");
	if (!loaded)
	{
		std::cerr << "no se pudo cargar la textura del cohete" << std::endl;
		return;
	}

	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	sf::IntRect spriteRect = sf::IntRect(0, 0, 16, 16);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(8, 8);
}

void Rocket::Update(float dt)
{
	m_elapsedTime += dt;

	int animFrame = static_cast<int> ((m_elapsedTime / m_animDuration) * frameCount) % frameCount;
	sf::IntRect spriteRect = sf::IntRect(animFrame * 16, 0, 16, 16);
	sprite.setTextureRect(spriteRect);

	sprite.move(0, -m_velocity * dt);
}

Rocket::~Rocket()
{
}