#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <vector>

enum class PointType {
    NORMAL,
    VERTEX
};

struct Point {
    GLdouble x, y, z;
    PointType type;
};

struct GameState {
    GLdouble zoom, cameraX, cameraY, degrees;
    bool fullscreen, running;
    SDL_Window* window;
    std::vector<Point> points;
    GLfloat *luz_posicion, *colorLuz;
};




std::vector<Point> ProcessFile(char* path) {
    std::vector<Point> result;
    std::ifstream infile(path);
    char type;
    float x, y, z;
    while (infile >> type >> x >> y >> z) {
        Point p;
        if (type == 'N') {
            p.type = PointType::NORMAL;
        }
        else {
            p.type = PointType::VERTEX;
        }
        p.x = x;
        p.y = y;
        p.z = z;

        result.push_back(p);
    }

    result.shrink_to_fit();

    return result;
}

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
        case SDLK_SPACE:
            gs->points.clear();
            gs->points = ProcessFile("../lightPolygons.txt");
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

void DrawPoints(std::vector<Point> points) {
    glBegin(GL_QUADS);
    for (Point p : points) {
        if (p.type == PointType::NORMAL) {
            glNormal3f(p.x, p.y, p.z);
        }
        else {
            glVertex3f(p.x, p.y, p.z);
        }
    }
    glEnd();

}

void Render(double deltaTime, struct GameState* gs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, gs->zoom, gs->cameraX, gs->cameraY, 0, 0, 1, 0);
    
    glTranslatef(0.0f, 0.0f, -6.f);

    glPushMatrix();

    gs->degrees = fmod(gs->degrees + 0.072 * deltaTime, 360);
    glRotated(gs->degrees, 0, 1, 0);

    glTranslatef(2.f, 1.f, 2.5f);

    glDisable(GL_LIGHTING);
    
    glBegin(GL_POLYGON);
        glColor3f(1.f, 1.f, 1.f);   
        glVertex3f(-0.25f, -0.25f, 0.f);
        glVertex3f(0.25f, -0.25f, 0.f);
        glVertex3f(0.25f, 0.25f, 0.f);
        glVertex3f(-0.25f, 0.25f, 0.f);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // habilita la luz 0
    glLightfv(GL_LIGHT0, GL_POSITION, gs->luz_posicion);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gs->colorLuz);



    glPopMatrix();

    //glRotated(gs->degrees/2, 0, 1, 0);
    DrawPoints(gs->points);
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

    
	GLfloat luz_posicion[4] = { 0, 0, 0, 1 };
	GLfloat colorLuz[4] = { 1, 1, 1, 1 };

    struct GameState* gs = new GameState;
    gs->zoom = 15;
    gs->cameraX = 0;
    gs->cameraY = 0;
    gs->degrees = 0;
    gs->fullscreen = false;
    gs->running = true;
    gs->window = window;
    gs->points = ProcessFile("../lightPolygons.txt");
    gs->luz_posicion = luz_posicion;
    gs->colorLuz = colorLuz;

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
    gs->points.clear();
    delete gs;

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
