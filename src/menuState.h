#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "state.h"
#include "stateMachine.h"
#include "gameState.h"

class MenuState : public State {
private:
    StateMachine* m_StateMachine;
    SDL_Rect m_PlayButton;
    SDL_Rect m_ExitButton;

public:
    MenuState(StateMachine* stateMachine);
    void init() override;
	void input(SDL_Event event) override;
	void update() override;
	void draw(SDL_Renderer* renderer) override;
	void destroy() override;
};