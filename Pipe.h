#ifndef PIPE_H
#define PIPE_H
#include "config.h"

struct Pipe {
    float PosX;
    float PosY;
    float Width;
    float Height;
    float Speed;
    Color color;
    bool passed = false;
    Pipe();
    void Draw() const; 
    void Update(float &deltaTime);
};

#endif