/*
 * Ray.cpp
 *
 *  Created on: 7 de abr. de 2021
 *      Author: magoninho
 */

#include "Ray.h"

/*
 * This function normalizes an angle
 * \param double angle
 * */
float normalizeAngle(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0) {
		angle = (2 * PI) + angle;
	}
	return angle;
}


/*
 * A simple Pythagora's theorem to find a distance
 * \param float x1
 * \param float y1
 * \param float x2
 * \param float y2
 * */
float distanceBetween(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

Ray::Ray(float rayAngle, Player& player, Map& map)
{
	this->rayAngle = normalizeAngle(rayAngle);
	this->player = player;
	this->map = map;
	wallPositionX = 0;
	wallPositionY = 0;
	finalDistance = 0;
}

///////////////////////////////////////
// This is a function that draws a line
// \param window
// \param starting x
// \param starting y
// \param ending x
// \param ending y
// \param color
///////////////////////////////////////
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

/*
  ________
 /_  __/ /_  ___
  / / / __ \/ _ \
 / / / / / /  __/
/_/ /_/ /_/\___/_                              __  _
            / __ \____ ___  ___________ ______/ /_(_)___  ____ _
           / /_/ / __ `/ / / / ___/ __ `/ ___/ __/ / __ \/ __ `/
          / _, _/ /_/ / /_/ / /__/ /_/ (__  ) /_/ / / / / /_/ /
         /_/ |_|\__,_/\__, /\___/\__,_/____/\__/_/_/ /_/\__, /
                     /____/                            /____/
       	   	   	   	   	   	   	   	   	   begins here...
*/
void Ray::cast()
{
	float xintersect, yintersect; // the first intersections, from where the player is to a horizontal or vertical line
	float xstep, ystep;


	/*
	 _                _                _        _
	| |              (_)              | |      | |
	| |__   ___  _ __ _ _______  _ __ | |_ __ _| |
	| '_ \ / _ \| '__| |_  / _ \| '_ \| __/ _` | |
	| | | | (_) | |  | |/ / (_) | | | | || (_| | |
	|_| |_|\___/|_|  |_/___\___/|_| |_|\__\__,_|_|

	 */

	bool foundHorizontalWall = false; // a boolean to check if a horizontal wall was found
	// variables to store where the horizontal wall was hit
	float horizontalHitX = 0;
	float horizontalHitY = 0;

	yintersect = (float)((int)(player.fPlayerY / TILESIZE) * TILESIZE); // according to the trigonometry, this is where the first y intersection happens

	if (rayAngle > 0 && rayAngle < PI) // if the player is looking DOWN, the yintersect needs to increment by the tilesize
		yintersect += TILESIZE;

	xintersect = player.fPlayerX + (yintersect - player.fPlayerY) / tan(rayAngle); // according to the trigonometry, this is where the first x intersection will happen

	/*
	 * now that we got the first intersection (xintersect and yintersect), we need to find the xstep and ystep
	 * which are the steps for both x and y after the first intersection
	 * */
	ystep = TILESIZE; // for the horizontal lines the ystep is only the tile size, since the distance from every intersection in y has the same size as the tile size


	// if the player is looking up, then the ystep becomes -TILESIZE
	if (rayAngle > PI && rayAngle < 2*PI)
		ystep *= -1;

	xstep = ystep/tan(rayAngle); // based on the trigonometry, this is what the xstep is

	/*
	 * These are the variables that will hold the current position of the HORIZONTAL intersections
	 * Now they are the xintersect and yintersect, but when the checking starts they will be incremented by the xstep and ystep
	 * */
	float nextHorizontalX = xintersect;
	float nextHorizontalY = yintersect;

	if (rayAngle > PI && rayAngle < 2*PI) // if the player is looking up, then subtract a small amount so the ray can check the correct wall
		nextHorizontalY -= 0.01;


	//////////////////////////////////////////////
	////// starting the horizontal checking //////
	//////////////////////////////////////////////


	// while the ray is inside the window
	while (nextHorizontalX <= WINDOW_WIDTH &&
		  nextHorizontalX >= 0 &&
		  nextHorizontalY <= WINDOW_HEIGHT &&
		  nextHorizontalY >= 0)
	{
		// if where the ray is currently intersecting has a wall in the map array, then a horizontal wall was found!
		if (map.hasWallAt(nextHorizontalX, nextHorizontalY))
		{
			foundHorizontalWall = true;
			// if we find a wall, then store the position of the hit
			horizontalHitX = nextHorizontalX;
			horizontalHitY = nextHorizontalY;
			break; // breaks the loop because where done with the checking
		} else
		{
			// if wall not found, then continue checking by incrementing the nextHorizontalX and nextHorizontalY with the xstep and ystep
			nextHorizontalX += xstep;
			nextHorizontalY += ystep;
		}
	}

	/*
	                _   _           _
                       | | (_)         | |
	__   _____ _ __| |_ _  ___ __ _| |
	\ \ / / _ \ '__| __| |/ __/ _` | |
	 \ V /  __/ |  | |_| | (_| (_| | |
	  \_/ \___|_|   \__|_|\___\__,_|_|

	*/

	bool foundVerticalWall = false; // a boolean to check if a horizontal wall was found
	// variables to store where the vertical wall was hit
	float verticalHitX = 0;
	float verticalHitY = 0;


	xintersect = (float)((int)(player.fPlayerX / TILESIZE)) * TILESIZE; // according to the trigonometry, this is where the first x intersection happens

	if (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI) // if the player is looking right, then the xintersect needs to be incremented by the tile size
		xintersect += TILESIZE;

	yintersect = player.fPlayerY + (xintersect - player.fPlayerX) * tan(rayAngle); // according to the trigonometry, this is where the first y intersection will happen

	xstep = TILESIZE; // the xstep in vertical checking is the same as the tile size

	if (rayAngle > 0.5 * PI && rayAngle < 1.5 * PI) // if the player is looking left, the xstep needs to become -TILESIZE
		xstep *= -1;

	/*
	 * now that we got the first intersection (xintersect and yintersect), we need to find the xstep and ystep
	 * which are the steps for both x and y after the first intersection
	 * */
	ystep = xstep * tan(rayAngle); // according with the raycasting trigonometry, for the vertical lines the ystep is this little formula

	/*
	 * These are the variables that will hold the current position of the VERTICAL intersections
	 * Now they are the xintersect and yintersect, but when the checking starts they will be incremented by the xstep and ystep
	 * */
	float nextVerticalX = xintersect;
	float nextVerticalY = yintersect;

	if (rayAngle > 0.5 * PI && rayAngle < 1.5 * PI) // if the player is looking left, then subtract a small amount so the ray can check the correct wall
		nextVerticalX -= 0.01; // this also solves an offset bug

	////////////////////////////////////////////
	////// starting the vertical checking //////
	////////////////////////////////////////////

	// while the ray is inside the window
	while (nextVerticalX >= 0 &&
			nextVerticalX <= WINDOW_WIDTH &&
			nextVerticalY >= 0 &&
			nextVerticalY <= WINDOW_HEIGHT)
	{
		// if where the ray is currently intersecting has a wall in the map array, then a vertical wall was found!
		if (map.hasWallAt(nextVerticalX, nextVerticalY))
		{
			foundVerticalWall = true;
			// if we find a wall, then store the position of the hit
			verticalHitX = nextVerticalX;
			verticalHitY = nextVerticalY;
			break; // breaks the loop because where done with the checking
		} else
		{
			// if wall not found, then continue checking
			nextVerticalX += xstep;
			nextVerticalY += ystep;
		}
	}

	/*
		____  _      __
	   / __ \(_)____/ /_____ _____  ________
	  / / / / / ___/ __/ __ `/ __ \/ ___/ _ \
	 / /_/ / (__  ) /_/ /_/ / / / / /__/  __/
	/_____/_/____/\__/\__,_/_/_/_/\___/\___/      __  _
                            / ____/___ _/ /______  __/ /___ _/ /_(_)___  ____
			   / /   / __ `/ / ___/ / / / / __ `/ __/ / __ \/ __ \
			  / /___/ /_/ / / /__/ /_/ / / /_/ / /_/ / /_/ / / / /
			  \____/\__,_/_/\___/\__,_/_/\__,_/\__/_/\____/_/ /_/
	*/

	////////////////////////////////////////////////////////////////////////////
	// We need to compare the horizontal distance with the vertical distance. //
	// Then check which one is the nearest to the player					  //
	////////////////////////////////////////////////////////////////////////////

	// the variables to stop both horizontal and vertical distance to a wall
	float horizontalDistance = 0;
	float verticalDistance = 0;

	// if found horizontal wall, calculate the distance between the player and the horizontal wall
	if (foundHorizontalWall)
		horizontalDistance = distanceBetween(player.fPlayerX, player.fPlayerY, horizontalHitX, horizontalHitY);
	else
		horizontalDistance = 999999;

	// if found vertical wall, calculate the distance between the player and the vertical wall
	if (foundVerticalWall)
		verticalDistance = distanceBetween(player.fPlayerX, player.fPlayerY, verticalHitX, verticalHitY);
	else
		verticalDistance = 999999;

	// std::cout << foundHorizontalWall << " " << foundVerticalWall << " " << horizontalDistance << " " << verticalDistance << std::endl;



	////////////////////////////////////////////////////////////////////////////////////
	////// Now we need to store the FINAL DISTANCE in the wall position variables //////
	////// Of course, we need the nearest position						  		  //////
	////////////////////////////////////////////////////////////////////////////////////
	finalDistance = (horizontalDistance < verticalDistance) ? horizontalDistance : verticalDistance;

	// And also based on the distances, we find whether the horizontal or vertical wall positions need to be the final position for this ray (wallPositionX and wallPositionY)
	wallPositionX = (horizontalDistance < verticalDistance) ? horizontalHitX : verticalHitX;
	wallPositionY = (horizontalDistance < verticalDistance) ? horizontalHitY : verticalHitY;
}

/*
 * Renders the ray on a given window
 * \param sf::RenderWindow& window
 * */
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
}

