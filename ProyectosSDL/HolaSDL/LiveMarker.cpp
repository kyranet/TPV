#include "LiveMarker.h"
#include "Game.h"

/// Public
// Constructor
LiveMarker::LiveMarker(float32 x, float32 y, float32 width, float32 height,
                       Texture *texture)
    : GameObject(x, y, width, height), Renderable(texture) {}

/// Public Virtual
// Defines the render behaviour
void LiveMarker::render() const {
  SDL_Rect rect{(int)_position.x, (int)_position.y, _texture->getW(),
                _texture->getH()};
  int lives = Game::getGameManager()->getLives();
  for (int i = 0; i < lives; i++) {
    rect.x = (int)_position.x + i * _texture->getW();
    _texture->render(rect);
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &LiveMarker::deserialize(std::istream &out) { return out; }

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &LiveMarker::serialize(std::ostream &is) const { return is; }