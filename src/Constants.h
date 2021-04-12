/*
 * Constants.hpp
 *
 *  Created on: 6 de abr. de 2021
 *      Author: magoninho
 */

#include <math.h>
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#define PI 3.14159265359

constexpr int TILESIZE = 32;
constexpr int ROWS = 11;
constexpr int COLS = 15;
constexpr int WINDOW_WIDTH = COLS * TILESIZE;
constexpr int WINDOW_HEIGHT = ROWS * TILESIZE;

constexpr float FOV = 60 * (PI / 180);

constexpr int NUM_OF_RAYS = WINDOW_WIDTH / 4; // divided by 4, just to not cast to many rays




#endif
