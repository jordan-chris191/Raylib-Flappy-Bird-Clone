#include "Flight.h"

void ApplyFlight(float& posY, float& vY)
{
	float LiftStrength = 7;
	vY = -LiftStrength;
	posY += vY;
}

void Fly(float& posY, float& vY)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        ApplyFlight(posY, vY);
    }
}
