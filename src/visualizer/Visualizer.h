#ifndef VISUALIZER
#define VISUALIZER

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "../Object.h"
#include "Shader.cpp"
#include "Camera.h"
#include "../../lib/glm/glm/gtc/type_ptr.hpp"

typedef std::pair<std::vector<glm::vec3>, std::vector<int>> MeshData;

struct GraphicalSetup
{
    GLuint VBO;
    GLuint VAO;
    GLuint viewLoc;
    GLuint modelLoc;
    GLuint projectionLoc;
    Shader shader;
};

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
    void initializeInput();
    std::pair<std::vector<float>, int> getAllVertices();
    GraphicalSetup setupVisualization(glm::mat4 view, glm::mat4 model, glm::mat4 projection, std::vector<float> fVertices);
    Camera camera;
public:
    Visualizer(unsigned int WINDOW_W, unsigned int WINDOW_H);
    void start();
    void handleInput(double deltatime);
    void setEntities(std::vector<Object> &ent);
    MeshData calculateMeshVertices(Object &obj);
};

#endif