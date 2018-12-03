#include "State.h"
#include "Game.h"
#include "Block.h"
#include "Wall.h"
#include "Ball.h"
#include "Paddle.h"
#include "Button.h"
#include "Counter.h"
#include <fstream>
#include "CollisionLogic.h"


/**
 * Constructor.
 */


void State::_render() const {
	SDL_RenderClear(_renderer);
	for (auto gameObject : _gameObjects) {
		gameObject->render();
	}
	SDL_RenderPresent(_renderer);
}

void State::_update() { 
	for (auto gameObject : _gameObjects) {
		gameObject->update();
	}
}

void State::_handleEvents() { 
	SDL_Event event;
	while (!_exit && SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			_exit = true;
		for (auto gameObject : _gameObjects) {
			gameObject->handleEvents(event);
		}
	}
}

void State::_fixUpdate(float32 time) { 
	_world->Step(time, 8, 3);
}

void State::_destroy() {
	for (list<GameObject*>::iterator object : _pendingOnDestroy) {
		delete *object;
		*object = nullptr;
		_gameObjects.erase(object);
	}
	_pendingOnDestroy.clear();
}

State* State::current = nullptr;

void State::destroy(list<GameObject*>::iterator& gameObjectId) {
	_pendingOnDestroy.push_back(gameObjectId);
}

State::State(Game *game, SDL_Renderer *renderer) 
	: _game(game), _renderer(renderer) {
	_world = new b2World(b2Vec2(0.0f, 0.0f));
	_listenerLogic = new CollisionLogic();
	_world->SetContactListener(_listenerLogic);
}

State::~State() { 
	for (auto gameObject : _gameObjects) {
		delete gameObject;
	}
	_pendingOnDestroy.clear();
	_gameObjects.clear();
	delete _world;
	delete _listenerLogic;
}

void State::run() { 

	b2Timer startTime;
	while (!_exit)
	{
		_handleEvents();
		_update();
		if (startTime.GetMilliseconds() >= 0.001f/(FRAMERATE))
		{
			_fixUpdate(startTime.GetMilliseconds());
			startTime.Reset();
		}
		_render();
		_destroy();
	}
	_end();
}

void State::add(GameObject& gameObject) {
	_gameObjects.push_front(&gameObject);
	gameObject.setId(_gameObjects.begin());
}

void State::load(string& filename) {
	// Open a readonly file stream
	ifstream file(filename.c_str());
	if (file.good())
	{
		while (!file.eof()) {
			GAME_OBJECTS type;
			file >> type;
			GameObject *gameObject;
			switch (type)
			{
			case block:
				gameObject = new Block();
				file >> *gameObject;
				//static_cast<Block*>(gameObject)->Init(*_world, _game->getTextures()[BRICKS]);
				_gameObjects.push_back(gameObject);
				break;/*
			case wall: 
				Wall wall;
				file >> wall;
				_gameObjects->push_back(wall);
				_renderableGameObjects->push_back(wall);
				break;
			case ball:
				Ball ball;
				file >> ball;
				_gameObjects->push_back(ball);
				_renderableGameObjects->push_back(ball);
				break;
			case paddle:
				Paddle paddle;
				file >> paddle;
				_gameObjects->push_back(paddle);
				_renderableGameObjects->push_back(paddle);
				_controllableGameObjects->push_back(paddle);
				break;
			case button:
				Button button;
				file >> button;
				_gameObjects->push_back(button);
				_renderableGameObjects->push_back(button);
				_controllableGameObjects->push_back(button);
				break;
			case award:
				Award award;
				file >> award;
				_gameObjects->push_back(award);
				_renderableGameObjects->push_back(award);
				break;
			case counter:
				Counter counter;
				file >> counter;
				_gameObjects->push_back(counter);
				_renderableGameObjects->push_back(counter);
				_updatableGameObjects->push_back(counter);
				break;*/
			default:
				throw "Error loading gameobject";
			}
		}
		file.close();
	}
}
void State::save(string& filename) {
	// Open a writeonly file stream
	fstream file;
	file.open(filename, fstream::out);
	if (file.good())
	{
		for (auto gameObject : _gameObjects) {
			file << &gameObject;
		}
		file.close();
	}
}