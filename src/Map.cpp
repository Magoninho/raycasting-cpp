/*
 * Map.cpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include "Map.h"

Map::Map()
{
}

int Map::hasWallAt(int x, int y)
{
	return grid[(int)floor(y / TILESIZE)][(int)floor(x / TILESIZE)] == 1;
}

void Map::render(sf::RenderWindow& window)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int tileX = j * TILESIZE;
			int tileY = i * TILESIZE;
			sf::Color color = sf::Color::White;

			if (grid[i][j] == 1)
				color = sf::Color::Black;
			else
				color = sf::Color::White;

			sf::RectangleShape rectangle[ROWS * COLS];
			for (int r = 0; r < (ROWS * COLS); r++)
			{
				rectangle[r].setPosition(tileX, tileY);
				rectangle[r].setSize(sf::Vector2f(TILESIZE-1, TILESIZE-1));
				rectangle[r].setFillColor(color);
				window.draw(rectangle[r]);

			}
		}
	}
}

Map::~Map()
{
	// TODO Auto-generated destructor stub
}

