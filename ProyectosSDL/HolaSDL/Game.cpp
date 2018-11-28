#include "Game.h"
#include "LoadManager.h"
#include "GameState.h"

/**
 * Constructor.
 */
Game::Game()
	: _window(nullptr), _renderer(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() < 0)
	{
		throw "Error loading the SDL font";
	}
	_window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_window == nullptr || _renderer == nullptr)
		throw "Error loading the SDL window or renderer";
	for (uint i = 0; i < NUMBER_TEXTURES; i++)
	{
		_textures[i] = new Texture(_renderer, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);
	}
	_fonts[BIGFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 72);
	_fonts[MEDIUMFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 40);

	_states.insert ( std::pair<States, State*> (States::GAME, new GameState(this, _renderer)) ) ;
	_gamemanager = new GameManager(this);
	LoadManager::load(this, "../saves/level.save");
}

/**
 * Destructor.
 */
Game::~Game()
{
	for (auto state : _states) {
		delete state.second;
	}

	for (uint i = 0; i < NUMBER_TEXTURES; i++)
	{
		delete _textures[i];
	}
	delete _fonts[BIGFONT];
	delete _fonts[MEDIUMFONT];
	delete _gamemanager;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	SDL_Quit();
}

/**
 * It gets all the textures of the game.
 */
Texture **Game::getTextures()
{
	return _textures;
}

/**
 * It gets all the fonts of the game.
 */
Font **Game::getFonts()
{
	return _fonts;
}

/**
 * Execute the main loop.
 */
void Game::run()
{
	State* cur = _states[States::GAME];
	cur->init();
	cur->run();
}

/**
 * Change the state of the game(it is needed to exit from the current state).
 */
void Game::changeState(const States &state)
{
	
}

void Game::newScore(const string &name, int score, double time)
{
	
}
GameManager *Game::gameManager()
{
	return _gamemanager;
}
