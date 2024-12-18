#include "raylib.h"
#include "game.h"
#include "colors.h"
#include <iostream>

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime > interval) {
		lastUpdateTime = currentTime;
		return true;
	} else {
		return false;
	}
}

int main ()
{
	Color darkBlue = {44, 44, 127, 255};

	Game game = Game();

	InitWindow(500, 620, "Hello Raylib");
	SearchAndSetResourceDir("resources");

	SetTargetFPS(60);	
	// game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(game.music);
		game.handleInput();

		if (eventTriggered(0.2)) {
			game.moveBlockDown();
		}

		// drawing
		BeginDrawing();
		ClearBackground(darkBlue);

		

		DrawText("Score", 365, 15, 24, WHITE);
		DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(GetFontDefault(), scoreText, 24, 1);

		DrawText(scoreText, 320 + (170 - textSize.x) / 2, 65, 24, WHITE);
		DrawText("Next", 370, 175, 24, WHITE);
		DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

		if (game.gameOver) {
			DrawText("Game Over", 320, 450, 24, WHITE);
		}

		game.draw();

		// end
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
