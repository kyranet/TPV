#pragma once

#include <list>
#include <stack>
#include <functional>
#include "SDL.h"
#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "Renderable.h"
#include "Controllable.h"
#include "Updatable.h"
#include "ArkanoidTimer.h"

class Game;
class CollisionLogic;

class State
{
  class newInstance
  {
  public:
    newInstance(GAME_OBJECTS type, b2Vec2 &position)
        : type(type), position(position){};
    GAME_OBJECTS type;
    b2Vec2 position;
  };

protected:
  SDL_Renderer *_renderer = nullptr;
  list<GameObject *> _gameObjects;
  list<list<GameObject *>::iterator> _pendingOnDestroy;
  list<newInstance *> _pendingOnCreate;
  stack<function<void()>> _pendingEvents;
  CollisionLogic *_listenerLogic;
  b2World *_world;
  ArkanoidTimer *_stateTime;
  bool _exit = false;
  Game *_game;
  virtual void _end(){};

public:
  State(){};
  State(Game *game, SDL_Renderer *renderer);
  virtual ~State();
  static State *current;
  virtual void end() { _exit = true; };
  virtual void reset(){};
  virtual void init()
  {
    current = this;
    _stateTime->reset();
    _exit = false;
  };
  void destroy(list<GameObject *>::iterator &gameObjectId);

  void create();
  void render() const;
  void update();
  void handleEvents();
  void fixUpdate(float32 time);
  void afterUpdate();
  void events();
  virtual void destroy();

  void addCreation(GAME_OBJECTS type, b2Vec2 &position);
  GameObject *create(GAME_OBJECTS type, b2Vec2 &position);
  void add(GameObject &gameObject);
  void addEvent(function<void()>);
  float32 getTime() const;
};
