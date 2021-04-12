/*
 * Player.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Player.h"
#include "Ray.h"


Player::Player()
{
	fPlayerX = WINDOW_WIDTH / 2;
	fPlayerY = WINDOW_HEIGHT / 2;

	fPlayerAngle = 3*PI / 2; // (90 degrees)
	fPlayerSpeed = 120;
	fRotationSpeed = 150 * (PI / 180);
	nRadius = 5;

	nTurnDirection = 0;
	nWalkingDirection = 0;


}

void Player::update(sf::Time& deltaTime)
{
	// rotation i guess
	fPlayerAngle += fRotationSpeed * nTurnDirection * deltaTime.asSeconds();

	// TODO: COLLISIONS

	int nMoveStep = nWalkingDirection * fPlayerSpeed; // gets the move step based from the walking direction, which can be -1, 0 or 1
	fPlayerX += cos(fPlayerAngle) * nMoveStep * deltaTime.asSeconds();
	fPlayerY += sin(fPlayerAngle) * nMoveStep * deltaTime.asSeconds();

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
}

