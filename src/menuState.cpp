#include "menuState.h"

MenuState::MenuState(StateMachine* stateMachine, SDL_Renderer* renderer) {
    m_StateMachine = stateMachine;
    m_Renderer = renderer;
    m_TextPosition = { 0, 0 ,0 , 0 };
}

void MenuState::init() {
    TTF_Font* font = TTF_OpenFont("./assets/arial.ttf", 28);
    m_PlayTextLabel.init(m_Renderer, font);
    m_ExitTextLabel.init(m_Renderer, font);

    m_PlayButton = { 300, 160, 200, 80 };
    m_PlayTextLabel.createLabel("PLAY!", &m_TextPosition, { 0, 0, 0, 255 });
    m_TextPosition.x = (m_PlayButton.x + (m_PlayButton.w / 2)) - (m_TextPosition.w / 2);
    m_TextPosition.y = (m_PlayButton.y + (m_PlayButton.h / 2)) - (m_TextPosition.h / 2);
    m_PlayTextLabel.createLabel("PLAY!", &m_TextPosition, { 0, 0, 0, 255 });
    

    m_ExitButton = { 300, 360, 200, 80 };
    SDL_Rect exitTextPosition;
    m_ExitTextLabel.createLabel("EXIT!", &m_TextPosition, { 0, 0, 0, 255 }); 
    m_TextPosition.x = (m_ExitButton.x + (m_ExitButton.w / 2)) - (m_TextPosition.w / 2);
    m_TextPosition.y = (m_ExitButton.y + (m_ExitButton.h / 2)) - (m_TextPosition.h / 2);
    m_ExitTextLabel.createLabel("EXIT!", &m_TextPosition, { 0, 0, 0, 255 }); 
}

void MenuState::input(SDL_Event event) {
    if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			IsRunning = false;
		}
        if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            m_StateMachine->pushState(std::make_unique<GameState>(m_StateMachine, m_Renderer));
        }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 160 && event.button.y < 240) {
                std::cout << "Play button pressed!" << std::endl;
                m_StateMachine->pushState(std::make_unique<GameState>(m_StateMachine, m_Renderer));
            }
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 360 && event.button.y < 440) {
                std::cout << "Exit button pressed!" << std::endl;
                IsRunning = false;
            }
        }
    }
}

void MenuState::update() {

}

void MenuState::draw() {
    SDL_SetRenderDrawColor(m_Renderer, 21, 231, 91, 255);
    SDL_RenderFillRect(m_Renderer, &m_PlayButton);
    m_PlayTextLabel.draw(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 170, 23, 53, 255);
    SDL_RenderFillRect(m_Renderer, &m_ExitButton);
    m_ExitTextLabel.draw(m_Renderer);
}

void MenuState::destroy() {
}