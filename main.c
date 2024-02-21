#include "raylib.h"

typedef struct _Circle {
    float x;
    float y;
    float r;
    float mass;
    float velocity_x;
    float velocity_y;
} Circle;

void draw_circle(Circle circle) {

    DrawCircle(circle.x, circle.y, 1, BLACK);

    DrawCircleLines(circle.x, circle.y, circle.r-0.5, BLACK);
    DrawCircleLines(circle.x, circle.y, circle.r, BLACK);
    DrawCircleLines(circle.x, circle.y, circle.r+0.5, BLACK);

}

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Circle circle = (Circle) {screenWidth / 2, screenHeight / 2, 30, 1, 0, 0};

    while (!WindowShouldClose())
    {

        float delta = GetFrameTime();
        float force = 3.0;

        if (IsKeyDown(KEY_RIGHT)) {
            circle.velocity_x += force / circle.mass * delta;
        }
        if (IsKeyDown(KEY_LEFT)) {
            circle.velocity_x -= force / circle.mass * delta;
        }
        if (IsKeyDown(KEY_UP)) {
            circle.velocity_y -= force / circle.mass * delta;
        }
        if (IsKeyDown(KEY_DOWN)) {
            circle.velocity_y += force / circle.mass * delta;
        }

        circle.x += circle.velocity_x;
        circle.y += circle.velocity_y;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_circle(circle);

        EndDrawing();
    }


    CloseWindow();

    return 0;
}