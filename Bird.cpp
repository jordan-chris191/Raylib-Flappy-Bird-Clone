#include "Bird.h"
#include "Flight.h"

Bird::Bird()
{
    PosX = 50;
    PosY = 350;
    vY = 0;
    Size = 38;
    CurrentFrame = 0;
    AnimationTime = 0.1f;
    TimeSinceLastFrame = 0.0f;
    RotationAngle = 0.0f;
    Texture2D textures[3];
}

Bird::~Bird()
{
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(textures[i]);
    }
}

void Bird::Update(float deltaTime)
{
    int rotationSpeed = 3;
    if (vY < 0) {
        RotationAngle = -25.0f;
    }
    else if (vY > 0) {
        RotationAngle += 100.0f * (deltaTime*rotationSpeed);
        if (RotationAngle > 70.0f) {        
            RotationAngle = 70.0f;
        }
    }
    TimeSinceLastFrame += deltaTime;
    if (TimeSinceLastFrame >= AnimationTime)
    {
        TimeSinceLastFrame = 0.0f;
        CurrentFrame = (CurrentFrame + 1) % 3;
    }
}

void Bird::Draw() const
{
   
    float aspectRatio = (float)textures[CurrentFrame].width / textures[CurrentFrame].height;
    float destWidth = Size;
    float destHeight = Size / aspectRatio;

    Vector2 origin = { textures[CurrentFrame].width / 2.0f, textures[CurrentFrame].height / 2.0f };

    DrawTexturePro(
        textures[CurrentFrame],                                   
        Rectangle{ 0, 0, (float)textures[CurrentFrame].width, (float)textures[CurrentFrame].height },
        Rectangle{ PosX, PosY, destWidth, destHeight },             
        origin,                                                      
        RotationAngle,                                               
        WHITE                                                        
    );
}

void Bird::LoadTextures()
{
    Image BirdUp = LoadImage("FlappyBird_assets/yellowbird-upflap.png");
    Image BirdMid = LoadImage("FlappyBird_assets/yellowbird-midflap.png");
    Image BirdDown = LoadImage("FlappyBird_assets/yellowbird-downflap.png");

    textures[0] = LoadTextureFromImage(BirdUp);
    textures[1] = LoadTextureFromImage(BirdMid);
    textures[2] = LoadTextureFromImage(BirdDown);

    UnloadImage(BirdUp);
    UnloadImage(BirdMid);
    UnloadImage(BirdDown);
}
