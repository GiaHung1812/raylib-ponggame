#pragma once

#include <raylib.h>

enum class BallExit
{
    None,
    PlayerScored,
    CpuScored
};

class Ball
{
public:
    Ball(Vector2 startPosition, float radius, Vector2 startSpeed);

    BallExit Update(int screenWidth, int screenHeight);
    void Draw() const;
    void Reset(int screenWidth, int screenHeight);
    void BounceHorizontally();

    Vector2 Position() const;
    float Radius() const;
    bool IsMovingRight() const;

private:
    Vector2 position_;
    Vector2 speed_;
    float radius_;
};
