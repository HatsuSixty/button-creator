#include <raylib.h>
#include <stdio.h>

#include "stb_image_write.h"

#include "config.h"

#define WIDTH 110
#define HEIGHT 42

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "button-creator");
    SetTargetFPS(60);

#define SELECTOR_WIDTH SELECTOR_SIZE
#define SELECTOR_HEIGHT SELECTOR_WIDTH
#define SELECTOR_SQUARE_WIDTH (SELECTOR_PADDING * 2 + SELECTOR_WIDTH)

    Rectangle selector_rectangle =
        (Rectangle){.x = SELECTOR_PADDING + BORDER_SIZE,
                    .y = (HEIGHT / 2) - SELECTOR_HEIGHT / 2,
                    .width = SELECTOR_WIDTH,
                    .height = SELECTOR_HEIGHT};

    Texture selector_texture = LoadTexture(SELECTOR_TEXTURE);

    Rectangle text_rectangle =
        (Rectangle){.x = BORDER_SIZE + SELECTOR_SQUARE_WIDTH,
                    .y = BORDER_SIZE + TEXT_PADDING,
                    .width = WIDTH - (BORDER_SIZE + SELECTOR_SQUARE_WIDTH) -
                             BORDER_SIZE - TEXT_PADDING,
                    .height = HEIGHT - (BORDER_SIZE * 2) - (TEXT_PADDING * 2)};

    Font font = LoadFont(FONT);

    int text_width, text_height;
    {
        Vector2 dimensions = MeasureTextEx(font, TEXT, FONT_SIZE, FONT_SPACING);
        text_width = dimensions.x;
        text_height = dimensions.y;
    };

    RenderTexture text_texture = LoadRenderTexture(text_width, text_height);

    while (!WindowShouldClose()) {
        BeginTextureMode(text_texture);
        {
            ClearBackground(COLOR);
            DrawTextEx(font, TEXT, (Vector2){.x = 0, .y = 0}, FONT_SIZE,
                       FONT_SPACING, TEXT_COLOR);
        }
        EndTextureMode();

        BeginDrawing();
        {
            ClearBackground(COLOR);
            DrawRectangleLinesEx(
                (Rectangle){.x = 0, .y = 0, .width = WIDTH, .height = HEIGHT},
                BORDER_SIZE, BORDER_COLOR);

            DrawTexturePro(selector_texture,
                           (Rectangle){.width = selector_texture.width,
                                       .height = selector_texture.height,
                                       .x = 0,
                                       .y = 0},
                           selector_rectangle, (Vector2){0}, 0.0f, WHITE);
            DrawTexturePro(text_texture.texture,
                           (Rectangle){.width = text_width,
                                       .height = -text_height,
                                       .x = 0,
                                       .y = 0},
                           text_rectangle, (Vector2){0}, 0.0f, WHITE);
        }
        EndDrawing();
    }

    UnloadFont(font);
    UnloadRenderTexture(text_texture);

    Image data = LoadImageFromScreen();

    CloseWindow();

    stbi_write_png("button.png", WIDTH, HEIGHT, 4, data.data, WIDTH * 4);

    return 0;
}