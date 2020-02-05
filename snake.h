#pragma once

#include <SDL2/SDL.h>
#include <list>
#include <iostream>

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Snake {
private:
	std::list<SDL_Rect> m_Body;
	Direction m_Direction;
	int m_Size;
	bool m_NewSegment;
	bool m_GameOver;
public:
	Snake(int x, int y, int size, Direction dir);
	void changeDirection(Direction dir);
	void addSegment();
	void update();
	void draw(SDL_Renderer* renderer);
	void checkCollision();

	std::list<SDL_Rect> getBody() const;
	bool gameOver() const;
};