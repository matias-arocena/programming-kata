#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>


int main(int argv, char** args) {
    SDL_Window* window = SDL_CreateWindow("emptySDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "[Video Error]:" 
                << SDL_GetError()
                << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (window == nullptr) {
        std::cerr << "[GL Context Error]:" 
                << SDL_GetError()
                << std::endl;
    }

    float red = 0.3f;
    float green = 0.3f;
    float blue = 0.3f;

    bool running = true;
    while(running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_RIGHT:
                    red++;
                    break;
                case SDLK_LEFT:
                    red--;
                    break;
                case SDLK_UP:
                    green++;
                    break;
                case SDLK_DOWN:
                    green--;
                    break;
                default:
                    break;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red, green, blue, 1);
        
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
}

