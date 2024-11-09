#ifndef GRAVITY_H
#define GRAVITY_H
#define GRAVITY 0.5f
struct Gravity
{
	float Strength = GRAVITY;
};
void ApplyGravity2d(float& posY, float& vY, float& Strength);

#endif