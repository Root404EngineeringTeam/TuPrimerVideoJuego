#include "Player.h"

#include <iostream>

Player::Player(const float x, const float y, const float velocity) :
	m_velocity(velocity), m_elapsedTime(0.0f), m_animDuration(1.0f), frameCount(2)
{
	bool loaded = texture.loadFromFile("Assets/sprites/ship.png");
	if (!loaded)
	{
		std::cerr << "no se pudo cargar la textura del jugador" << std::endl;
		return;
	}

	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	sf::IntRect spriteRect = sf::IntRect(0, 0, 16, 24);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(8, 12);
	sprite.setScale(2.5f, 2.5f);
}

void Player::IsMoving(sf::Keyboard::Key key)
{
	isMoving = true;
	keyPressed = key;
}

void Player::StopMoving()
{
	isMoving = false;
}

void Player::Update(float dt)
{
	m_elapsedTime += dt;

	if (isMoving)
	{
		switch (keyPressed)
		{
		case sf::Keyboard::Right:
			sprite.move(dt * m_velocity, 0);
			break;
		case sf::Keyboard::Left:
			sprite.move(dt * -m_velocity, 0);
			break;
		}
	}

	int animFrame = static_cast<int> ((m_elapsedTime / m_animDuration) * frameCount) % frameCount;
	sf::IntRect spriteRect = sf::IntRect(0, animFrame * 24, 16, 24);
	sprite.setTextureRect(spriteRect);
}

Player::~Player()
{
}