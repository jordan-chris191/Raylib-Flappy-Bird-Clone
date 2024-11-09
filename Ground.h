#ifndef GROUND_H
#define GROUND_H
#include "config.h"

struct Ground
{
    float X;                   // Position of the ground (X-axis)
    float Y;                   // Position of the ground (Y-axis)
    float Height;              // Height of the ground (fixed at GROUND_HEIGHT)
    float Width;               // Width of the ground
    Texture2D texture;        // Single texture for the ground

    Ground();              
    ~Ground();
    void LoadTexture();        // Method to load texture
    void Draw() const;         // Method to draw the ground
};

#endif
