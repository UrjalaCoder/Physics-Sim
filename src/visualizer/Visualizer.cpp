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

void Visualizer::setEntities(std::vector<Object> &ent)
{
    // Clear and reserve memory
    this->entities.clear();
    this->entities.reserve(ent.size());

    // Copy the entities
    for(int i = 0; i < ent.size(); ++i)
    {
        this->entities[i] = ent[i];
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

MeshData Visualizer::calculateMeshVertices(Object &obj)
{
    if(obj.shape == CUBE || obj.shape == RECT)
    {
        return this->calculateRectMesh(obj.vertices);
    } else {
        return MeshData();
    }
}

MeshData Visualizer::calculateRectMesh(std::vector<glm::vec3> objVertices)
{
    std::vector<glm::vec3> vertices = objVertices;
    constexpr int N = 24;
    std::vector<int> vertexOrder = std::vector<int>(N, 0);

    auto triangulateQuad = [](int a, int b, int c, int d)
    {
        std::vector<int> quadVertices = std::vector<int>(6, 0);
        quadVertices[0] = a;
        quadVertices[1] = b;
        quadVertices[2] = c;
        quadVertices[3] = c;
        quadVertices[4] = d;
        quadVertices[5] = a;
        return quadVertices;
    };

    std::vector<int> temp(6, 0);

    auto copyToVertex = [](std::vector<int> &vertices, std::vector<int> &temp, int startIndex)
    {
        for(int i = 0; i < 6; ++i)
        {
            vertices[i + startIndex * 6] = temp[i];
        }
    };

    // First upper half
    temp = triangulateQuad(0, 1, 2, 3);
    copyToVertex(vertexOrder, temp, 0);

    // Upper half done, bigger side 1
    temp = triangulateQuad(1, 0, 4, 5);
    copyToVertex(vertexOrder, temp, 1);

    // Bottom
    temp = triangulateQuad(4, 5, 6, 7);
    copyToVertex(vertexOrder, temp, 2);

    // Other long side
    temp = triangulateQuad(3, 2, 6, 7);
    copyToVertex(vertexOrder, temp, 3);

    // Front facing small
    temp = triangulateQuad(0, 3, 7, 4);
    copyToVertex(vertexOrder, temp, 4);

    // Backwards facing small
    temp = triangulateQuad(1, 3, 6, 2);
    copyToVertex(vertexOrder, temp, 5);

    MeshData result;
    result = std::make_pair(vertices, vertexOrder);
    return result;
}