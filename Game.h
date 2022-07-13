#pragma once
#include "SDL.h"
#include <vector>
using namespace std;

struct Vector2
{
	float x, y;
};

struct Ball
{
	vector<float> x;
	vector<float> y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;

	bool mIsRunning;

	Vector2 mPaddlePos_1;
	Vector2 mPaddlePos_2;
	Vector2 mBallPos;
	Vector2 mBallVel;

	Uint32 mThicksCount;

	int mPaddledir_1;
	int mPaddledir_2;

	Ball Ball_Pos;
	Ball Ball_Spd;
	vector<Ball> Balls;
};