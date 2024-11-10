#ifndef BIRD_H
#define BIRD_H

#include "raylib.h"

class Bird {
public:
    float PosX, PosY;        // Position of the bird
    float vY;                // Vertical velocity
    float Size;              // Size of the bird (for collision detection)
    int CurrentFrame;        // Current frame for animation
    float AnimationTime;     // Time per frame for animation
    float TimeSinceLastFrame; // Timer to keep track of frame changes
    float RotationAngle = 0.0f;
    Texture2D textures[3];  
    Bird();
    ~Bird();
    void Update(float deltaTime); // Update the bird's animation frame
    void Draw() const;           // Draw the bird on the screen
    void LoadTextures();         // Load the bird textures

};

#endif // BIRD_H