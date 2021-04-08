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

Ray::Ray(float rayAngle)
{
	rayAngle = normalizeAngle(rayAngle);
	wallHitX = 0;
	wallHitY = 0;
	distance = 0;


}

Ray::~Ray()
{
	// TODO Auto-generated destructor stub
}

