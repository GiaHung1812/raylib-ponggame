#include <raylib.h>

#include "Game.h"

using namespace std;

int main()
{
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong Game!");
    SetTargetFPS(60);

    Game game(screen_width, screen_height);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        game.Update();
        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
