#include "Flight.h"

void ApplyFlight(float& posY, float& vY)
{
	float flightStrength = 7;
	vY = -flightStrength;
	posY += vY;
}

void Fly(float& posY, float& vY)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        ApplyFlight(posY, vY);
    }
}
