#pragma once

#include "checkML.h"
#include "Box2D/Box2D.h"
#include "TopBoard.h"

class Game;


class GameManager
{
private:
  int _currentLevel;
  float32 _totalTime;
  int _currentBlocks;
  int _currentBalls;
  int _score;
  int _lives;
  static Game *_game;
  TopBoard* _topBoard;

public:
  GameManager(Game *game);
  ~GameManager();
  void finishLevel(float32 time);
  int getLevel() const;
  void setLevel(int level);
  void reset();
  void setBlocks(int blocksLenght);
  void addBlock();
  void deleteBlock();
  void addScore(int score);
  int getScore() const;
  void setScore(int score);
  void setBalls(int ballsLenght);
  void deleteBall();
  void addBalls(int balls);
  void setLives(int livesLenght);
  void deleteLive();
  void addLives(int lives);
  int getLives() const;
  void newGame();
  static Game *getGame() { return _game; };
  static void setGame(Game *game) { _game = game; };
  std::vector<PlayerGame*> getScores() const { return _topBoard->showScores(); };
};
