/*
 * Ray.cpp
 *
 *  Created on: 7 de abr. de 2021
 *      Author: magoninho
 */

#include "Ray.h"

float normalizeAngle(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0) {
		angle = (2 * PI) + angle;
	}
	return angle;
}

float distanceBetween(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

Ray::Ray(float rayAngle, Player& player, Map& map)
{
	this->rayAngle = normalizeAngle(rayAngle);
	this->player = player;
	this->map = map;
	this->wallPositionX = 0;
	this->wallPositionY = 0;
	this->finalDistance = 0;
}


void Ray::castLine(sf::RenderWindow& window, int x, int y, int endX, int endY, sf::Color color)
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

void Ray::cast()
{
	float xintersect, yintersect;
	float xstep, ystep;

	///////////////////////
	// Vertical checking //
	///////////////////////

	float verticalHitX = 0;
	float verticalHitY = 0;

	bool foundVerticalWall = false;

	xintersect = (float)((int)(player.fPlayerX / TILESIZE)) * TILESIZE;

	if (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI) // looking right
		xintersect += TILESIZE;

	yintersect = player.fPlayerY + (xintersect - player.fPlayerX) * tan(rayAngle);

	xstep = TILESIZE;

	if (rayAngle > 0.5 * PI && rayAngle < 1.5 * PI) // looking left
		//invert the xstep if looking up (because y grows down, not up)
		xstep *= -1;

	ystep = xstep * tan(rayAngle);

	float nextVerticalX = xintersect;
	float nextVerticalY = yintersect;

	if (rayAngle > 0.5 * PI && rayAngle < 1.5 * PI) // looking left
		nextVerticalX -= 1; // this is for fixing the bug of offset

	// starting the vertical checking

	while (nextVerticalX >= 0 &&
			nextVerticalX <= WINDOW_WIDTH &&
			nextVerticalY >= 0 &&
			nextVerticalY <= WINDOW_HEIGHT)
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
	///////////////////////////////
	// horizontal check
	//////////////////////////////
	bool foundHorizontalWall = false;
	float horizontalHitX = 0;
	float horizontalHitY = 0;

	yintersect = (float)((int)(player.fPlayerY / TILESIZE) * TILESIZE);

	if (rayAngle > 0 && rayAngle < PI) // looking down
		yintersect += TILESIZE;

	xintersect = player.fPlayerX + (yintersect - player.fPlayerY) / tan(rayAngle);

	ystep = TILESIZE;

	if (rayAngle > PI && rayAngle < 2*PI) // looking up
		//invert the ystep if looking up (because y grows down, not up)
		ystep *= -1;

	xstep = ystep/tan(rayAngle);

	float nextHorizontalX = xintersect;
	float nextHorizontalY = yintersect;

	if (rayAngle > PI && rayAngle < 2*PI)
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
		horizontalDistance = distanceBetween(player.fPlayerX, player.fPlayerY, horizontalHitX, horizontalHitY);
		else
			horizontalDistance = 999999;
	if (foundVerticalWall)
		verticalDistance = distanceBetween(player.fPlayerX, player.fPlayerY, verticalHitX, verticalHitY);
		else
			verticalDistance = 999999;
	// std::cout << foundHorizontalWall << " " << foundVerticalWall << " " << horizontalDistance << " " << verticalDistance << std::endl;

	wallPositionX = (horizontalDistance < verticalDistance) ? horizontalHitX : verticalHitX;
	wallPositionY = (horizontalDistance < verticalDistance) ? horizontalHitY : verticalHitY;


	finalDistance = (horizontalDistance < verticalDistance) ? horizontalDistance : verticalDistance;
}


void Ray::render(sf::RenderWindow& window)
{
	castLine(
		window,
		player.fPlayerX,
		player.fPlayerY,
		wallPositionX,
		wallPositionY,
		sf::Color::Red
	);
}

Ray::~Ray()
{
	// TODO Auto-generated destructor stub
}

