#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include <iostream>
#include <cmath>
#include <chrono>

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

    glMatrixMode(GL_PROJECTION);
    glClearColor(0, 0, 0, 1);
    gluPerspective(45, 640 / 480, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    GLdouble zoom = 15;
    GLdouble cameraX = 0;
    GLdouble cameraY = 0;
    GLfloat degrees = 0;

    bool fullscreen = false;

    bool running = true;
    auto newTime = std::chrono::system_clock::now();
    while (running) {
        auto oldTime = newTime;
        newTime = std::chrono::system_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(newTime - oldTime).count();

        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_KP_PLUS:
                zoom -= 0.4;
                break;
            case SDLK_KP_MINUS:
                zoom += 0.4;
                break;
            case SDLK_UP:
                cameraY += 0.01;
                break;
            case SDLK_DOWN:
                cameraY -= 0.01;
                break;
            case SDLK_LEFT:
                cameraX -= 0.01;
                break;
            case SDLK_RIGHT:
                cameraX += 0.01;
                break;
            case SDLK_c:
                cameraX = 0;
                cameraY = 0;
                zoom = 15;
                break;
            case SDLK_F11:
                if (fullscreen) {
                    SDL_SetWindowFullscreen(window, SDL_FALSE);
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
                fullscreen = !fullscreen;
                break;
            default:
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(0, 0, zoom, cameraX, cameraY, 0, 0, 1, 0);

        degrees = fmod(degrees + 0.072 * deltaTime, 360);
        glRotatef(degrees, 0, 0, -6);

        glTranslatef(-1.5f, 0.0f, -5.9f);

        glPushMatrix();
        glRotatef(degrees, 0, 1, 0);
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
        glRotatef(-degrees, 0, 1, 0);
        glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.4f, 1.f);
        glVertex3d(-1, 1, 0);
        glVertex3d(1, 1, 0);
        glVertex3d(1, -1, 0);
        glVertex3d(-1, -1, 0);
        glEnd();
        glPopMatrix();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

