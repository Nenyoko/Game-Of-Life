#include <raylib.h>

#include "grid.h"

int main() {
    InitWindow(512, 512, "Game of life");
    SetTargetFPS(60);

    Grid grid(32, 32);

    bool tick_status = false;
    unsigned short tick_cooldown = 0;
    const unsigned short target_cooldown = 4;

    while (!WindowShouldClose()) {
        grid.UpdateEdit();

        tick_status ^= IsKeyPressed(KEY_SPACE);
        if (tick_status) {
            tick_cooldown++;
            if(tick_cooldown >= target_cooldown) {
                grid.UpdateTick();
                tick_cooldown = 0;
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            grid.Clear();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            grid.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
