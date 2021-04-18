#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include "Freeimage/FreeImage.h"
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
    gluPerspective(45, 640 / 480, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    //TEXTURA
    char* archivo = new char[13];
    archivo = "../opengl.png";

    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(archivo);
    FIBITMAP* bitmap = FreeImage_Load(fif, archivo);
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int w = FreeImage_GetWidth(bitmap);
    int h = FreeImage_GetHeight(bitmap);
    void* datos = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN

    GLuint textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_BGR, GL_UNSIGNED_BYTE, datos);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //FIN TEXTURA

    GLdouble zoom = 15;
    GLdouble cameraX = 0;
    GLdouble cameraY = 0;

    char state = 0;
    GLdouble polygonSize = 3.0;
    bool fullscreen = false;

    bool running = true;
    while (running) {
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
                polygonSize += 0.01;
                break;
            case SDLK_DOWN:
                polygonSize -= 0.01;
                break;
            case SDLK_w:
                cameraY += 0.01;
                break;
            case SDLK_s:
                cameraY -= 0.01;
                break;
            case SDLK_a:
                cameraX -= 0.01;
                break;
            case SDLK_d:
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

        glTranslatef(-1.5f, 0.0f, -5.9f);

        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3d(0, 1, 0);
        glColor3f(0, 1, 0);
        glVertex3d(-1, -1, 0);
        glColor3f(0, 0, 1);
        glVertex3d(1, -1, 0);
        glEnd();

        glTranslatef(3.0, 0, 0);

        //glPushMatrix();
        glScaled(polygonSize, polygonSize, 0.0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        

        glBegin(GL_POLYGON);
            glColor3f(1.0f, 1.0f, 1.0f);

            glTexCoord2d(49.0 / 512.0, (512.0 - 212.0 - 51.0) / 512);
            glVertex3d(-0.5, (212.0 / 512.0) / -2, 0);

            glTexCoord2d((49.0 + 452.0) / 512.0, (512.0 - 212.0 - 51.0) / 512);
            glVertex3d(0.5, (212.0 / 512.0) / -2, 0);

            glTexCoord2d((49.0 + 452.0) / 512.0, (512.0 - 51.0) / 512);
            glVertex3d(0.5, (212.0 / 512.0) / 2, 0);

            glTexCoord2d(49.0 / 512.0, (512.0 - 51.0) / 512);
            glVertex3d(-0.5, (212.0 / 512.0) / 2, 0);

        glEnd();
        glDisable(GL_TEXTURE_2D);

        //glPopMatrix();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

