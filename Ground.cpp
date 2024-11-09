#include "Ground.h"

Ground::Ground()
{
	X = 0; 
	Y = 700 - GROUND_HEIGHT;
	Width = 500;
	Height = GROUND_HEIGHT;
	texture;
}

void Ground::Draw() const
{
	DrawTexture(texture, X, Y, WHITE);
}

Ground::~Ground()
{
	UnloadTexture(texture); 
}

void Ground::LoadTexture()
{
    Image Base = LoadImage("C:/Users/user/desktop/FlappyBird_assets/base.png");
	texture = LoadTextureFromImage(Base);
    UnloadImage(Base);
}