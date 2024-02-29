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

    Circle circle = (Circle) {screenWidth / 3, screenHeight / 4 * 4, 30, 1, 0, 0};

    Circle circle2 = (Circle) {screenWidth / 3 * 2, screenHeight / 2, 30, 2, 0, 0};

    float gravity = 75;

    float floor_height = screenHeight / 2;

    //WaitTime(0.5);


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

        if (IsKeyPressed(KEY_SPACE)) {
            circle.y = screenHeight;
            circle.velocity_y = 0;
        }
        if (IsKeyPressed(KEY_T)) {
            circle.y = 0;
            circle.velocity_y = 0;
        }
        if (IsKeyPressed(KEY_UP)) {
            gravity += 10;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            gravity -= 10;
        }

        circle.velocity_y += gravity * delta;
        circle2.velocity_y += gravity * delta;

        circle.x += circle.velocity_x * delta;
        circle.y += circle.velocity_y * delta;

        circle2.x += circle2.velocity_x * delta;
        circle2.y += circle2.velocity_y * delta;


        if (circle_collision(circle, circle2) == 1) {
            float angle = circle_angle(circle, circle2);
            float dist = circle_dist(circle, circle2);

            float colfactor = 2;

            float faccolfactor = colfactor * (fabs(circle.velocity_x) + fabs(circle.velocity_y) + fabs(circle2.velocity_x) + fabs(circle2.velocity_y));

            // only do it to circle 1
            circle.velocity_x -= (cos(angle) * dist * faccolfactor * delta) / circle.mass;
            circle.velocity_y -= (sin(angle) * dist * faccolfactor * delta) / circle.mass;

            circle2.velocity_x += (cos(angle) * dist * faccolfactor * delta) / circle2.mass;
            circle2.velocity_y += (sin(angle) * dist * faccolfactor * delta) / circle2.mass;
        }

        float c1depth = circle.y + circle.r - floor_height; // how "deep" into the floor circle1 is
        float c2depth = circle2.y + circle2.r - floor_height;
        float floorfac = 0.1; // how bouncy floor is

        if (c1depth > 0) {
            //circle.velocity_y -= c1depth * c1depth * delta * floorfac;
            float oldv = circle.velocity_y;

            // push factor
            float push = c1depth*5*delta;
            if (push <= 1) {
                push = pow(c1depth * delta + 1, 1);
                circle.velocity_y = -1 * sqrt(2*c1depth*gravity) * push;
            } else {
                circle.velocity_y = -1 * sqrt(2*c1depth*gravity) * push;
            }
            //circle.velocity_y -= abs(oldv) * 0.6; // makes it slightly bouncy. abs is to ensure the old energy only makes it go up.

        }
        if (circle2.y + circle2.r > floor_height) {
            circle2.velocity_y -= c2depth * c2depth * delta * floorfac;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_circle(circle);
            draw_circle(circle2);

            //DrawLine(0, floor_height-1, screenWidth, floor_height-1, BLACK);
            DrawLine(0, floor_height, screenWidth, floor_height, BLACK);
            //DrawLine(0, floor_height+1, screenWidth, floor_height+1, BLACK);


        EndDrawing();
    }


    CloseWindow();

    return 0;
}