#include "Ball.h"

#include <cmath>

using namespace std;

namespace
{
const Color kBallColor{243, 213, 91, 255};
}

Ball::Ball(Vector2 startPosition, float radius, Vector2 startSpeed)
    : position_(startPosition), speed_(startSpeed), radius_(radius)
{
}

BallExit Ball::Update(int screenWidth, int screenHeight)
{
    position_.x += speed_.x;
    position_.y += speed_.y;

    if (position_.y - radius_ <= 0)
    {
        position_.y = radius_;
        speed_.y = abs(speed_.y);
    }
    else if (position_.y + radius_ >= screenHeight)
    {
        position_.y = screenHeight - radius_;
        speed_.y = -abs(speed_.y);
    }

    if (position_.x - radius_ <= 0)
    {
        Reset(screenWidth, screenHeight);
        return BallExit::PlayerScored;
    }
    if (position_.x + radius_ >= screenWidth)
    {
        Reset(screenWidth, screenHeight);
        return BallExit::CpuScored;
    }

    return BallExit::None;
}

void Ball::Draw() const
{
    DrawCircleV(position_, radius_, kBallColor);
}

void Ball::Reset(int screenWidth, int screenHeight)
{
    position_ = {screenWidth / 2.0f, screenHeight / 2.0f};
    speed_.x = abs(speed_.x) * (GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f);
    speed_.y = abs(speed_.y) * (GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f);
}

void Ball::BounceHorizontally()
{
    speed_.x *= -1.0f;
}

Vector2 Ball::Position() const
{
    return position_;
}

float Ball::Radius() const
{
    return radius_;
}

bool Ball::IsMovingRight() const
{
    return speed_.x > 0;
}
