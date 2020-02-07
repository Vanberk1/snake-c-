#include "gameState.h"

GameState::GameState(StateMachine* stateMachine, SDL_Renderer* renderer) {
	m_StateMachine = stateMachine;
	m_Renderer = renderer;
}

void GameState::init() {
    TTF_Font* font = TTF_OpenFont("./assets/arial.ttf", 32);
	m_ScoreTextLabel.init(m_Renderer, font);
	m_TextPosition = { 25, 25, 0, 0};
	m_ScoreTextLabel.createLabel("SCORE: 0", &m_TextPosition, { 255, 255, 255, 255 }); 

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
	if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		// std::cout << "test 1" << std::endl;
		IsRunning = false;
	}
	if(!m_Snake->gameOver()) {
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				// std::cout << "test 2" << std::endl;
				// m_StateMachine->popState();
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
				std::cout << "SCORE: " << m_Score << std::endl;
				std::stringstream ss;

				ss << "SCORE: " << m_Score;
				m_ScoreTextLabel.setText(ss.str(), &m_TextPosition);
			}
			m_Timer = 0;
		}
	}
}

void GameState::draw() {
	m_Food->draw(m_Renderer);
	m_Snake->draw(m_Renderer);
	m_ScoreTextLabel.draw(m_Renderer);
}

void GameState::destroy() {
	delete m_Snake;
	delete m_Food;
}


