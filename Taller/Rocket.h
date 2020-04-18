#pragma once

#include <SFML/Graphics.hpp>

class Rocket
{
public:
	Rocket(const float x, const float y, const float velocity);
	~Rocket();

	void Update(float dt);

	inline const sf::Sprite GetSprite() const { return sprite; }

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float m_velocity;
	int frameCount;
	float m_elapsedTime, m_animDuration;
};

