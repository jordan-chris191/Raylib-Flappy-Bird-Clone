#include "Bird.h"
#include "Flight.h"

Bird::Bird()
{
    PosX = 50;
    PosY = 350;
    vY = 0;
    size = 38;
    currentFrame = 0;
    animationTime = 0.1f;
    timeSinceLastFrame = 0.0f;
    rotationAngle = 0.0f;
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
        rotationAngle = -25.0f;
    }
    else if (vY > 0) {
        rotationAngle += 100.0f * (deltaTime*rotationSpeed);
        if (rotationAngle > 70.0f) {        
            rotationAngle = 70.0f;
        }
    }
    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= animationTime)
    {
        timeSinceLastFrame = 0.0f;
        currentFrame = (currentFrame + 1) % 3;
    }
}

void Bird::Draw() const
{
   
    float aspectRatio = (float)textures[currentFrame].width / textures[currentFrame].height;
    float destWidth = size;
    float destHeight = size / aspectRatio;

    Vector2 origin = { textures[currentFrame].width / 2.0f, textures[currentFrame].height / 2.0f };

    DrawTexturePro(
        textures[currentFrame],                                   
        Rectangle{ 0, 0, (float)textures[currentFrame].width, (float)textures[currentFrame].height },
        Rectangle{ PosX, PosY, destWidth, destHeight },             
        origin,                                                      
        rotationAngle,                                               
        WHITE                                                        
    );
}

void Bird::LoadTextures()
{
    Image BirdUp = LoadImage("C:/Users/user/desktop/FlappyBird_assets/yellowbird-upflap.png");
    Image BirdMid = LoadImage("C:/Users/user/desktop/FlappyBird_assets/yellowbird-midflap.png");
    Image BirdDown = LoadImage("C:/Users/user/desktop/FlappyBird_assets/yellowbird-downflap.png");

    textures[0] = LoadTextureFromImage(BirdUp);
    textures[1] = LoadTextureFromImage(BirdMid);
    textures[2] = LoadTextureFromImage(BirdDown);

    UnloadImage(BirdUp);
    UnloadImage(BirdMid);
    UnloadImage(BirdDown);
}
