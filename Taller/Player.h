#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(const float x, const float y, const float velocity);
	~Player();

	void IsMoving(sf::Keyboard::Key key);
	void StopMoving();
	void Update(float dt);

	inline const sf::Sprite GetSprite() const { return sprite; }

private:
	sf::Texture texture;
	sf::Sprite sprite;
	float m_velocity;

	bool isMoving;
	sf::Keyboard::Key keyPressed;

	int frameCount;
	float m_elapsedTime, m_animDuration;
};

