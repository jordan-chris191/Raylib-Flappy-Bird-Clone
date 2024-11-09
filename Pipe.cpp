#include "Pipe.h"

Pipe::Pipe()
{
    PosX = SCREEN_WIDTH+12;
    PosY = GetRandomValue(100, SCREEN_HEIGHT - 200);
    Width = 60;
    Height = SCREEN_HEIGHT;
    Speed = SPEED;
    bool passed = false;
}

void Pipe::Draw() const
{
    int tipWidth = Width + 10;
    int tipHeight = 50;
    float tweakBorder = 9.5;
    DrawRectangle(PosX - 5, 0, Width + 10, PosY, DARKGRAY);
    DrawRectangle(PosX, 0, Width, PosY, color);

    DrawRectangle(PosX - 5, PosY + GAP_HEIGHT, Width + 10, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), DARKGRAY);
    DrawRectangle(PosX, PosY + GAP_HEIGHT, Width, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), color);

    DrawRectangle(PosX - tweakBorder, PosY - tipHeight, tipWidth + 10, tipHeight + 4, DARKGRAY);
    DrawRectangle(PosX - 4, PosY - tipHeight + 3, tipWidth, tipHeight-2, color);

   DrawRectangle(PosX - tweakBorder, PosY + GAP_HEIGHT, tipWidth + 10, tipHeight + 4, DARKGRAY);
   DrawRectangle(PosX - 4, PosY + GAP_HEIGHT + 3, tipWidth, tipHeight-2, color);
}

void Pipe::Update(float &deltaTime)
{
    PosX -= Speed * deltaTime; 
    if (PosX + Width < 0)
    {
        PosX = SCREEN_WIDTH+12;
        PosY = GetRandomValue(100, (SCREEN_HEIGHT - GROUND_HEIGHT) - 300);
        passed = false;
    }
}