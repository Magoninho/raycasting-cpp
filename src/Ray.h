/*
 * Ray.h
 *
 *  Created on: 7 de abr. de 2021
 *      Author: magoninho
 */
#include <SFML/Graphics.hpp>
#include "Constants.h"

#ifndef RAY_H_
#define RAY_H_

class Ray
{
public:
	Ray(float rayAngle);
	virtual ~Ray();

public:
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float finalDistance;

public:
	void cast();
	void render(sf::RenderWindow& window);


};

#endif /* RAY_H_ */
