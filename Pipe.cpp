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
    float tipWidth = Width + 12;
    float tipHeight = 50;
    float tweakBorder = 4.0f;  // Reduced tweakBorder for smaller borders
    float tipOffsetX = 2.0f;   // Adjust this value to move the tip left or right
    float roundness = 0.2f;    // 0.5f means 50% rounding for a more curved tip
    int segments = 8;          // Number of segments for smoother rounding

    // Upper pipe
    DrawRectangle(PosX - 2, 0, Width + 4, PosY, DARKGRAY);  // Smaller border
    DrawRectangle(PosX, 0, Width, PosY, color);

    // Lower pipe
    DrawRectangle(PosX - 2, PosY + GAP_HEIGHT, Width + 4, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), DARKGRAY);  // Smaller border
    DrawRectangle(PosX, PosY + GAP_HEIGHT, Width, (SCREEN_HEIGHT - GROUND_HEIGHT) - (PosY + GAP_HEIGHT), color);

    // Upper pipe tip (rounded)
    float tipPosX1 = PosX + (Width - tipWidth) / 2 + tipOffsetX;  // Centered with offset
    DrawRectangleRounded(Rectangle{ tipPosX1 - tweakBorder, PosY - tipHeight, tipWidth + 5, tipHeight + 4 }, roundness, segments, DARKGRAY);  // Border with rounded corners
    DrawRectangleRounded(Rectangle{ tipPosX1 - 2, PosY - tipHeight + 3, tipWidth, tipHeight - 2 }, roundness, segments, color);  // Rounded tip

    // Lower pipe tip (rounded)
    float tipPosX2 = PosX + (Width - tipWidth) / 2 + tipOffsetX;  // Centered with offset
    DrawRectangleRounded(Rectangle{ tipPosX2 - tweakBorder, PosY + GAP_HEIGHT, tipWidth + 5, tipHeight + 4 }, roundness, segments, DARKGRAY);  // Border with rounded corners
    DrawRectangleRounded(Rectangle{ tipPosX2 - 2, PosY + GAP_HEIGHT + 3, tipWidth, tipHeight - 2 }, roundness, segments, color);  // Rounded tip
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