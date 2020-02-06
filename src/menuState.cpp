#include "menuState.h"

MenuState::MenuState(StateMachine* stateMachine) {
    m_StateMachine = stateMachine;
}

void MenuState::init() {
    m_PlayButton = { 300, 160, 200, 80 };
    m_ExitButton = { 300, 360, 200, 80 };
}

void MenuState::input(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 160 && event.button.y < 240) {
                std::cout << "Play button pressed!" << std::endl;
                m_StateMachine->pushState(std::make_unique<GameState>(m_StateMachine));
            }
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 360 && event.button.y < 440) {
                std::cout << "Exit button pressed!" << std::endl;
            }
        }
    }
}

void MenuState::update() {

}

void MenuState::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 21, 231, 91, 255);
    SDL_RenderFillRect(renderer, &m_PlayButton);
    SDL_SetRenderDrawColor(renderer, 170, 23, 53, 255);
    SDL_RenderFillRect(renderer, &m_ExitButton);
}

void MenuState::destroy() {

}