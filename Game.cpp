#include "Game.h"
#include <vector>
const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
,mRenderer(nullptr)
,mThicksCount(0)
,mPaddledir_1(0)
,mPaddledir_2(0)
{
	
}
 
bool Game::Initialize()
{
	int sdResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdResult != 0)
	{
		SDL_Log("Unable to initialize : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ Chapter1", 100, 100, 1024, 768, 0);

	if (!mWindow)
	{
		SDL_Log("Failed to creat window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Failed to creat renderer : %s", SDL_GetError());
		return false;
	}
    
	mPaddlePos_1.x = 10.0f;
	mPaddlePos_1.y = 768.0f / 2.0f;
	mPaddlePos_2.x = 1000.0f;
	mPaddlePos_2.y = 768.0f / 2.0f;
	/*
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	*/
	
	Ball_Pos.x.push_back(1024.0f / 2.0f);
	Ball_Pos.y.push_back(768.0f / 2.0f);
	Ball_Spd.x.push_back(-200.0f);
	Ball_Spd.y.push_back(235.0f);
	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()	
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddledir_1 = 0;
	mPaddledir_2 = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddledir_1 -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddledir_1 += 1;
	}
	if(state[SDL_SCANCODE_UP])
	{
		mPaddledir_2 -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		mPaddledir_2 += 1;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mThicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mThicksCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mThicksCount = SDL_GetTicks();

	if (mPaddledir_1 != 0)
	{
		mPaddlePos_1.y += mPaddledir_1 * 300.0f * deltaTime;

		if (mPaddlePos_1.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos_1.y = (paddleH / 2.0f + thickness);
		}
		if (mPaddlePos_1.y > (768.0f - paddleH / 2.0f + thickness))
		{
			mPaddlePos_1.y = (768.0f - paddleH / 2.0f + thickness);
		}
	}

	if (mPaddledir_2 != 0)
	{
		mPaddlePos_2.y += mPaddledir_2 * 300.0f * deltaTime;

		if (mPaddlePos_2.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos_2.y = (paddleH / 2.0f + thickness);
		}
		if (mPaddlePos_2.y > (768.0f - paddleH / 2.0f + thickness))
		{
			mPaddlePos_2.y = (768.0f - paddleH / 2.0f + thickness);
		}
	}
	/*
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff_1 = mPaddlePos_1.y - mBallPos.y;
	float diff_2 = mPaddlePos_2.y - mBallPos.y;
	diff_1 = (diff_1 > 0.0f) ? diff_1 : -diff_1;
	diff_2 = (diff_2 > 0.0f) ? diff_2 : -diff_2;
	if ((diff_1 <= paddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f) || (diff_2 <= paddleH / 2.0f && mBallPos.x <= 1000.0f && mBallPos.x >= 995.0f && mBallVel.x > 0.0f))
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x <= 0.0f || (mBallPos.x >= 1015.0f))
	{
		mIsRunning = false;
	}

	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1.0f;
	}
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1.0f;
	}
	*/
	

}


void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect wall  
	{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect paddle_1{
		static_cast<int>(mPaddlePos_1.x),
		static_cast<int>(mPaddlePos_1.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};

	SDL_RenderFillRect(mRenderer, &paddle_1);

	SDL_Rect paddle_2{
		static_cast<int>(mPaddlePos_2.x),
		static_cast<int>(mPaddlePos_2.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};

	SDL_RenderFillRect(mRenderer, &paddle_2);

	/*
	SDL_Rect Ball
	{
		static_cast<int>(mBallPos.x - thickness/2),
    	static_cast<int>(mBallPos.y - thickness/2),
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &Ball);
	*/

	SDL_RenderPresent(mRenderer);
}