#include "Visualizer.h"

Visualizer::Visualizer(unsigned int WINDOW_W, unsigned int WINDOW_H)
{
    this->WINDOW_WIDTH = WINDOW_W;
    this->WINDOW_HEIGHT = WINDOW_H;

    // Set attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Initialize window and context
    this->window = SDL_CreateWindow("Physical Sim", 0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    this->glContext = SDL_GL_CreateContext(this->window);
    if(this->glContext != nullptr)
    {
        glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
        glewInit();
    }
}

void Visualizer::start()
{
    while(this->windowOpen)
    {
        this->handleInput();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(this->window);
    }
}

void Visualizer::handleInput()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        auto key = event.key.keysym;
        if (event.type == SDL_QUIT)
        {
            this->windowOpen = false;
        }
    }
}