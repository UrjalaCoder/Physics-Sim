#ifndef VISUALIZER
#define VISUALIZER

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "../Object.h"
#include "Shader.cpp"

typedef std::pair<std::vector<glm::vec3>, std::vector<int>> MeshData;

class Visualizer
{
private:
    unsigned int WINDOW_WIDTH, WINDOW_HEIGHT;
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    bool windowOpen = true;
    std::vector<Object> entities;
    MeshData calculateRectMesh(std::vector<glm::vec3> objVertices);
    void render(Shader shader, GLuint VAO, int vertexCount);
public:
    Visualizer(unsigned int WINDOW_W, unsigned int WINDOW_H);
    void start();
    void handleInput();
    void setEntities(std::vector<Object> &ent);
    MeshData calculateMeshVertices(Object &obj);
};

#endif