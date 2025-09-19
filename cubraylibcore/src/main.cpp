#include "raylib.h"

int main()
{
    InitWindow(800, 450, "raylibtest");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}