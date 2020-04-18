#include "Game.h"

#include <iostream>
#include <SFML/Audio.hpp>

Game::Game(const std::string& title, const int width, const int height)
{
	m_videoMode = sf::VideoMode(width, height);
	m_window = new sf::RenderWindow(m_videoMode, title, sf::Style::Default);

	bgColor = sf::Color(0, 0, 85);

	player = new Player(m_videoMode.width / 2, m_videoMode.height - 40, 200.0f);

	bool loaded = bgMusic.openFromFile("Assets/audios/Chiptronical.ogg");
	if (!loaded)
		std::cerr << "no se pudo cargar la música de pondo" << std::endl;
	else
	{
		bgMusic.setVolume(5.0f);
		bgMusic.play();
	}

	loaded = pointsFont.loadFromFile("Assets/fonts/Vonique_43_D.otf");
	if (!loaded)
		std::cerr << "no se pudo cargar la fuente para los puntos" << std::endl;
	{
		pointsText.setFont(pointsFont);
		pointsText.setPosition(0, 0);
		pointsText.setFillColor(sf::Color::White);
		pointsText.setString("0 Points.");
	}
}

void Game::SpawnRocket()
{
	sf::Vector2f playerPosition = player->GetSprite().getPosition();
	
	Rocket* rocket = new Rocket(playerPosition.x, playerPosition.y, 250.0f);
	rockets.push_back(rocket);
}

void Game::Update(float dt)
{
	sf::Event evt;
	while (m_window->pollEvent(evt))
	{
		switch (evt.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (evt.key.code == sf::Keyboard::Space)
				SpawnRocket();
			else
				player->IsMoving(evt.key.code);
			break;
		case sf::Event::KeyReleased:
			player->StopMoving();
			break;
		}
	}

	for (int i = 0; i < rockets.size(); i++)
	{
		Rocket* rocket = rockets.at(i);
		rocket->Update(dt);

		if (rocket->GetSprite().getPosition().y <= 0)
		{
			rockets.erase(rockets.begin() + i);
			delete rocket;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies.at(i);
		enemy->Update(dt);

		if (enemy->GetSprite().getPosition().y >= m_videoMode.height)
		{
			enemies.erase(enemies.begin() + i);
			delete enemy;
		}
	}

	for (int i = 0; i < rockets.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			Rocket* rocket = rockets.at(i);
			Enemy* enemy = enemies.at(j);

			sf::FloatRect rectRocket = rocket->GetSprite().getGlobalBounds();
			sf::FloatRect rectEnemy = enemy->GetSprite().getGlobalBounds();

			if (rectRocket.intersects(rectEnemy))
			{
				enemies.erase(enemies.begin() + j);
				rockets.erase(rockets.begin() + i);

				delete rocket;
				delete enemy;

				points++;
				pointsText.setString(std::to_string(points) + " Points.");

				break;
			}
		}
	}

	player->Update(dt);

	currentTime += dt;
	if (currentTime >= prevTime + 1.125f)
	{
		float randLocation = rand() % m_videoMode.width + 8;
		Enemy* enemy = new Enemy(randLocation, 0, 100.0f);
		enemies.push_back(enemy);

		prevTime = currentTime;
	}
}

void Game::Render()
{
	m_window->clear(bgColor);

	m_window->draw(player->GetSprite());

	for (int i = 0; i < rockets.size(); i++)
	{
		Rocket* rocket = rockets.at(i);
		m_window->draw(rocket->GetSprite());
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies.at(i);
		m_window->draw(enemy->GetSprite());
	}

	m_window->draw(pointsText);

	m_window->display();
}

int Game::Run()
{
	sf::Clock clock;

	srand((int) time(0));

	while (m_window->isOpen())
	{
		sf::Time dt = clock.restart();
		Update(dt.asSeconds());
		Render();
	}

	return 0;
}

Game::~Game()
{
	delete player;
	delete m_window;
}