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
    float tweakBorder = 4.0f;  // Reduced tweakBorder for smaller borders
    float tipOffsetX = 2.0f;  // You can adjust this value to move the tip left or right

    // Upper pipe
    DrawRectangle(PosX - 2, 0, Width + 4, PosY, DARKGRAY);  // Smaller border
    DrawRectangle(PosX, 0, Width, PosY, color);

    // Lower pipe
    DrawRectangle(PosX - 2, PosY + GAP_HEIGHT, Width + 4, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), DARKGRAY);  // Smaller border
    DrawRectangle(PosX, PosY + GAP_HEIGHT, Width, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), color);

    // Upper pipe tip (centered with tipOffsetX adjustment)
    int tipPosX1 = PosX + (Width - tipWidth) / 2 + tipOffsetX;  // Centered with offset
    DrawRectangle(tipPosX1 - tweakBorder, PosY - tipHeight, tipWidth + 5, tipHeight + 4, DARKGRAY);  // Smaller border
    DrawRectangle(tipPosX1 - 2, PosY - tipHeight + 3, tipWidth, tipHeight - 2, color);

    // Lower pipe tip (centered with tipOffsetX adjustment)
    int tipPosX2 = PosX + (Width - tipWidth) / 2 + tipOffsetX;  // Centered with offset
    DrawRectangle(tipPosX2 - tweakBorder, PosY + GAP_HEIGHT, tipWidth + 5, tipHeight + 4, DARKGRAY);  // Smaller border
    DrawRectangle(tipPosX2 - 2, PosY + GAP_HEIGHT + 3, tipWidth, tipHeight - 2, color);
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