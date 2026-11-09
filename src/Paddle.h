#pragma once

#include <raylib.h>

class Paddle
{
public:
    Paddle(float x, float y, float width, float height, float speed);

    void UpdatePlayer(int screenHeight);
    void UpdateCpu(float targetY, int screenHeight);
    void Draw() const;

    Rectangle Bounds() const;

private:
    void LimitToScreen(int screenHeight);

    Rectangle bounds_;
    float speed_;
};
