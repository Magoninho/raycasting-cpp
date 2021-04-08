/*
 * Player.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Player.h"

float distanceBetween(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}



int rmDec(float number)
{
	return (int)number;
}

Player::Player(float fPlayerX, float fPlayerY)
{
	this->fPlayerX = fPlayerX;
	this->fPlayerY = fPlayerY;

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


float wallPositionX;
float wallPositionY;

float finalDistance;

float horizontalHitX = 0;
float horizontalHitY = 0;

float verticalHitX = 0;
float verticalHitY = 0;

void Player::castAllRays(Map map)
{
	for (float i = 0; i < 1; i++)
	{
		double rayAngle = normalizeAngle((fPlayerAngle));
//		std::cout << fPlayerAngle << std::endl;

		float xintersect, yintersect;
		float xstep, ystep;


		///////////////////////////////
		// horizontal check
		//////////////////////////////

		bool foundHorizontalWall = false;

		yintersect = (int)(fPlayerY / TILESIZE) * TILESIZE;

		if (rayAngle > 0 && rayAngle < PI) // looking down
			yintersect += TILESIZE;

		xintersect = fPlayerX + (yintersect - fPlayerY) / tan(rayAngle);

		ystep = TILESIZE;

		if (!(rayAngle > 0 && rayAngle < PI)) // looking up
			//invert the ystep if looking up (because y grows down, not up)
			ystep *= -1;

		xstep = ystep/tan(rayAngle);

		float nextHorizontalX = xintersect;
		float nextHorizontalY = yintersect;

		if (!(rayAngle > 0 && rayAngle < PI))
			nextHorizontalY -= 0.01; // this is for fixing the bug of offset

		// starting the horizontal checking

		while (nextHorizontalX <= WINDOW_WIDTH &&
				nextHorizontalX >= 0 &&
				nextHorizontalY <= WINDOW_HEIGHT &&
				nextHorizontalY >= 0)
		{
			if (map.hasWallAt(nextHorizontalX, nextHorizontalY))
			{
				foundHorizontalWall = true;
				// if we find a wall, then store the position of the hit
				horizontalHitX = nextHorizontalX;
				horizontalHitY = nextHorizontalY;
				break;
			} else
			{
				// if wall not found, then continue checking
				nextHorizontalX += xstep;
				nextHorizontalY += ystep;
			}
		}



		///////////////////////
		// Vertical checking //
		///////////////////////

		bool foundVerticalWall = false;

		xintersect = (int)(fPlayerX / TILESIZE) * TILESIZE;

		if (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI) // looking right
			xintersect += TILESIZE;

		yintersect = fPlayerY + (xintersect - fPlayerX) / tan(rayAngle);

		xstep = TILESIZE;

		if (rayAngle > 0.5 * PI && rayAngle < 1.5 * PI) // looking left
			//invert the xstep if looking up (because y grows down, not up)
			xstep *= -1;

		ystep = xstep * tan(rayAngle);

		float nextVerticalX = xintersect;
		float nextVerticalY = yintersect;

		if (!(rayAngle < 0.5 * PI || rayAngle > 1.5 * PI)) // looking left
			nextVerticalX -= 0.01; // this is for fixing the bug of offset

		// starting the vertical checking

		while (nextVerticalX >= 0 &&
				nextVerticalX <= WINDOW_WIDTH &&
				nextVerticalY >= 0
				&& nextVerticalY <= WINDOW_HEIGHT)
		{
			if (map.hasWallAt(nextVerticalX, nextVerticalY))
			{
				foundVerticalWall = true;
				// if we find a wall, then store the position of the hit
				verticalHitX = nextVerticalX;
				verticalHitY = nextVerticalY;
				break;
			} else
			{
				// if wall not found, then continue checking
				nextVerticalX += xstep;
				nextVerticalY += ystep;
			}
		}

		/////////////////////////////////////////////////////////////////////////
		//							  Distance
		//							 Calculation!
		/////////////////////////////////////////////////////////////////////////
		// we need to compare the horizontal distance with the vertical distance.
		// then check which one is the nearest to the player
		/////////////////////////////////////////////////////////////////////////

		float horizontalDistance = 0;
		float verticalDistance = 0;


		if (foundHorizontalWall)
			horizontalDistance = distanceBetween(fPlayerX, fPlayerY, horizontalHitX, horizontalHitY);
//		else
//			horizontalDistance = 999999;
		if (foundVerticalWall)
			verticalDistance = distanceBetween(fPlayerX, fPlayerY, verticalHitX, verticalHitY);
//		else
//			verticalDistance = 999999;
		std::cout << foundHorizontalWall << " " << foundVerticalWall << " " << horizontalDistance << " " << verticalDistance << std::endl;

		wallPositionX = (horizontalDistance < verticalDistance) ? horizontalHitX : verticalHitX;
		wallPositionY = (horizontalDistance < verticalDistance) ? horizontalHitY : verticalHitY;


		finalDistance = (horizontalDistance < verticalDistance) ? horizontalDistance : verticalDistance;

		// TODO: COLORS BASED ON DEPTH
	}
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
	castLine(
			window,
			fPlayerX,
			fPlayerY,
			verticalHitX,
			verticalHitY,
			sf::Color::Green
	);
	castLine(
			window,
			fPlayerX,
			fPlayerY,
			horizontalHitX,
			horizontalHitY,
			sf::Color::Red
	);
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

