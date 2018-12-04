#include "MenuState.h"
#include "Button.h"
#include "Game.h"
#include <functional>

/**
 * Constructor.
 */
MenuState::MenuState(Game *game, SDL_Renderer *renderer) : State(game, renderer)
{
  auto _buttons = new Button *[4];
  string nombres[4] = {"New Game", "Continue", "ScoreBoard", "Exit"};
  function<void()> callbacks[4] = {
      [this, game]() { _exit = true; game->changeState(GAME); game->getGameState()->newGame(true); },
      [this, game]() { _exit = true; game->changeState(GAME); game->getGameState()->newGame(false); },
      [this, game]() { _exit = true; game->changeState(SCOREBOARD); },
      [this, game]() { _exit = true; game->changeState(GAMEOVER); }};

  for (int i = 0; i < 4; i++)
  {
    _buttons[i] = new Button(game->getFonts()[BIGFONT], 0, i * 110, 200, 100, WHITE, GREY, nombres[i], callbacks[i]);
    add(*_buttons[i]);
  }
  delete[] _buttons;
}

/**
 * Destructor.
 */
MenuState::~MenuState()
{
}
