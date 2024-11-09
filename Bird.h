#ifndef BIRD_H
#define BIRD_H

#include "raylib.h"

class Bird {
public:
    float PosX, PosY;        // Position of the bird
    float vY;                // Vertical velocity
    float size;              // Size of the bird (for collision detection)
    int currentFrame;        // Current frame for animation
    float animationTime;     // Time per frame for animation
    float timeSinceLastFrame; // Timer to keep track of frame changes
    float rotationAngle = 0.0f;
    Texture2D textures[3];  
    Bird();
    ~Bird();
    void Update(float deltaTime); // Update the bird's animation frame
    void Draw() const;           // Draw the bird on the screen
    void LoadTextures();         // Load the bird textures

};

#endif // BIRD_H