#include "food.h"

Food::Food(int size) {
	srand(time(NULL));
	m_Size = size;
	m_Body.w = m_Size;
	m_Body.h = m_Size;
}

void Food::respawn(Snake snake) {
	bool isValid = false;
	auto snakeBody = snake.getBody();
	int x;
	int y;
	while(!isValid) {
		bool isOverlaping = false;
		x = (rand() % GRID_X) * m_Size;
		y = (rand() % GRID_Y) * m_Size;

		for(auto it = snakeBody.begin(); it != snakeBody.end(); it++) {
			if(x == it->x && y == it->y) {
				isOverlaping = true;
				break;
			}
		}
		if(!isOverlaping) {
			isValid = true;
		}
	}

	m_Body.x = x;
	m_Body.y = y;
}

void Food::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &m_Body);
}

SDL_Rect Food::getBody() const {
	return m_Body;
}