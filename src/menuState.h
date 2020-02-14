#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "state.h"
#include "stateMachine.h"
#include "gameState.h"
#include "textLabel.h"

class MenuState : public State {
private:
    StateMachine* m_StateMachine;
    SDL_Renderer* m_Renderer;
    SDL_Rect m_TextPosition;
    SDL_Rect m_PlayButton;
    TextLabel m_PlayTextLabel;
    SDL_Rect m_ExitButton;
    TextLabel m_ExitTextLabel;
public:
    MenuState(StateMachine* stateMachine, SDL_Renderer* renderer);
    void init() override;
	void input(SDL_Event event) override;
	void update(float deltaTime) override;
	void draw() override;
	void destroy() override;
};