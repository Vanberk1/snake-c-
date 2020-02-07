#include "gameState.h"

GameState::GameState(StateMachine* stateMachine, SDL_Renderer* renderer) {
	m_StateMachine = stateMachine;
	m_Renderer = renderer;
}

void GameState::init() {
    TTF_Font* font = TTF_OpenFont("./assets/arial.ttf", 32);
	TTF_Font* fontGameOver = TTF_OpenFont("./assets/arial.ttf", 48);

	m_ScoreTextLabel.init(m_Renderer, font);
	m_GameOverText.init(m_Renderer, fontGameOver);
	m_RestartText.init(m_Renderer, font);

	m_ScoreTextLabel.setPosition({ 25, 25, 0 , 0 });
	m_ScoreTextLabel.createLabel("SCORE: 0", { 255, 255, 255, 255 }); 

	m_GameOverText.createLabel("GAME OVER", { 255, 255, 255, 255 });
	SDL_Rect* textPosition = m_GameOverText.getPosition();
	textPosition->x = (800 / 2) - (textPosition->w / 2);
	textPosition->y = (600 / 2) - (textPosition->h / 2) - 60;
	m_GameOverText.setPosition(*textPosition);
	m_GameOverText.setText("GAME OVER");

	m_RestartText.createLabel("PRESS 'R' TO RESTART", { 255, 255, 255, 255 });
	textPosition = m_RestartText.getPosition();
	textPosition->x = (800 / 2) - (textPosition->w / 2);
	textPosition->y = (600 / 2) - (textPosition->h / 2);
	m_RestartText.setPosition(*textPosition);
	m_RestartText.setText("PRESS 'R' TO RESTART");

	m_Score = 0;
	m_Timer = 0;
	m_SnakeSpeed = 500;
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
				std::cout << "UP" << std::endl;
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_A) {
				m_Snake->changeDirection(LEFT);
				std::cout << "LEFT" << std::endl;
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_S) {
				m_Snake->changeDirection(DOWN);
				std::cout << "DOWN" << std::endl;
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_D) {
				m_Snake->changeDirection(RIGHT);
				std::cout << "RIGHT" << std::endl;
			}
		}
	}
	else {
		if(event.key.keysym.scancode == SDL_SCANCODE_R) {
			m_StateMachine->restart(std::make_unique<GameState>(m_StateMachine, m_Renderer));
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
				m_ScoreTextLabel.setText(ss.str());
			}
			m_Timer = 0;
		}
	}
}

void GameState::draw() {
	m_Food->draw(m_Renderer);
	m_Snake->draw(m_Renderer);
	m_ScoreTextLabel.draw(m_Renderer);

	if(m_Snake->gameOver()) {
		m_GameOverText.draw(m_Renderer);
		m_RestartText.draw(m_Renderer);
	}
}

void GameState::destroy() {
	delete m_Snake;
	delete m_Food;
}


