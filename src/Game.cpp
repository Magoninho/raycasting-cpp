/*
 * Game.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Game.h"

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game")
{
	if(!FPSFont.loadFromFile("Media/jetbrains.ttf"))
		printf("error while loading the font");

	FPS.setFont(FPSFont);
	FPS.setScale(0.7f, 0.7f);
	FPS.setFillColor(sf::Color::White);
	FPS.setPosition(0, 0);
}

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


void Game::update(sf::Time& deltaTime)
{
	player.update(deltaTime);
}

void Game::render()
{
	window.clear(sf::Color::Black);
	map.render(window);
	player.render(window);
	castAllRays();
	for(auto ray : rays)
	  ray.render(window);
	rays.clear();
	window.display();
}


void Game::showFPS(float fps)
{
	FPS.setString(std::to_string(fps) + "FPS");
}

void Game::run()
{
	int frames = 0;
	int fps = 60;
	sf::Clock clock;
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
			// completou 1 segundo (60 frames)
			frames++;
		}


		// probably this is not even working (help pls)
		if (frames > fps)
		{

			showFPS((1.f/  clock.getElapsedTime().asSeconds())/100);
			frames -= fps;
			clock.restart().asSeconds();
		}

		render();
	}
}


Game::~Game()
{
	// TODO Auto-generated destructor stub
}

