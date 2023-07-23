#include <iostream>
#include <raylib.h>

using namespace std;

struct Ball
{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw() {
        DrawCircle((int) x, (int) y, radius, WHITE);
    }
};

struct Paddle
{
    float x, y;
    float speed;
    float width, height;
    int score;

    Rectangle GetRec()
    {
        return Rectangle{ x - width / 2 , y - height / 2 , width, height };
    }

    void Draw()
    {
        DrawRectangle(x - width/2, y - height/2, width, height, WHITE);
    }
};

int main() {
    InitWindow(800, 600, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;

    ball.x = GetScreenWidth() / 2.0;
    ball.y = GetScreenHeight() / 2.0;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle leftPaddle;
    leftPaddle.x = 20;
    leftPaddle.y = GetScreenHeight() / 2 ; 
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 700;
    leftPaddle.score = 0;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 20 ;
    rightPaddle.y = GetScreenHeight() / 2 ; 
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 700;
    rightPaddle.score = 0;


    while (!WindowShouldClose())
    {
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        if (ball.y < 0) {
            ball.y = 0;
            ball.speedY *= -1;
        } else if (ball.y > GetScreenHeight()) {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
        }

        if (ball.x < 0) {
            rightPaddle.score++;
            ball.speedX = 300;
            ball.speedY = 300;
            ball.x = GetScreenWidth() / 2.0;
            ball.y = GetScreenHeight() / 2.0;
        }
        else if (ball.x > GetScreenWidth()) {
            leftPaddle.score++;
            ball.speedX = 300;
            ball.speedY = 300;
            ball.x = GetScreenWidth() / 2.0;
            ball.y = GetScreenHeight() / 2.0;
        }


        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }
        else if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRec()))
        {
            if (ball.speedX < 0) {
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) *  - ball.speedX;
                ball.speedX *= -1.1f;
            }
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRec()))
        {
            if (ball.speedX > 0) {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * - ball.speedX;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();
        DrawText(TextFormat("%d : %d", leftPaddle.score, rightPaddle.score), GetScreenWidth() / 2 - 10, 30, 20, WHITE);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}