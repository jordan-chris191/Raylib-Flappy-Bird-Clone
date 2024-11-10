
#include "config.h"
Bird bird;
Texture2D digitTextures[10];
Ground ground, ground2;
Gravity gravity;
std::vector<Pipe> pipes;
int score = 0;
int gameFrame = 0;
bool isPaused = false;
bool isGameStarted = false;
bool isGameOver = false;
int numPipes = 2;
float deltaTime = 0.0f;
enum GameState {
    START,
    RUNNING,
    PAUSED,
    GAME_OVER
};
GameState currentGameState = START;
void Start()
{
    float hoverAmplitude = 1.0f;
    float hoverFrequency = 5.0f;
    float hoverOffset = hoverAmplitude * sin(GetTime() * hoverFrequency);
    bird.PosY += hoverOffset;
    bird.Update(GetFrameTime());
    bird.vY = 0;
    bird.Draw();
    ground.Draw();
    ground2.X = ground.X + 335;
    ground2.Draw();

    for (auto& pipe : pipes) pipe.Draw();
}
void InitPipes() {
    for (int i = 0; i < numPipes; i++) {
        Pipe newPipe;
        newPipe.PosX += i * 240;
        pipes.push_back(newPipe);
    }
}


void HandleCollision() {
    for (auto& pipe : pipes) {
        bool inGap = (bird.PosY > pipe.PosY && bird.PosY < pipe.PosY + GAP_HEIGHT);
        if (!inGap) {
            if (CheckAABBCollision(Vector2{ bird.PosX, bird.PosY }, bird.Size / 2, { pipe.PosX, 0, pipe.Width, pipe.PosY }) ||
                CheckAABBCollision(Vector2{ bird.PosX, bird.PosY }, bird.Size / 2, { pipe.PosX, pipe.PosY + GAP_HEIGHT, pipe.Width,
                SCREEN_HEIGHT - GROUND_HEIGHT - pipe.PosY - GAP_HEIGHT })) {
                isGameOver = true;
                return;
            }
            else {

                pipe.color = MARIOGREEN;
            }
        }
        else {
            pipe.color = MARIOGREEN;
        }

        if (pipe.PosX + pipe.Width < bird.PosX && !pipe.passed) {
            //if the bird succesfully passed through a pipe add score
            score++;
            pipe.passed = true;
        }
        if (pipe.PosX + pipe.Width < 0) {
            pipe.PosX = SCREEN_WIDTH;
            pipe.passed = false;
        }
    }
}

void HandleScreenTap()
{


}

