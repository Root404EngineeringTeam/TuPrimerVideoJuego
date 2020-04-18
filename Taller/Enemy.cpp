#include "Enemy.h"

#include <iostream>

Enemy::Enemy(const float x, const float y, const float velocity) :
	m_velocity(velocity), frameCount(2), m_elapsedTime(0.0f), m_animDuration(1.0f)
{
	bool loaded = texture.loadFromFile("Assets/sprites/enemy.png");
	if (!loaded)
	{
		std::cerr << "no se pudo cargar la texture del enemigo" << std::endl;
		return;
	}

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setOrigin(16, 8);
	sprite.setScale(2.5f, 2.5f);

	sf::IntRect spriteRect = sf::IntRect(0, 0, 32, 16);
	sprite.setTextureRect(spriteRect);
}

void Enemy::Update(float dt)
{
	m_elapsedTime += dt;

	int animFrame = static_cast<int> ((m_elapsedTime / m_animDuration) * frameCount) % frameCount;
	sf::IntRect spriteRect = sf::IntRect(animFrame * 32, 0, 32, 16);
	sprite.setTextureRect(spriteRect);

	sprite.move(0, dt * m_velocity);
}

Enemy::~Enemy()
{}