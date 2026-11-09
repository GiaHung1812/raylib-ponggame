#pragma once

#include "Ball.h"
#include "Paddle.h"

class Game
{
public:
    Game(int screenWidth, int screenHeight);

    void Update();
    void Draw() const;

private:
    void HandleScore(BallExit ballExit);
    void HandlePaddleCollisions();

    int screenWidth_;
    int screenHeight_;
    int playerScore_ = 0;
    int cpuScore_ = 0;
    Ball ball_;
    Paddle player_;
    Paddle cpu_;
};
