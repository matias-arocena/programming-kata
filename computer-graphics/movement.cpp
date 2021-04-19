#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include <iostream>
#include <cmath>
#include <chrono>

struct GameState {
    GLdouble zoom , cameraX, cameraY, degrees;
    bool fullscreen, running;
    SDL_Window* window;
};


void ProcessInput(struct GameState* gs) {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            gs->running = false;
            break;
        case SDLK_KP_PLUS:
            gs->zoom -= 0.4;
            break;
        case SDLK_KP_MINUS:
            gs->zoom += 0.4;
            break;
        case SDLK_UP:
            gs->cameraY += 0.01;
            break;
        case SDLK_DOWN:
            gs->cameraY -= 0.01;
            break;
        case SDLK_LEFT:
            gs->cameraX -= 0.01;
            break;
        case SDLK_RIGHT:
            gs->cameraX += 0.01;
            break;
        case SDLK_c:
            gs->cameraX = 0;
            gs->cameraY = 0;
            gs->zoom = 15;
            break;
        case SDLK_F11:
            if (gs->fullscreen) {
                SDL_SetWindowFullscreen(gs->window, SDL_FALSE);
            }
            else {
                SDL_SetWindowFullscreen(gs->window, SDL_WINDOW_FULLSCREEN);
            }
            gs->fullscreen = !gs->fullscreen;
            break;
        default:
            break;
        }
    }
}

void Render(double deltaTime, struct GameState* gs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, gs->zoom, gs->cameraX, gs->cameraY, 0, 0, 1, 0);

    gs->degrees = fmod(gs->degrees + 0.072 * deltaTime, 360);
    glRotated(gs->degrees, 0, 0, -6);

    glTranslatef(-1.5f, 0.0f, -5.9f);

    glPushMatrix();
    glRotated(gs->degrees, 0, 1, 0);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3d(0, 1, 0);
    glColor3f(0, 1, 0);
    glVertex3d(-1, -1, 0);
    glColor3f(0, 0, 1);
    glVertex3d(1, -1, 0);
    glEnd();
    glPopMatrix();

    glTranslatef(3, 0, 0);

    glPushMatrix();
    glRotated(-gs->degrees, 0, 1, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.4f, 1.f);
    glVertex3d(-1, 1, 0);
    glVertex3d(1, 1, 0);
    glVertex3d(1, -1, 0);
    glVertex3d(-1, -1, 0);
    glEnd();
    glPopMatrix();
}

void GameLoop(double deltaTime, GameState* gs) {
    ProcessInput(gs);

    Render(deltaTime, gs);
}


int main(int argv, char** args) {
    SDL_Window* window = SDL_CreateWindow("colorPolygon",
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

    struct GameState* gs = new GameState;
    gs->zoom = 15;
    gs->cameraX = 0;
    gs->cameraY = 0;
    gs->degrees = 0;
    gs->fullscreen = false;
    gs->running = true;
    gs->window = window;

    glMatrixMode(GL_PROJECTION);
    glClearColor(0, 0, 0, 1);
    gluPerspective(45, 640 / 480, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    
    auto newTime = std::chrono::system_clock::now();
    while (gs->running) {
        auto oldTime = newTime;
        newTime = std::chrono::system_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(newTime - oldTime).count();
        GameLoop(deltaTime, gs);
        
        SDL_GL_SwapWindow(window);
    }

    gs->window = nullptr;
    delete gs;

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
