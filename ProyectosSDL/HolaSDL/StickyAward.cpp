#include "StickyAward.h"
#include "Game.h"
#include "State.h"

/// Public
/// Constructor
StickyAward::StickyAward(float32 x, float32 y, float32 width, float32 height, float32 speed, float32 framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void StickyAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current->addEvent([]() {
    Paddle *pad = dynamic_cast<GameState *>(State::current)->paddle();
    pad->setAction([pad]() {
      pad->splitFromBall();
      pad->setSticky(false);
    });
  });
}
