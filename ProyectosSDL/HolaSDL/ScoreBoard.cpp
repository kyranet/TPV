#include "ScoreBoard.h"
#include <fstream>
#include <iostream>
#include "Game.h"

/// Public
// Constructor
ScoreBoard::ScoreBoard(Font *font, float32 x, float32 y, float32 width, float32 height, SDL_Color color)
    : GameObject(x, y, width, height), _font(font), _color(color)
{
  vector<PlayerGame *> scores = Game::getGameManager()->getScores();
  int j = 0;
  for (auto score : scores)
  {
    if (j == 10)
      break;
    _texts[j] = new Text(_font, _position.x, _position.y + getSize().y * j, getSize().x, getSize().y, _color,
                         to_string(j + 1) + "\u00ba " + score->name + " " + to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (unsigned int j = scores.size(); j < 10; j++)
  {
    string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
    _texts[j] = new Text(_font, _position.x, _position.y + getSize().y * j, getSize().x, getSize().y, _color, aux);
  }
}

/// Public
// Destructor
ScoreBoard::~ScoreBoard()
{
  for (auto text : _texts)
  {
    delete text;
  }
}

/// Public
// Creates the first ten games.
void ScoreBoard::rewrite()
{
  vector<PlayerGame *> scores = Game::getGameManager()->getScores();
  int j = 0;
  for (auto score : scores)
  {
    if (j == 10)
      break;
    _texts[j]->setText(to_string(j + 1) + "\u00ba " + score->name + " " + to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (unsigned int j = scores.size(); j < 10; j++)
  {
    _texts[j]->setText(to_string(j + 1) + "\u00ba ------ ------ ------");
  }
}

/// Public Virtual
// Defines the render behaviour
void ScoreBoard::render() const
{
  // Render the first 10 elements
  for (unsigned int j = 0; j < 10; j++)
  {
    _texts[j]->render();
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &ScoreBoard::deserialize(std::istream &out)
{
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &ScoreBoard::serialize(std::ostream &is) const
{
  return is;
}
