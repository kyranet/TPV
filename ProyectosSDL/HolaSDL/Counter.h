#pragma once

#include "Text.h"
#include "Vector2D.h"
class Counter
{
private:
	int score;
	Text *text;

public:
	Counter(float x, float y, int width, int height, SDL_Color color, Font *font);
	Counter(Vector2D position, int width, int height, SDL_Color color, Font *font);
	~Counter();
	int setScore(const int num);
	int increaseScore(const int num);
	void render() const;
};
