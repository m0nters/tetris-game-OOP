#include<raylib.h>
#include"game.h"
#include"Color.h"
#include<iostream>

double prevTime = 0;
bool GameSpeed(double diff)
{
	double currentTime = GetTime();
	if (currentTime - prevTime >= diff)
	{
		prevTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	InitWindow(500, 620, "Tetris Game");
	SetTargetFPS(60);

	Font font = LoadFontEx("Cooper_Black.ttf", 64, 0, 0);
	
	Game game = Game();

	double startTime = GetTime();
	double currentTime, elapsedTime;
	int elapsedSeconds, minutes = 0, seconds = 0;
	Texture2D background = LoadTexture("tetris_background.png");
	Texture2D start_game = LoadTexture("start_game.png");
	RenderTexture2D startGameTexture = LoadRenderTexture(500, 620);
	bool gameStarted = false;
	Sound game_over = LoadSound("game_over.mp3");
		while (!WindowShouldClose())
		{
		BeginTextureMode(startGameTexture);
		DrawTexture(start_game, 0, 0, WHITE);
		EndTextureMode();

		BeginDrawing();

		if (!gameStarted)
		{
			ClearBackground(darkBlue);
			DrawTextureRec(startGameTexture.texture, Rectangle{ 0, 0, static_cast<float>(startGameTexture.texture.width), static_cast<float>(startGameTexture.texture.height) }, Vector2{ 0, 0 }, WHITE);

			if (IsKeyPressed(KEY_ENTER))
			{
				gameStarted = true;
				startTime = GetTime();
			}
		}
		else
		{
			if (!game.gameOver && !game.musicStopped)
			{
				currentTime = GetTime();
				elapsedTime = currentTime - startTime;
				elapsedSeconds = static_cast<int>(elapsedTime);
				minutes = elapsedSeconds / 60;
				seconds = elapsedSeconds % 60;
				StopSound(game_over);
			}

			SetMusicVolume(game.music, 0.5);
			UpdateMusicStream(game.music);

			game.HandleInput();
			
			if (GameSpeed(game.moveSpeed))
			{
				game.MoveBlockDown();
			}
			ClearBackground(darkBlue);
			DrawTexture(background, 310, 0, grey);

			game.Draw();
			DrawTextEx(font, "SCORE", { 340, 15 }, 40, 2, WHITE);
			DrawTextEx(font, "NEXT", { 340, 140 }, 40, 2, WHITE);
			DrawTextEx(font, "LEVEL", { 340, 450 }, 40, 2, WHITE);

			if (game.gameOver)
			{
				float rectWidth = 250.0f;
				float rectHeight = 150.0f;
				Vector2 rectPosition = { 37, 237 };

				DrawRectangleRounded({ rectPosition.x, rectPosition.y, rectWidth, rectHeight }, 0.2f, 10, black);

				const char* gameOverText = "GAME OVER";
				Vector2 textSize = MeasureTextEx(font, gameOverText, 38, 2);

				DrawTextEx(font, gameOverText, { rectPosition.x + (rectWidth - textSize.x) / 2, rectPosition.y + (rectHeight - textSize.y) / 2 }, 40, 2, red);
			}
			if (game.gameOver && !game.musicStopped)
			{
				PlaySound(game_over);
				game.musicStopped = true;
				startTime = currentTime;
			}
			if (game.musicStopped)
			{
				StopMusicStream(game.music);
			}
			else PlayMusicStream(game.music);
			DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, black);
			DrawRectangleRounded({ 320, 185, 170, 140 }, 0.3, 6, black);
			DrawRectangleRounded({ 320, 490, 170, 60 }, 0.3, 6, black);
			char scoreText[10];
			sprintf_s(scoreText, sizeof(scoreText), "%d", game.score);
			Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
			DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, YELLOW);

			char levelText[3];
			sprintf_s(levelText, sizeof(levelText), "%d", game.currentLevel);
			Vector2 levelTextSize = MeasureTextEx(font, levelText, 38, 2);
			DrawTextEx(font, levelText, { 320 + (170 - levelTextSize.x) / 2, 500 }, 38, 2, YELLOW);

			char timeText[16];
			sprintf_s(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

			DrawTextEx(font, "TIME", { 355, 340 }, 40, 2, WHITE);
			Vector2 timeTextSize = MeasureTextEx(font, timeText, 38, 2);

			float timeRectWidth = 170;
			float timeRectHeight = 60;
			Vector2 timeRectPos = { 320, 380 };

			DrawRectangleRounded({ timeRectPos.x, timeRectPos.y, timeRectWidth, timeRectHeight }, 0.3, 6, black);

			DrawTextEx(font, timeText, { timeRectPos.x + (timeRectWidth - timeTextSize.x) / 2, timeRectPos.y + (timeRectHeight - timeTextSize.y) / 2 }, 38, 2, YELLOW);
		}

		EndDrawing();
}
	UnloadSound(game_over);
	UnloadTexture(background);
	CloseWindow();

	return 0;			
}