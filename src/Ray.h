/*
 * Ray.h
 *
 *  Created on: 7 de abr. de 2021
 *      Author: magoninho
 */
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Player.h"

#ifndef RAY_H_
#define RAY_H_

class Ray
{
public:
	Ray(float rayAngle, Player& player, Map& map);
	virtual ~Ray();

public:
	Player 	player;
	Map	  	map;
	float 	rayAngle;
	float 	wallPositionX;
	float 	wallPositionY;
	float 	finalDistance;

public:
	void castLine(sf::RenderWindow& window, int x, int y, int endX, int endY, sf::Color color);
	void render(sf::RenderWindow& window);
	void cast();


	float horizontalHitX = 0;
	float horizontalHitY = 0;

	float verticalHitX = 0;
	float verticalHitY = 0;

};

#endif /* RAY_H_ */
