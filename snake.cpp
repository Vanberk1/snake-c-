#include "snake.h"

Snake::Snake(int x, int y, int size, Direction dir) {
	m_Direction = dir;
	m_Size = size;
	m_NewSegment = false;
	SDL_Rect head = { x * size, y * size, size - 1, size - 1 }; 
	m_Body.push_back(head);
}

void Snake::changeDirection(Direction dir) {
	m_Direction = dir;
}

void Snake::addSegment() {
	m_NewSegment = true;
}

void Snake::update() {
	SDL_Rect actualHead = m_Body.front();
	switch(m_Direction) {
	case UP:
		m_Body.push_front({ actualHead.x, actualHead.y - m_Size, m_Size - 1, m_Size - 1 });
		break;
	case LEFT:
		m_Body.push_front({ actualHead.x - m_Size, actualHead.y, m_Size - 1, m_Size - 1 });
		break;
	case DOWN:
		m_Body.push_front({ actualHead.x, actualHead.y + m_Size, m_Size - 1, m_Size - 1 });
		break;
	case RIGHT:
		m_Body.push_front({ actualHead.x + m_Size, actualHead.y, m_Size - 1, m_Size - 1 });
		break;
	}

	if(!m_NewSegment) {
		m_Body.pop_back();
	} 
	else {
		m_NewSegment = false;
	}
}

void Snake::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for(auto it = m_Body.begin(); it != m_Body.end(); it++) {
		SDL_RenderFillRect(renderer, &(*it));
	} 
}

std::list<SDL_Rect> Snake::getBody() const {
	return m_Body;
}