#include "snake.h"

Snake::Snake(int x, int y, int size, Direction dir) {
	m_Direction = dir;
	m_Size = size;
	m_NewSegment = false;
	m_GameOver = false;
	m_CanChange = true;
	SDL_Rect head = { x * size, y * size, size - 1, size - 1 }; 
	m_Body.push_back(head);
}

void Snake::changeDirection(Direction dir) {
	if(m_CanChange) {
		if(m_Direction == UP	&& dir != DOWN 	||
			m_Direction == DOWN && dir != UP 	||
			m_Direction == LEFT && dir != RIGHT ||
			m_Direction == RIGHT && dir != LEFT)
		m_Direction = dir;
		m_CanChange = false;
	}
}

void Snake::addSegment() {
	m_NewSegment = true;
}

void Snake::update() {
	checkCollision();
	if(!m_GameOver) {
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
			m_CanChange = true;
		} 
		else {
			m_NewSegment = false;
		}
	}
}

void Snake::checkCollision() {
	SDL_Rect head = m_Body.front();
	for(auto it = ++m_Body.begin(); it != m_Body.end(); it++) {
		if(head.x == it->x && head.y == it->y) {
			m_GameOver = true;
		}
	}

	if(head.x < 0 || head.x > 800 - m_Size || head.y < 0 || head.y > 600 - m_Size) {
		m_GameOver = true;
	}
}

void Snake::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
	for(auto it = m_Body.rbegin(); it != --m_Body.rend(); it++) {
		SDL_RenderFillRect(renderer, &(*it));
	} 
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &m_Body.front());
}

std::list<SDL_Rect> Snake::getBody() const {
	return m_Body;
}

bool Snake::gameOver() const {
	return m_GameOver;
}






