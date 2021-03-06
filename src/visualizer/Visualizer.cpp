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

void Visualizer::setEntities(std::vector<Object*> &ent)
{
    // Clear and reserve memory
    this->entities.clear();
    this->entities.reserve(ent.size());

    this->cubes.clear();

    // Copy the entities
    for(int i = 0; i < ent.size(); ++i)
    {
        Object entity = *(ent[i]);
        this->entities.push_back(entity);
        if(entity.shape == CUBE)
        {
            this->cubes.push_back(entity);
        }
    }
}

GraphicalSetup Visualizer::setupVisualization(glm::mat4 view, glm::mat4 model, glm::mat4 projection, std::vector<float> fVertices)
{
    float *vertices = &fVertices[0];
    // Setup VBO, Shaders and VAO
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // Shader setup
    Shader myShader("./src/visualizer/vertexShader.vs", "./src/visualizer/fragmentShader.vs");
    myShader.use();
    int modelLoc = glGetUniformLocation(myShader.ID, "model");
    int viewLoc = glGetUniformLocation(myShader.ID, "view");
    int projectionLoc = glGetUniformLocation(myShader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * fVertices.size(), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Enable Depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable vSync
    SDL_GL_SetSwapInterval(1);

    struct GraphicalSetup setup = { VBO, VAO, viewLoc, modelLoc, projectionLoc, myShader };
    return setup;
}

std::vector<float> getCubeVertices(std::vector<glm::vec3> vertices, std::vector<int> order)
{
    std::vector<float> fVertices(order.size() * 3);
    for(int i = 0; i < order.size(); i++)
    {
        int index = i * 3;
        glm::vec3 vertex = vertices[order[i]];
        fVertices[index] = vertex.x;
        fVertices[index + 1] = vertex.y;
        fVertices[index + 2] = vertex.z;
    }

    return fVertices;
}

void Visualizer::start()
{
    auto vertexData = this->calculateMeshVertices(this->cubes[0]);
    std::vector<float> fVertices = getCubeVertices(vertexData.first, vertexData.second);

    // Initialize matrices.
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    GraphicalSetup setup = this->setupVisualization(view, model, projection, fVertices);
   
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double deltaTime = 0;
    this->initializeInput();

    setup.shader.use();
    while(this->windowOpen)
    {
        this->handleInput(deltaTime);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = this->camera.getView();

        // Update view
        glUniformMatrix4fv(setup.viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Render
        glBindVertexArray(setup.VAO);
        for(auto &cube : this->cubes)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube.position);
            glm::mat4 rotationMatrix = glm::toMat4(cube.rotation);
            model = model * rotationMatrix;
            glUniformMatrix4fv(setup.modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            this->render(setup.shader, vertexData.second.size());
        }

        // Update time
        Uint64 now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - lastTime)*1000 / (double)SDL_GetPerformanceFrequency() );
        lastTime = now;

        SDL_GL_SwapWindow(this->window);
    }
}

void Visualizer::render(Shader shader, int vertexCount)
{
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Visualizer::initializeInput()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_WarpMouseInWindow(this->window, this->WINDOW_WIDTH / 2, this->WINDOW_HEIGHT / 2);
}

void Visualizer::handleInput(double delta)
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        auto key = event.key.keysym;
        if (event.type == SDL_QUIT)
        {
            this->windowOpen = false;
        }
        if(event.type == SDL_KEYDOWN)
        {
            switch (key.sym)
            {
            case SDLK_w:
                this->camera.handleInput(FORWARD, delta);
                break;
            case SDLK_a:
                this->camera.handleInput(LEFT, delta);
                break;
            case SDLK_d:
                this->camera.handleInput(RIGHT, delta);
                break;
            case SDLK_s:
                this->camera.handleInput(BACKWARD, delta);
                break;
            case SDLK_q:
                this->windowOpen = false;
                break;
            default:
                break;
            }
        }
        if(event.type == SDL_MOUSEMOTION)
        {
            this->camera.updateDirection(event.motion.xrel, event.motion.yrel);
        }
    }
}

MeshData Visualizer::calculateMeshVertices(Object &obj)
{
    if(obj.shape == CUBE)
    {
        return this->calculateRectMesh(obj.vertices);
    } else {
        // TODO: Implement other shapes
        return MeshData();
    }
}

MeshData Visualizer::calculateRectMesh(std::vector<glm::vec3> objVertices)
{
    std::vector<glm::vec3> vertices = objVertices;
    constexpr int N = 36;
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
    temp = triangulateQuad(1, 5, 6, 2);
    copyToVertex(vertexOrder, temp, 5);

    MeshData result;
    result = std::make_pair(vertices, vertexOrder);
    return result;
}