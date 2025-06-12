#include <raylib.h>
#include <raymath.h>

#include "math/maths.h"
#include "render/RenderTarget.h"
#include "render/Renderer.h"
#include "world/Scene.h"

int main()
{
    Renderer renderer{};
    RenderTarget target{960, 540};
    // RenderTarget target{640, 360};
    //  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_UNFOCUSED);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);
    InitWindow(target.size.x, target.size.y, "Test");
    Texture2D texture{LoadTextureFromImage(GenImageColor(target.size.x, target.size.y, BLACK))};
    SetExitKey(KEY_NULL);

    Scene scene{};
    bool toggle = false;

    Vector2 window_size{target.size};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE) ||
            (toggle ? IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) : IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            if (toggle)
                EnableCursor();
            else
                DisableCursor();
            toggle = !toggle;
        }

        if (IsWindowResized())
        {
            window_size.x = GetScreenWidth();
            window_size.y = GetScreenHeight();
        }

        scene.update(GetFrameTime());
        renderer.Render(target, scene);

        UpdateTexture(texture, &(*target.colour_buffer.begin()));
        BeginDrawing();
        DrawTexturePro(texture, {0, 0, target.size.x, target.size.y}, {0, 0, window_size.x, window_size.y}, {0, 0}, 0,
                       WHITE);
        DrawText(std::to_string(GetFPS()).c_str(), 5, 5, 24, GREEN);
        EndDrawing();
    }

    CloseWindow();
}
