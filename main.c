#include "raylib.h"

int main(void) {
  const int screenWidth = 1400;
  const int screenHeight = 700;

  // Window Initialization with OpenGL context
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  // Init world objects
  int renderTextureWidth = screenWidth - 10;
  int renderTextureHeight = screenHeight - 10;
  RenderTexture2D target =
      LoadRenderTexture(renderTextureWidth, renderTextureHeight);

  struct paddle {
    Vector2 position;
    Vector2 size;
    Color color;
  };

  struct paddle player = {{100.0f, (float)screenHeight / 2}, {25, 80}, BLUE};
  struct paddle enemy = {{1300.0f, (float)screenHeight / 2}, {25, 80}, MAROON};

  Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
  Vector2 ballSpeed = {5.0f, 4.0f};
  int ballRadius = 20;
  bool collision = false;

  SetTargetFPS(60);

  // Main loop
  // ----------------------------------------------------------
  while (!WindowShouldClose()) {
    // Update vars here
    // ----------------------------------------------------------

    // Ball movement logic
    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    // Wall collision bounce logic
    if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) ||
        (ballPosition.x <= ballRadius))
      ballSpeed.x *= -1.0f;
    if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) ||
        (ballPosition.y <= ballRadius))
      ballSpeed.y *= -1.0f;

    // Control keys
    if (IsKeyDown(KEY_UP))
      player.position.y -= 8.0f;
    if (IsKeyDown(KEY_DOWN))
      player.position.y += 8.0f;

    // Paddle collision bounce logic
    Rectangle playerRect = {player.position.x, player.position.y, player.size.x,
                            player.size.y};
    collision =
        CheckCollisionCircleRec(ballPosition, (float)ballRadius, playerRect);

    if (collision) {
      ballSpeed.x *= -1.0f;
    }

    // Draw
    // ----------------------------------------------------------
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawCircleV(ballPosition, (float)ballRadius, WHITE);

    DrawRectangleV(player.position, player.size, player.color);
    DrawRectangleV(enemy.position, enemy.size, enemy.color);

    DrawText("Move player with arrow keys", 10, 10, 20, BLACK);
    DrawText(TextFormat("Collision detected: %i", collision), 10, 40, 20,
             BLACK);
    DrawText(TextFormat("Player position y: %.0f", player.position.y), 10, 70,
             20, BLACK);

    EndDrawing();
  }

  // Window De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
