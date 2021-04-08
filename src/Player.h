/*
 * Player.h
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Constants.h"
#include "Map.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
											Player(float nPlayerX, float nPlayerY);
	virtual 								~Player();


public:
	float									fPlayerX, fPlayerY;
	float									fPlayerAngle; // aka direction, point of view etc (in radians)

	int 									nRadius;
	int										nWalkingDirection;
	int										nTurnDirection;
	float 									fPlayerSpeed;
	float									fRotationSpeed;

private:
	sf::CircleShape							playerShape;


public:
	void									update(sf::Time& deltaTime);
	void 									render(sf::RenderWindow& window);

	void									castAllRays(Map map);
	void 									castLine(sf::RenderWindow& window, int x, int y, int endX, int endY, sf::Color color);


};

#endif /* PLAYER_H_ */
