#include "raylib.h"
#include "raymath.h"
#include "math.h"

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

int circle_collision(Circle c1, Circle c2) {
    Vector2 v1 = (Vector2) {c1.x, c1.y};
    Vector2 v2 = (Vector2) {c2.x, c2.y};

    float coldist = c1.r + c2.r;

    if (Vector2Distance(v1, v2) <= coldist) {
        return 1;
    }

    return 0;

}

float circle_dist(Circle c1, Circle c2) {
    Vector2 v1 = (Vector2) {c1.x, c1.y};
    Vector2 v2 = (Vector2) {c2.x, c2.y};

    return Vector2Distance(v1, v2);
}

float circle_angle(Circle c1, Circle c2) {
    Vector2 v1 = (Vector2) {c1.x, c1.y};
    Vector2 v2 = (Vector2) {c2.x, c2.y};

    return Vector2Angle(v1, v2);
}

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Circle circle = (Circle) {screenWidth / 3, screenHeight / 2, 30, 1, 0, 0};

    Circle circle2 = (Circle) {screenWidth / 3 * 2, screenHeight / 2, 30, 1, 0, 0};


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

        if (IsKeyDown(KEY_D)) {
            circle2.velocity_x += force / circle2.mass * delta;
        }
        if (IsKeyDown(KEY_A)) {
            circle2.velocity_x -= force / circle2.mass * delta;
        }
        if (IsKeyDown(KEY_W)) {
            circle2.velocity_y -= force / circle2.mass * delta;
        }
        if (IsKeyDown(KEY_S)) {
            circle2.velocity_y += force / circle2.mass * delta;
        }

        circle.x += circle.velocity_x;
        circle.y += circle.velocity_y;

        circle2.x += circle2.velocity_x;
        circle2.y += circle2.velocity_y;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_circle(circle);
            draw_circle(circle2);

            if (circle_collision(circle, circle2) == 1) {
                DrawText("pussy", 0, 0, 10, BLACK);
                float angle = circle_angle(circle, circle2);
                float dist = circle_dist(circle, circle2);

                float colfactor = 50;

                // only do it to circle 1
                circle.velocity_x -= cos(angle) * dist * colfactor * delta;
                circle.velocity_y -= sin(angle) * dist * colfactor * delta;
            }


        EndDrawing();
    }


    CloseWindow();

    return 0;
}