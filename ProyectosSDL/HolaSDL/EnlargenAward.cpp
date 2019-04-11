#include "EnlargenAward.h"
#include "Game.h"
#include "GameState.h"

/// Public Virtual
// Defines behaviour when the instance gets in contact with the instance
void EnlargenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle larger
  State::current->addEvent([]() {
    Paddle* pad = dynamic_cast<GameState*>(State::current)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMaximumWidth);
    pad->setAction(NONE);
  });
}