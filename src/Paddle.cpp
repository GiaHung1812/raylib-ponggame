#include "Paddle.h"

using namespace std;

Paddle::Paddle(float x, float y, float width, float height, float speed)
    : bounds_{x, y, width, height}, speed_(speed)
{
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

    LimitToScreen(screenHeight);
}

void Paddle::UpdateCpu(float targetY, int screenHeight)
{
    const float centerY = bounds_.y + bounds_.height / 2.0f;
    if (centerY < targetY)
    {
        bounds_.y += speed_;
    }
    else if (centerY > targetY)
    {
        bounds_.y -= speed_;
    }

    LimitToScreen(screenHeight);
}

void Paddle::Draw() const
{
    DrawRectangleRounded(bounds_, 0.8f, 0, WHITE);
}

Rectangle Paddle::Bounds() const
{
    return bounds_;
}

void Paddle::LimitToScreen(int screenHeight)
{
    if (bounds_.y < 0)
    {
        bounds_.y = 0;
    }
    else if (bounds_.y + bounds_.height > screenHeight)
    {
        bounds_.y = screenHeight - bounds_.height;
    }
}
