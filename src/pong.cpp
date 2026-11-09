#include "pong.h"
#include <raylib.h>
#include <iostream>

namespace
{
    const Color kGreen{38, 185, 154, 255};
    const Color kDarkGreen{20, 160, 133, 255};
    const Color kLightGreen{129, 204, 184, 255};
    const Color kYellow{243, 213, 91, 255};
} // namespace

namespace pong
{
    Ball::Ball(float startX, float startY, float radius, float speedX, float speedY)
        : position_{startX, startY}, speed_{speedX, speedY}, radius_(radius)
    {
    }

    void Ball::Update(int screenWidth, int screenHeight, int &playerScore, int &cpuScore)
    {
        position_.x += speed_.x;
        position_.y += speed_.y;

        if (position_.y + radius_ >= screenHeight || position_.y - radius_ <= 0)
        {
            speed_.y *= -1;
        }

        if (position_.x + radius_ >= screenWidth)
        {
            ++cpuScore;
            Reset(screenWidth, screenHeight);
        }
        else if (position_.x - radius_ <= 0)
        {
            ++playerScore;
            Reset(screenWidth, screenHeight);
        }
    }

    void Ball::Draw() const
    {
        DrawCircleV(position_, radius_, kYellow);
    }

    Vector2 Ball::Position() const
    {
        return position_;
    }

    float Ball::Radius() const
    {
        return radius_;
    }

    void Ball::ReverseHorizontalSpeed()
    {
        speed_.x *= -1;
    }

    void Ball::Reset(int screenWidth, int screenHeight)
    {
        position_ = {screenWidth / 2.0f, screenHeight / 2.0f};
        speed_.x *= GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;
        speed_.y *= GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;
    }

    Paddle::Paddle(float x, float y, float width, float height, float speed)
        : bounds_{x, y, width, height}, speed_(speed)
    {
    }

    void Paddle::Draw() const
    {
        DrawRectangleRounded(bounds_, 0.8f, 0, WHITE);
    }

    Rectangle Paddle::Bounds() const
    {
        return bounds_;
    }

    void Paddle::UpdatePlayer(int screenHeight)
    {
        if (IsKeyDown(KEY_UP))
        {
            bounds_.y -= speed_;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            bounds_.y += speed_;
        }

        LimitMovement(screenHeight);
    }

    void Paddle::MoveTowards(float targetY, int screenHeight)
    {
        const float centerY = bounds_.y + bounds_.height / 2.0f;
        if (centerY > targetY)
        {
            bounds_.y -= speed_;
        }
        else if (centerY < targetY)
        {
            bounds_.y += speed_;
        }

        LimitMovement(screenHeight);
    }

    void Paddle::LimitMovement(int screenHeight)
    {
        if (bounds_.y < 0)
        {
            bounds_.y = 0;
        }
        if (bounds_.y + bounds_.height > screenHeight)
        {
            bounds_.y = screenHeight - bounds_.height;
        }
    }

    void CpuPaddle::Update(float ballY, int screenHeight)
    {
        MoveTowards(ballY, screenHeight);
    }

    Game::Game(int screenWidth, int screenHeight)
        : screenWidth_(screenWidth),
          screenHeight_(screenHeight),
          ball_(screenWidth / 2.0f, screenHeight / 2.0f, 20.0f, 7.0f, 7.0f),
          player_(screenWidth - 35.0f, screenHeight / 2.0f - 120.0f, 25.0f, 120.0f, 6.0f),
          cpu_(10.0f, screenHeight / 2.0f - 60.0f, 25.0f, 120.0f, 6.0f)
    {
    }

    void Game::Update()
    {
        ball_.Update(screenWidth_, screenHeight_, playerScore_, cpuScore_);
        player_.UpdatePlayer(screenHeight_);
        cpu_.Update(ball_.Position().y, screenHeight_);

        if (CheckCollisionCircleRec(ball_.Position(), ball_.Radius(), player_.Bounds()) ||
            CheckCollisionCircleRec(ball_.Position(), ball_.Radius(), cpu_.Bounds()))
        {
            ball_.ReverseHorizontalSpeed();
        }
    }

    void Game::Draw() const
    {
        ClearBackground(kDarkGreen);
        DrawRectangle(screenWidth_ / 2, 0, screenWidth_ / 2, screenHeight_, kGreen);
        DrawCircle(screenWidth_ / 2, screenHeight_ / 2, 150.0f, kLightGreen);
        DrawLine(screenWidth_ / 2, 0, screenWidth_ / 2, screenHeight_, WHITE);
        DrawCircle(screenWidth_ / 2, screenHeight_ / 2, 20.0f, WHITE);

        ball_.Draw();
        cpu_.Draw();
        player_.Draw();
        DrawText(TextFormat("%i", cpuScore_), screenWidth_ / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore_), 3 * screenWidth_ / 4 - 20, 20, 80, WHITE);
    }
} // namespace pong
