#include "Game.h"

using namespace std;

namespace
{
const Color kGreen{38, 185, 154, 255};
const Color kDarkGreen{20, 160, 133, 255};
const Color kLightGreen{129, 204, 184, 255};
}

Game::Game(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
      screenHeight_(screenHeight),
      ball_({screenWidth / 2.0f, screenHeight / 2.0f}, 20.0f, {7.0f, 7.0f}),
      player_(screenWidth - 35.0f, screenHeight / 2.0f - 120.0f, 25.0f, 120.0f, 6.0f),
      cpu_(10.0f, screenHeight / 2.0f - 60.0f, 25.0f, 120.0f, 6.0f)
{
}

void Game::Update()
{
    player_.UpdatePlayer(screenHeight_);
    cpu_.UpdateCpu(ball_.Position().y, screenHeight_);

    HandleScore(ball_.Update(screenWidth_, screenHeight_));
    HandlePaddleCollisions();
}

void Game::Draw() const
{
    ClearBackground(kDarkGreen);
    DrawRectangle(screenWidth_ / 2, 0, screenWidth_ / 2, screenHeight_, kGreen);
    DrawCircle(screenWidth_ / 2, screenHeight_ / 2, 150.0f, kLightGreen);
    DrawLine(screenWidth_ / 2, 0, screenWidth_ / 2, screenHeight_, WHITE);
    DrawCircle(screenWidth_ / 2, screenHeight_ / 2, 20.0f, WHITE);

    ball_.Draw();
    player_.Draw();
    cpu_.Draw();
    DrawText(TextFormat("%i", cpuScore_), screenWidth_ / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", playerScore_), 3 * screenWidth_ / 4 - 20, 20, 80, WHITE);
}

void Game::HandleScore(BallExit ballExit)
{
    if (ballExit == BallExit::PlayerScored)
    {
        ++playerScore_;
    }
    else if (ballExit == BallExit::CpuScored)
    {
        ++cpuScore_;
    }
}

void Game::HandlePaddleCollisions()
{
    const bool hitsPlayer = ball_.IsMovingRight() &&
                            CheckCollisionCircleRec(ball_.Position(), ball_.Radius(), player_.Bounds());
    const bool hitsCpu = !ball_.IsMovingRight() &&
                        CheckCollisionCircleRec(ball_.Position(), ball_.Radius(), cpu_.Bounds());

    if (hitsPlayer || hitsCpu)
    {
        ball_.BounceHorizontally();
    }
}
