#pragma once

#include "state.h"
#include "stateMachine.h"
#include "snake.h"
#include "food.h"

struct vec2 {
	int x, y;
};

class GameState : public State {
private:
	StateMachine* m_StateMachine;
	int m_Score;
	int m_Timer;
	int m_SnakeSpeed;
	int m_Size;
	vec2 m_Position;

	Snake* m_Snake;
	Food* m_Food;

public:
  	GameState(StateMachine* stateMachine);
	void init() override;
	void input(SDL_Event event) override;
	void update() override;
	void draw(SDL_Renderer* renderer) override;
	void destroy() override;
};