#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "state.h"
#include "stateMachine.h"
#include "snake.h"
#include "food.h"
#include "textLabel.h"

struct vec2 {
	int x, y;
};

class GameState : public State {
private:
	StateMachine* m_StateMachine;
	SDL_Renderer* m_Renderer;
	SDL_Rect m_TextPosition;
	TextLabel m_ScoreTextLabel;
	std::string m_ScoreText;
	int m_Score;
	int m_Timer;
	int m_SnakeSpeed;
	int m_Size;
	vec2 m_Position;

	Snake* m_Snake;
	Food* m_Food;

public:
  	GameState(StateMachine* stateMachine, SDL_Renderer* renderer);
	void init() override;
	void input(SDL_Event event) override;
	void update() override;
	void draw() override;
	void destroy() override;
};