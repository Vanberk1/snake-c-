#pragma once

#include <SDL2/SDL.h>
#include <list>

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

public:
	Snake(int x, int y, int size, Direction dir);
	void changeDirection(Direction dir);
	void addSegment();
	void update();
	void draw(SDL_Renderer* renderer);

	std::list<SDL_Rect> getBody() const;
};