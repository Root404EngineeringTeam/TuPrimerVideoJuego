#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Rocket.h"
#include "Enemy.h"

class Game
{
public:
	Game(const std::string& title, const int width, const int height);
	~Game();

	void Update(float dt);
	void Render();
	int Run();

private:
	void SpawnRocket();

	sf::VideoMode m_videoMode;
	sf::RenderWindow* m_window;

	sf::Color bgColor;

	Player* player;

	std::vector<Rocket *> rockets;
	std::vector<Enemy *> enemies;

	float currentTime = 0.0f, prevTime = 0.0f;
	sf::Music bgMusic;

	unsigned int points;
	sf::Font pointsFont;
	sf::Text pointsText;
};

