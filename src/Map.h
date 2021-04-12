/*
 * Map.h
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Constants.h"

#ifndef MAP_H_
#define MAP_H_

class Map
{
public:
								Map();
	virtual 					~Map();

public:
	bool						hasWallAt(int x, int y);
	void						render(sf::RenderWindow& window);



public:
	int					grid[ROWS][COLS] = {
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
								{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
						};


};

#endif /* MAP_H_ */
