#include "Game.h"
#include "Error.h"

Game* Game::instance= nullptr;

Game::Game(std::string title,int width, int height)
{
	if(nullptr != Game::instance)
	{
		Error("Second instantion of the game!");
	}
	Game::instance= this;
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		Error(SDL_GetError());
	}
	int result= IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	if(0 == result)
	{
		Error("Loading SDL_image failed");
	}
	if(0 == (result & IMG_INIT_JPG ) )
	{
		Error("Loading IMG_INIT_JPG failed");
	}
	if(0 == (result & IMG_INIT_PNG) )
	{
		Error("Loading IMG_INIT_PNG failed");
	}
	if(0 == (result & IMG_INIT_TIF ))
	{
		Error("Loading IMG_INIT_TIF failed");
	}
	window= SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(nullptr == window)
	{
		Error(SDL_GetError());
	}
	renderer= SDL_CreateRenderer(window, -1, 0);
	if(nullptr == window)
	{
		Error(SDL_GetError());
	}
	state= new State();
}

Game::~Game()
{
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game& Game::GetInstance(void)
{
	return *(Game::instance);
}

State& Game::GetState(void) const
{
	return *state;
}

SDL_Renderer* Game::GetRenderer(void)const
{
	return renderer;
}

void Game::Run(void)
{
	while(!state->QuitRequested())
	{
		state->Update();
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}