void HandleGameOver()
{
    if (isGameOver) {
        deltaTime = 0;
        for (auto& pipe : pipes) pipe.Speed = 0;
    }
    else {
        for (auto& pipe : pipes) pipe.Speed = 200;
        gravity.Strength = 0.5f;
    }
}
void HandlePause() {
    if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }
    if (isPaused) {
        deltaTime = 0;
        for (auto& pipe : pipes) pipe.Speed = 0;

        gravity.Strength = 0;
    }
    else {
        for (auto& pipe : pipes) pipe.Speed = 200;
        gravity.Strength = 0.5f;
    }
}
void RunGame() {
    isGameStarted = true;
    score = 0;
    bird.PosY = SCREEN_HEIGHT / 2;
    pipes.clear();
    InitPipes();
}
void HandleGravity() {
    if (bird.PosY <= SCREEN_HEIGHT - GROUND_HEIGHT - bird.Size + 20) {
        ApplyGravity2d(bird.PosY, bird.vY, gravity.Strength);

    }
    else
    {
        bird.PosY = SCREEN_HEIGHT - GROUND_HEIGHT - bird.Size + 20;
        bird.vY = 0;
        //when the bird touches the ground
        isGameOver = true;
    }
}
void DrawEntities() {
    for (auto& pipe : pipes) {
        pipe.Draw();
    };
    ground.Draw();
    ground2.Draw();

}
void ScoreText()
{
    std::string scoreText = std::to_string(score);
    int scoreFontSize = 50;
    int scorePosX = SCREEN_WIDTH / 2 - MeasureText(scoreText.c_str(), scoreFontSize) / 2;
    int scorePosY = 60;
    int scorePosX2 = scorePosX + 3;
    int scorePosY2 = scorePosY + 3;
    int scorePosX3 = scorePosX + 2;
    int scorePosY3 = scorePosY + 2;
    int scorePosX4 = scorePosX + 1;
    int scorePosY4 = scorePosY + 1;

    //shadow effect
    DrawText(scoreText.c_str(), scorePosX4, scorePosY4, scoreFontSize, BLACK);
    DrawText(scoreText.c_str(), scorePosX3, scorePosY3, scoreFontSize, BLACK);
    DrawText(scoreText.c_str(), scorePosX2, scorePosY2, scoreFontSize, BLACK);
    DrawText(scoreText.c_str(), scorePosX, scorePosY, scoreFontSize, WHITE);
}
void DrawUI() {
    ScoreText();
    if (isPaused && !isGameOver) {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 50) / 2, SCREEN_HEIGHT / 2 - 25, 50, WHITE);
    }
}
void RunFlappyBirdApp() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone");
    Image icon = LoadImage("FlappyBird_assets/flappy-1.png");

    SetWindowIcon(icon);

    SetTargetFPS(60);
    InitAudioDevice();

    bird.LoadTextures();
    ground.LoadTexture();
    ground2.LoadTexture();


    Texture2D button = LoadTexture("FlappyBird_assets/restart-button.png");
    float frameHeight = (float)button.height / NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };
    Rectangle btnBounds = { SCREEN_WIDTH / 2.0f - button.width / 2.0f, SCREEN_HEIGHT / 2.0f - button.height + 300 / NUM_FRAMES / 2.0f, (float)button.width, frameHeight };
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = { 0.0f, 0.0f };
    Texture2D gameOver = LoadTexture("FlappyBird_assets/gameover.png");
    Texture2D background = LoadTexture("FlappyBird_assets/background-day.png");
    Sound wing = LoadSound("FlappyBird_assets/wing.wav");
    Sound swoosh = LoadSound("FlappyBird_assets/swoosh.wav");
    Sound die = LoadSound("FlappyBird_assets/audio_die.wav");
    Sound point = LoadSound("FlappyBird_assets/point.wav");
    Image startMessage = LoadImage("FlappyBird_assets/message.png");
    Texture2D startMessageTexture = LoadTextureFromImage(startMessage);
    UnloadImage(startMessage);

    bool isSoundPlayed = false;

    while (!WindowShouldClose()) {
        gameFrame++;
        mousePoint = GetMousePosition();
        btnAction = false;
        deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(SKYBLUE);
        sourceRec.y = btnState * frameHeight;
        float scaleX = (float)SCREEN_WIDTH / (float)background.width;
        float scaleY = (float)SCREEN_HEIGHT / (float)background.height;
        float scale = (scaleX < scaleY) ? scaleX + 0.05 : scaleY + 0.05;
        Vector2 back = { (SCREEN_WIDTH - background.width * scale) / 2, (SCREEN_HEIGHT - background.height * scale) / 2 };
        DrawTextureEx(background, back, 0.0f, scale, WHITE);

        switch (currentGameState) {
        case START:
            Start();
            DrawTexture(startMessageTexture, SCREEN_WIDTH / 2 - startMessageTexture.width / 2,
                SCREEN_HEIGHT / 2 - startMessageTexture.height / 2, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                RunGame();
                currentGameState = RUNNING;
                isSoundPlayed = false;
            }
            break;

        case RUNNING:
            HandlePause();
            if (!isPaused) {
                for (auto& pipe : pipes) pipe.Update(deltaTime);
                Fly(bird.PosY, bird.vY);
                if (IsKeyPressed(KEY_SPACE) && !isGameOver) PlaySound(wing);
                for (auto& pipe : pipes)
                {
                    if (pipe.PosX + pipe.Width < bird.PosX)
                    {
                        PlaySound(point);
                    }
                }

                HandleGravity();
                HandleCollision();
                HandleGameOver();

               
                if (isGameOver) {
                    currentGameState = GAME_OVER;
                }
            }
            DrawEntities();
            bird.Update(deltaTime);
            bird.Draw();
            DrawUI();
            break;
        case PAUSED:
            if (IsKeyPressed(KEY_P)) {
                currentGameState = RUNNING;
            }
            DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 50) / 2, SCREEN_HEIGHT / 2 - 25, 50, WHITE);
            break;

        case GAME_OVER:
            HandleGravity();
            for (auto& pipe : pipes) {
                pipe.Update(deltaTime);
            }
            ground.Draw();
            ground2.Draw();
            if (!isSoundPlayed) {
                PlaySound(die);
                isSoundPlayed = true;
            }
            bird.PosX + 10;
            bird.RotationAngle += 5.0f;
            if (bird.RotationAngle > 70.0f) {
                bird.RotationAngle = 70.0f;
            }

            DrawEntities();
            bird.Draw();
            DrawTexture(gameOver, SCREEN_WIDTH / 2 - gameOver.width / 2,
                SCREEN_HEIGHT / 2 - gameOver.height - 100 / 2, WHITE);
            Vector2 ButtonBounds = { btnBounds.x, btnBounds.y };
            DrawTextureRec(button, sourceRec, ButtonBounds, WHITE);

            if (CheckCollisionPointRec(mousePoint, btnBounds)) {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    btnState = 2;
                    PlaySound(swoosh);
                }

                else
                {
                    btnState = 1;
                    btnBounds.y = 390;
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    btnAction = true;
                }
            }
            else
            {
                btnState = 0;
                btnBounds.y = 400;
            }

            if (btnAction) {
                currentGameState = START;
                isGameStarted = false;
                isGameOver = false;
                isPaused = false;
                isSoundPlayed = false;
                score = 0;
                bird.PosY = SCREEN_HEIGHT / 2;
                pipes.clear();
                InitPipes();
                btnBounds.y = 460;
                bird.RotationAngle = 0;
            }
        }

        EndDrawing();
    }
    UnloadImage(icon);
    UnloadSound(die);
    UnloadSound(point);
    UnloadSound(swoosh);
    UnloadSound(wing);
    CloseAudioDevice();
    UnloadTexture(button);
    UnloadTexture(gameOver);
    UnloadTexture(startMessageTexture);
    CloseWindow();
}