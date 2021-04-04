#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include <iostream>


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
    gluPerspective(45, 640/480, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);   

    GLdouble zoom = 15;
    GLdouble cameraX = 0;
    GLdouble cameraY = 0;

    char state = 0;
    bool fullscreen = false;

    bool running = true;
    while(running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
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
                case SDLK_SPACE:
                    state = (state + 1) % 3;
                    break;
                case SDLK_F11:
                    if(fullscreen) {
                        SDL_SetWindowFullscreen(window, SDL_FALSE);
                    } else {
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

        glBegin(GL_TRIANGLES);
            glColor3d(1, 1, 1);
            glVertex3d(-1.5,  1, -6);
            glColor3d(1, 1, 1);
            glVertex3d(-2.5, -1, -6);
            glColor3d(1, 1, 1);
            glVertex3d(-0.5, -1, -6);
        glEnd();
        
        glBegin(GL_POLYGON);
            glVertex3d(0.5, 1, -6);
            glColor3d(1, 1, 1);
            glVertex3d(2.5, 1, -6);
            glColor3d(1, 1, 1);
            glVertex3d(2.5, -1, -6);
            glColor3d(1, 1, 1);
            glVertex3d(0.5, -1, -6);
        glEnd();

        if (state > 0) {
            glTranslatef(-1.5f, 0.0f, -5.9f);
        
            glBegin(GL_TRIANGLES);
                glColor3f(1, 0, 0);
                glVertex3d(0, 1, 0);
                glColor3f(0, 1, 0);
                glVertex3d(-1, -1, 0);
                glColor3f(0, 0, 1);
                glVertex3d(1, -1, 0);
            glEnd();
        }

        if (state > 1) {
            glTranslatef(3, 0, 0);
        
            glBegin(GL_POLYGON);
                glColor3f(0.4f, 0.4f, 1.f);
                glVertex3d(-1, 1, 0);
                glVertex3d(1, 1, 0);
                glVertex3d(1, -1, 0);
                glVertex3d(-1, -1, 0);
            glEnd();
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
}

