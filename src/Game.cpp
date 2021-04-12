/*
 * Game.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Game.h"

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", sf::Style::Close)
{
	window.setPosition(sf::Vector2i(10, 50));
	// loading font
	if(!FPSFont.loadFromFile("Media/jetbrains.ttf"))
		printf("error while loading the font");

	// configuring font
	FPS.setFont(FPSFont);
	FPS.setScale(0.7f, 0.7f);
	FPS.setFillColor(sf::Color::White);
	FPS.setPosition(0, 0);
}

/*
 * This function will iterate through the number of rays, create a ray with an angle created with the index, and cast this ray
 * */
void Game::castAllRays()
{
	for (float i = 0; i < NUM_OF_RAYS; i++)
	{
		float rayAngle = (player.fPlayerAngle - FOV/2.0) + (i/NUM_OF_RAYS) * FOV;
		Ray ray(rayAngle, this->player, map);
		rays.push_back(ray);
		// std::cout << rays[i].rayAngle << std::endl;
		rays[i].cast();
	}
}


/*
 * Processing the SFML events
 * */
void Game::processEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		// Player movement!
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::W)
				player.nWalkingDirection = 	1;
			if (event.key.code == sf::Keyboard::S)
				player.nWalkingDirection = 	-1;
			if (event.key.code == sf::Keyboard::A)
				player.nTurnDirection = 	-1;
			if (event.key.code == sf::Keyboard::D)
				player.nTurnDirection = 	1;
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::W)
				player.nWalkingDirection = 	0;
			if (event.key.code == sf::Keyboard::S)
				player.nWalkingDirection = 	0;
			if (event.key.code == sf::Keyboard::A)
				player.nTurnDirection = 	0;
			if (event.key.code == sf::Keyboard::D)
				player.nTurnDirection = 	0;
			break;


		default:
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();


	}
}

/*
 * The update function
 * */
void Game::update(sf::Time& deltaTime)
{
	player.update(deltaTime);
}

/*
 * Rendering all the stuff
 * */
void Game::render()
{
	window.clear(sf::Color::Black);
	map.render(window);
	player.render(window);
	castAllRays();
	for(auto ray : rays)
	  ray.render(window);
	rays.clear();
	window.draw(FPS);
	window.display();
}

/*
 * Sets the FPS
 * */
void Game::setFPS(int fps)
{
	FPS.setString(std::to_string(fps) + "FPS");
}

/*
 * Initializes the GAME LOOP
 * */

void Game::run()
{
	int fps = 100;
	sf::Clock clock;
	sf::Clock fpsClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / fps);

	while (window.isOpen())
	{
		/**
		 * This is a process called fixed time steps
		 * The game will only update if the time passed is the same as 1 divided by the amount of fps
		 * */
		timeSinceLastUpdate += clock.restart();

		processEvents();

		while (timeSinceLastUpdate > timePerFrame) // time per frame
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}

		// Shows the FPS on the screen
		setFPS(1.f / fpsClock.getElapsedTime().asSeconds());
		fpsClock.restart();

		render();
	}
}


Game::~Game()
{
}

