#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

extern const int GRID_X;
extern const int GRID_Y;

class Food {
private:
	SDL_Rect m_Body;
	int m_Size;
public:
	Food(int size);
	void respawn(Snake snake);
	void draw(SDL_Renderer* renderer);

	SDL_Rect getBody() const;
};