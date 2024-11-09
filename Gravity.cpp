#include "Gravity.h"

void ApplyGravity2d(float& posY, float& vY, float& Strength)
{
	Strength;
	vY += Strength;
	posY += vY;
}