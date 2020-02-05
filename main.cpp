#include <SDL2/SDL.h>
#include <iostream>
#include "snake.h"
#include "food.h";

const int GRID_X = 40;
const int GRID_Y = 30;

int main(int argc, char* args[]) { 
    bool isRunning = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL Failed!" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Snake!", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        GRID_X * 20,
        GRID_Y * 20,
        SDL_WINDOW_SHOWN
    );
    if(!window) {
        std::cout << "SDL window Failed!" << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        std::cout << "SDL renderer Failed!" << std::endl;
        return 1;
    }
    int timer = 0;
    int x = 4, y = 5;
    int size = 20;
    int score = 0;

    Snake snake(x, y, size, RIGHT);
    Food food(size);
    food.respawn(snake);

    while(isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isRunning = false;
            }

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.scancode == SDL_SCANCODE_W) {
                    snake.changeDirection(UP);
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_A) {
                    snake.changeDirection(LEFT);
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_S) {
                    snake.changeDirection(DOWN);
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_D) {
                    snake.changeDirection(RIGHT);
                }

                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    // snake.addSegment();
                    // food.respawn(snake);
                }
            }
        }

        timer++;
        if(timer > 100) {
            snake.update();
            
            SDL_Rect headRect = snake.getBody().front();
            SDL_Rect foodRect = food.getBody();
            if(headRect.x == foodRect.x && headRect.y == foodRect.y) {
                score++;
                snake.addSegment();
                food.respawn(snake);
                std::cout << "Score: " << score << std::endl;
            }
            timer = 0;
        }
        
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        
        food.draw(renderer);
        snake.draw(renderer);
    
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}