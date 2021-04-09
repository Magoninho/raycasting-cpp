/*
 * Player.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Player.h"
#include "Ray.h"

int rmDec(float number)
{
	return (int)number;
}

Player::Player()
{
	fPlayerX = WINDOW_WIDTH / 2;
	fPlayerY = WINDOW_HEIGHT / 2;

	fPlayerAngle = PI; // (90 degrees)
	fPlayerSpeed = 2;
	fRotationSpeed = 2 * (PI / 180);
	nRadius = 5;

	nTurnDirection = 0;
	nWalkingDirection = 0;


}

void Player::castLine(sf::RenderWindow& window, int x, int y, int endX, int endY, sf::Color color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x, y)),
		sf::Vertex(sf::Vector2f(endX, endY))
	};
	line[0].color = color;
	line[1].color = color;
	window.draw(line, 2, sf::Lines);
}



void Player::update(sf::Time& deltaTime)
{
	// rotation i guess
	fPlayerAngle += fRotationSpeed * nTurnDirection;

	// TODO: COLLISIONS

	int nMoveStep = nWalkingDirection * fPlayerSpeed; // gets the move step based from the walking direction, which can be -1, 0 or 1
	fPlayerX += cos(fPlayerAngle) * nMoveStep;
	fPlayerY += sin(fPlayerAngle) * nMoveStep;

	// reset the angle
	if (fPlayerAngle < 0)
		fPlayerAngle += 2 * PI;
	if (fPlayerAngle > 2 * PI)
		fPlayerAngle -= 2 * PI;
}


void Player::render(sf::RenderWindow& window)
{
	playerShape.setRadius((float)nRadius);
	playerShape.setPosition(fPlayerX, fPlayerY);
	playerShape.setFillColor(sf::Color::Magenta);
	playerShape.setOrigin(playerShape.getLocalBounds().width/2, playerShape.getLocalBounds().height/2);
	window.draw(playerShape);
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

