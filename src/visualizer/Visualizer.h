#ifndef VISUALIZER
#define VISUALIZER

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Visualizer
{
private:
    unsigned int WINDOW_WIDTH, WINDOW_HEIGHT;
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    bool windowOpen = true;
public:
    Visualizer(unsigned int WINDOW_W, unsigned int WINDOW_H);
    void start();
    void handleInput();
};

#endif