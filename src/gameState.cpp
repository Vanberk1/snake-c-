#include "gameState.h"

GameState::GameState(StateMachine* stateMachine) {
	m_StateMachine = stateMachine;
}

void GameState::init() {
	m_Score = 0;
	m_Timer = 0;
	m_SnakeSpeed = 250;
	m_Size = 20;
	m_Position.x = 4;
	m_Position.y = 5;

	m_Snake = new Snake(m_Position.x, m_Position.y, m_Size, RIGHT);
	m_Food = new Food(m_Size);
	m_Food->respawn(*m_Snake);
}

void GameState::input(SDL_Event event) {
	if(!m_Snake->gameOver()) {
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				m_StateMachine->popState();
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_W) {
				m_Snake->changeDirection(UP);
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_A) {
				m_Snake->changeDirection(LEFT);
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_S) {
				m_Snake->changeDirection(DOWN);
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_D) {
				m_Snake->changeDirection(RIGHT);
			}

			if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				// snake.addSegment();
				// food.respawn(snake);
			}
		}
	}
}

void GameState::update() {
	if(!m_Snake->gameOver()) {
		m_Timer++;
		if(m_Timer > m_SnakeSpeed) {
			m_Snake->update();
			
			SDL_Rect headRect = m_Snake->getBody().front();
			SDL_Rect foodRect = m_Food->getBody();
			if(headRect.x == foodRect.x && headRect.y == foodRect.y) {
				m_Score++;
				m_Snake->addSegment();
				m_Food->respawn(*m_Snake);
				std::cout << "Score: " << m_Score << std::endl;
			}
			m_Timer = 0;
		}
	}
}

void GameState::draw(SDL_Renderer* renderer) {
	if(!m_Snake->gameOver()) {
		m_Food->draw(renderer);
		m_Snake->draw(renderer);
	}
}

void GameState::destroy() {
	delete m_Snake;
	delete m_Food;
}


