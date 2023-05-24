#include "raylib.h"

class Ball {
public:
	float X;
	float Y;
	float Radius;
	float SpeedX;
	float SpeedY ;

	void draw() {
		DrawCircle((int)X, (int)Y, Radius, DARKBLUE);
	}
};

class Paddle {
public:
	float X;
	float Y;
	float Speed;
	float width, height;

	Rectangle getRect() {
		return Rectangle{ X - width / 2, Y - height / 2, 10, 100};
	}

	void draw() {
		DrawRectangleRec(getRect(), RED);
	}
};

int main() {
	Ball ball;
	InitWindow(800, 600, "Muliplayer_pong");
	// it is for showing the real fps of the screen;
	SetWindowState(FLAG_VSYNC_HINT);
	ball.X = GetScreenWidth() / 2.0f;
	ball.Y = GetScreenHeight() / 2.0f;
	ball.Radius = 10;
	ball.SpeedX = 300;
	ball.SpeedY = 300;

	// making object for left and right paddle and initalizing all the values
	Paddle leftPaddle;
	leftPaddle.X = 50;
	leftPaddle.Y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.Speed = 700;

	Paddle rightPaddle;
	rightPaddle.X = GetScreenWidth() - 50;
	rightPaddle.Y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.Speed = 700;

	const char* winnerText = nullptr;
	const char* gameName = "Multiplayer Pong";
	// in game loop we do all the update first than the drawing
	while (!WindowShouldClose())
	{
		// get frame time is very small number so we have to multiply it wiith bigger number
		ball.X += 1 * GetFrameTime() * ball.SpeedX;
		ball.Y += 1 * GetFrameTime() * ball.SpeedY;

		if (ball.Y < 60) {
			ball.Y = 60;
			ball.SpeedY *= -1;
		}

		if (ball.Y > GetScreenHeight()) {
			ball.Y = GetScreenHeight();
			ball.SpeedY *= -1;
		}

		//keyboard controls for the paddles
		if (IsKeyDown(KEY_W)) {
			leftPaddle.Y -= GetFrameTime() * leftPaddle.Speed;
			if (leftPaddle.Y <= 0) {
				leftPaddle.Y = 50;
			}
		}
		if (IsKeyDown(KEY_S)) {
			leftPaddle.Y += GetFrameTime() * leftPaddle.Speed;
			if (leftPaddle.Y >= GetScreenHeight()) {
				leftPaddle.Y = GetScreenHeight() - 50;
			}
		}
		if (IsKeyDown(KEY_UP)) {
			rightPaddle.Y -= GetFrameTime() * rightPaddle.Speed;
			if (rightPaddle.Y <= 0) {
				rightPaddle.Y = 50;
			}
		}
		if (IsKeyDown(KEY_DOWN)) {
			rightPaddle.Y += GetFrameTime() * rightPaddle.Speed;
			if (rightPaddle.Y >= GetScreenHeight()) {
				rightPaddle.Y = GetScreenHeight() - 50;
			}
		}
		if (winnerText and IsKeyDown(KEY_SPACE)) {
			ball.X = GetScreenWidth() / 2;
			ball.Y = GetScreenHeight() / 2;
			ball.SpeedX = 300;
			ball.SpeedY = 300;
			winnerText = nullptr;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.X, ball.Y }, ball.Radius, leftPaddle.getRect())) {
			if (ball.SpeedX < 0) {
				ball.SpeedX *= -1.1f;
				ball.SpeedY = (ball.Y - leftPaddle.Y) / (leftPaddle.height /2) * 300;

			}
			
		}
		if (CheckCollisionCircleRec(Vector2{ ball.X, ball.Y }, ball.Radius, rightPaddle.getRect())) {
			if (ball.SpeedX > 0) {
				ball.SpeedX *= -1;
				ball.SpeedY = (ball.Y - rightPaddle.Y) / (rightPaddle.height / 2) * 300;

			}
		}
		if (ball.X < 0) {
			winnerText = "Right Player Wins!";
		}
		if (ball.X > GetScreenWidth()) {
			winnerText = "Left Player Wins";
		}
		int textWidth = MeasureText(gameName, 60);
		
		BeginDrawing();
			ClearBackground(BLACK);

			DrawText(gameName, GetScreenWidth() / 2 - textWidth / 2, 0, 60, YELLOW);
			ball.draw();
			leftPaddle.draw();
			rightPaddle.draw();
			if (winnerText) {
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() /2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, VIOLET);
			}

		EndDrawing();

		//DrawFPS(10, 10);

	}

	CloseWindow();

	return 0;
}