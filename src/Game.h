/*
 * Game.h
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include <iostream>
#include "Map.h"
#include "Player.h"

#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
							Game();
	virtual 				~Game();
	void					run();


public:
	// public methods

public:
	// public variables

private:
	// private variables

	sf::RenderWindow 		window;

	Player					player;
	Map						map;

	sf::Font				FPSFont;
	sf::Text				FPS;

private:
	// private methods
	void					processEvents();
	void					update(sf::Time& deltaTime);
	void					render();
	void					showFPS(float fps);



};

#endif /* GAME_H_ */
